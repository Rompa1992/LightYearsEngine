# Index

- Specific Solution Code:
    - Class: Apllication{};
    - World.cpp: TickInternal()
    - config.h: GetResourceDir()
    - Class: AssetManager{};
    - AssetManager: AssetManager& Get()
    - AssetManager: LoadTexture()
    - AssetManager: CleanCycle()
    - PhysicsSystem: Singleton Design and Protected Constructor
    - PhysicsSystem::AddListener()
    - Understanding The Delegate System in `ly` Namespace

- Code Fundementals 
    - When to Forward Declare vs Include
    - Lambda Functions in C++

- Output Bugs

- Inline Errors



---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# SPECIFIC SOLUTION CODE  

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



# Class: Apllication{};

This document explains the `Application` creation process, including how dynamic allocation and polymorphism work in the context of the `GetApplication()` function.

---

## What Does `GetApplication()` Do?
- `GetApplication()` is a global factory function that creates and returns a pointer to an `Application` object.
- Specifically, it dynamically allocates a `GameApplication` object (a subclass of `Application`) on the heap using `new`.
- The returned object is treated as an `Application*` due to inheritance, allowing polymorphism to work correctly.

---

## Why Use Pointers in `GetApplication()`?

### Dynamic Allocation
- The object created with `new` persists beyond the scope of `GetApplication()` and can be explicitly deleted when no longer needed.

### Polymorphism
- Using a pointer to the base class (`Application*`), the program can interact with the derived class (`GameApplication`) and call overridden methods dynamically.
- For example, calling `Run()` on `Application*` will invoke the `GameApplication::Run()` implementation if it’s overridden.

---

## How Is It Used in `main()`?
- The pointer returned by `GetApplication()` is stored in a base class pointer (`Application*`).
- The program then calls the `Run()` method, which leverages polymorphism to execute the derived class implementation:

```cpp
ly::Application* app = GetApplication(); // Get a dynamically allocated GameApplication
app->Run();                              // Calls GameApplication::Run() due to polymorphism
delete app;                              // Cleans up memory to avoid leaks
```

---

## What Happens If You Use an Object Instead of a Pointer?

Changing `ly::Application* app = GetApplication();` to `ly::Application app = GetApplication();` causes a compilation error:

1. **Pointer to Object Assignment**:
   - The compiler cannot assign a pointer (`Application*`) to an object (`Application`).

2. **Dereferencing the Pointer**:
   - If you dereference the pointer:
     ```cpp
     ly::Application app = *GetApplication(); // Dereference the pointer to copy the object
     ```
     - **Object Slicing**: The base class portion of the `GameApplication` is copied into `app`, losing derived class data and behavior.
     - **Memory Leak**: The original `GameApplication` created with `new` is left on the heap, causing a memory leak since it is not deleted.

---

## Best Practices for `GetApplication()`

1. **Use Pointers When Polymorphism Is Needed**:
   ```cpp
   ly::Application* app = GetApplication();
   app->Run(); // Calls the overridden version in GameApplication
   delete app; // Properly cleans up the dynamically allocated object
   ```

2. **Return an Object Directly If Polymorphism Is Not Required**:
   ```cpp
   ly::Application GetApplication() {
       return ly::GameApplication(); // Returns an object, not a pointer
   }
   ```

---

## Why Stick to Pointers Here?

### Pointers Enable:
- Dynamic allocation for explicit lifetime control.
- Polymorphism, allowing derived class methods to override base class methods dynamically.

### Returning an Object Instead:
- Simplifies memory management but removes polymorphism, as the type of the object is fixed at compile time.



---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# World.cpp: TickInternal()

---

## What Does `TickInternal()` Do?

- `TickInternal()` processes actors in the game world during a single update cycle.
- Specifically, it:
  1. Adds new actors from `_pendingActors` to `_actors` and initializes them.
  2. Removes actors flagged for destruction.
  3. Updates all active actors by calling their `Tick(deltaTime)` function.
  4. Updates the global state of the world itself via the `Tick(deltaTime)` function.

---

## Adding New Actors

```cpp
for (shared_ptr<Actor> actor : _pendingActors)
{
    _actors.push_back(actor);
    actor->BeginPlayInternal();
}

_pendingActors.clear();
```

- `_pendingActors` is a list of actors waiting to be added to the game world.
- Each actor is:
  - Moved to `_actors`, the list of active actors.
  - Initialized by calling `BeginPlayInternal()`, a function that sets up the actor when it becomes active.
- After processing all pending actors, `_pendingActors` is cleared to prevent duplication.

---

## Removing Destroyed Actors

```cpp
for (auto iter = _actors.begin(); iter != _actors.end();)
{
    if (iter->get()->IsPendingDestroy())
        iter = _actors.erase(iter);
    else
    {
        iter->get()->Tick(deltaTime);
        ++iter;
    }
}
```

- `_actors` is the list of all active actors.
- The loop uses an iterator (`iter`) to traverse `_actors`.

### Key Steps:
1. **Check for Pending Destruction**:
   - `iter->get()` retrieves the raw pointer from the `shared_ptr<Actor>`.
   - `IsPendingDestroy()` checks if the actor is flagged for destruction.
2. **Erase Actors Pending Destruction**:
   - If `IsPendingDestroy()` returns `true`, the actor is removed using `erase()`.
   - `erase()` returns an updated iterator, ensuring the loop continues correctly without invalidating the iterator.
3. **Update Active Actors**:
   - If the actor is not pending destruction, `Tick(deltaTime)` is called to update its state.
   - The iterator is then incremented to process the next actor.

---

## Ticking the World

```cpp
Tick(deltaTime);
```

- The `Tick` function is likely a higher-level function responsible for updating the global state of the world.
- It operates after all actors have been processed, ensuring that the world itself stays in sync with its actors.

---

## Full Code for Reference

```cpp
void World::TickInternal(float deltaTime)
{
    for (shared_ptr<Actor> actor : _pendingActors)
    {
        _actors.push_back(actor);
        actor->BeginPlayInternal();
    }

    _pendingActors.clear();

    for (auto iter = _actors.begin(); iter != _actors.end();)
    {
        if (iter->get()->IsPendingDestroy())
            iter = _actors.erase(iter);
        else
        {
            iter->get()->Tick(deltaTime);
            ++iter;
        }
    }

    Tick(deltaTime);
}

```


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# config.h: `GetResourceDir()`

## Purpose
The `GetResourceDir` function determines the directory path for resource files (e.g., assets like textures and sounds) based on the build configuration (Debug or Release). This helps manage resources dynamically, ensuring the correct paths are used during development and after packaging.

---

## Behavior
### **Release Build (`NDEBUG` defined)**
- Returns a relative path: `@RESOURCE_FOLDER_NAME@/`
- This corresponds to the `assets/` folder copied to the same directory as the game executable during the build process.
- Example: `build/LightYearsGame/assets/`

### **Debug Build (`NDEBUG` not defined)**
- Returns an absolute path: `@RESOURCE_SRC_DIR@/`
- This resolves to the source directory where the `assets` folder resides during development.
- Example: `LightYearsGame/assets/`

---

## CMake Integration
The `GetResourceDir` function uses placeholders (`@RESOURCE_FOLDER_NAME@` and `@RESOURCE_SRC_DIR@`) that are replaced during the CMake configuration process. These values are defined as follows:
- `RESOURCE_FOLDER_NAME`: `"assets"`
- `RESOURCE_SRC_DIR`: `${CMAKE_CURRENT_SOURCE_DIR}/assets`

This setup ensures:
1. The `assets` folder in the source directory is copied to the build directory during the build process.
2. The executable can seamlessly access resources during both development and production.

---

## Workflow Example
1. **Debug Build**:
   - Resources are loaded directly from the source directory for easy editing and testing.
   - Path Example: `LightYearsGame/assets/`

2. **Release Build**:
   - Resources are loaded from the `assets` folder in the build/output directory, which is populated by CMake during the build process.
   - Path Example: `build/LightYearsGame/assets/`

---

## Key Notes
- The **custom command** in the `LightYearsGame` CMake file ensures the `assets` folder is copied to the build directory:
  ```cmake
  add_custom_command(TARGET ${LIGHT_YEARS_GAME_TARGET_NAME}
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy_directory
      ${RESOURCE_SRC_DIR}
      $<TARGET_FILE_DIR:${LIGHT_YEARS_GAME_TARGET_NAME}>/${RESOURCE_FOLDER_NAME}
  )

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# Class Explanation: AssetManager{};

## Purpose
The `AssetManager` class is designed as a **singleton**, meaning it ensures that only one instance of the class exists during the program's lifetime. This pattern is particularly useful for managing shared resources like textures, sounds, or fonts in a game, providing a centralized and consistent way to access assets.

---

## Behavior
### **Singleton Design**
- The class restricts instantiation by making the constructor `protected`, preventing external code from creating new instances.
- A **static pointer** (`_assetManager`) is declared to hold the single instance of the class. It ensures all parts of the application access the same instance.

### **Static Member**
- `static AssetManager* _assetManager;`:
  - A **static member** belongs to the class itself, rather than any individual instance.
  - It ensures the singleton instance is shared across the entire application.

---

## How It Works
1. **Creating the Singleton Instance**:
   - The class likely includes a public static method (e.g., `GetInstance`) to create and return the single instance.
   - This method would check if `_assetManager` is `nullptr` (not initialized) and, if so, create the instance.

   Example:
   ```cpp
   static AssetManager* GetInstance()
   {
       if (!_assetManager)
           _assetManager = new AssetManager();
       return _assetManager;
   }

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# AssetManager: AssetManager::Get()

## Purpose
The `AssetManager::Get` function implements the singleton pattern. It ensures only one instance of the `AssetManager` class exists and provides a global way to access it. The function dynamically creates the instance on the heap if it doesn't already exist.

---

## Behavior
### **Instance Creation**
- The function checks if `_assetManager` (a static member of `AssetManager`) is `nullptr`.
- If `_assetManager` is `nullptr`, a new instance of `AssetManager` is created using a `std::unique_ptr` and assigned to `_assetManager` via `std::move`.

### **Returning the Singleton**
- Once the instance exists, the function returns a reference to the object stored in `_assetManager` using `*` dereferencing.

---

## Key Concepts

### **What is a `std::unique_ptr`?**
- A **`std::unique_ptr`** is a smart pointer from **C++11** that provides exclusive ownership of a dynamically allocated object.
- Once a `std::unique_ptr` manages an object, no other pointer can manage the same object.
- When the `std::unique_ptr` is destroyed (e.g., goes out of scope), it automatically deletes the object it manages, ensuring no memory leaks.

### **Why Use `std::unique_ptr`?**
- To avoid manual memory management.
- To ensure proper cleanup of dynamically allocated objects.
- To prevent multiple ownership of the same object, which can lead to undefined behavior.

### **Why is the Instance Created on the Heap?**
- The singleton pattern requires an object to persist throughout the application's lifetime.
- By allocating the instance on the heap, it remains in memory even if the `Get` function goes out of scope.

---

## `std::move` in this Context
- **Purpose**: Transfers ownership of the newly created `std::unique_ptr` to `_assetManager`.
- **Why It's Needed**:
  - When creating a `std::unique_ptr` with `new AssetManager`, the temporary object (the newly created `std::unique_ptr`) cannot be copied because `std::unique_ptr` has **deleted copy constructors** and **copy assignment operators**. This is by design to prevent multiple `std::unique_ptr` instances from managing the same resource.
  - Instead, ownership must be **explicitly transferred** using `std::move`, which converts the temporary object into an **rvalue reference**. This indicates that the resource can be safely "moved" from the temporary `std::unique_ptr` to `_assetManager`.

### **Copying vs. Moving**
- **Copying**:
  - Duplicates the contents of one object into another.
  - For pointers, copying would result in two pointers managing the same resource, leading to issues like double deletion.
- **Moving**:
  - Transfers ownership of a resource from one object to another.
  - After the move, the original object is left in a valid but empty state (e.g., its pointer is set to `nullptr`).

### **How `std::move` Works Here**
1. The temporary `std::unique_ptr` created by `std::unique_ptr<AssetManager>{new AssetManager}` owns the `AssetManager` instance.
2. `std::move` transfers ownership of this `std::unique_ptr` to `_assetManager`.
3. The temporary `std::unique_ptr` no longer owns the `AssetManager` instance, ensuring no double ownership.

### **Advantages of Using `std::move`**
- Prevents accidental copying of the `std::unique_ptr`.
- Clearly conveys that ownership transfer is intentional and explicit.
- Ensures `std::unique_ptr`'s memory management guarantees are upheld.

### **Post-Move State**
After `std::move`, the temporary `std::unique_ptr` becomes empty. Attempting to dereference or use it would result in undefined behavior, but this isn't a concern here since the object is immediately assigned to `_assetManager`.

---

### **Example Without `std::move`**
If `std::move` were omitted, the following error would occur:
```plaintext
error: use of deleted function ‘std::unique_ptr(const std::unique_ptr&)’
```

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# AssetManager: LoadTexture()

## Purpose
The `LoadTexture` function loads and manages textures efficiently using a **singleton** `AssetManager` class. It ensures that each texture is loaded only once and reuses previously loaded textures when requested, avoiding redundant operations and saving memory.

---

## Behavior
### **Key Steps**
1. **Check for an Existing Texture**:
   - The function uses `_loadedTextureMap` (a `Dictionary` mapping file paths to `shared_ptr<sf::Texture>`) to check if a texture is already loaded.
   - The `find` method retrieves an iterator pointing to the element matching the `path` key.

2. **If Texture Is Found**:
   - If the key is found (`found != _loadedTextureMap.end()`), the function returns the corresponding `shared_ptr` using `found->second`.

3. **If Texture Is Not Found**:
   - A new `sf::Texture` object is created and wrapped in a `shared_ptr`.
   - The `loadFromFile` method attempts to load the texture from the given `path`.
     - **On Success**:
       - The texture is added to `_loadedTextureMap` with `path` as the key.
       - The `shared_ptr` is returned.
     - **On Failure**:
       - A `shared_ptr` containing `nullptr` is returned to indicate failure.

---

## Key Concepts
### **`std::unordered_map` (Alias: `Dictionary`)**
- **Purpose**: A hash-based container that stores key-value pairs and provides fast lookups.
- **Advantages Over a List**:
  - **O(1) Average Lookup Time**:
    - Unlike a list, where lookups require linear time (O(n)) since every element must be checked, an unordered map uses a hash table to find elements in constant average time.
  - **Key-Value Mapping**:
    - Each key (file path) maps to a unique value (`shared_ptr<sf::Texture>`), making it ideal for associating data like file paths with corresponding textures.

- **How It Works**:
  - Internally, `std::unordered_map` uses a hash function to compute a hash value for keys, determining where the value is stored. Collisions (keys with the same hash) are handled using techniques like chaining.

- **Why Not Use a List**:
  - A list would require iterating through each element to find a match, which is inefficient for large datasets.
  - Unlike a list, an unordered map allows direct access to elements using a key, making it significantly faster for lookups.

---

### **Key Methods in Use**
1. **`.find(key)`**:
   - Searches for an element with the given key (`path`) in the map.
   - Returns an iterator:
     - **If Found**: Points to the matching element.
     - **If Not Found**: Points to `end()` (past-the-end iterator).

2. **`.end()`**:
   - Represents an iterator pointing just past the last element in the map.
   - Used to check if a key was not found (`found == _loadedTextureMap.end()`).

3. **`.second`**:
   - Accesses the value associated with a key-value pair.
   - When iterating over or searching in the map, `found->second` retrieves the `shared_ptr<sf::Texture>` corresponding to the key.

---

### **Smart Pointers**
1. **`std::shared_ptr`**:
   - Used here to manage the lifetime of `sf::Texture` objects.
   - Allows multiple parts of the program to share ownership of the same texture without duplicating it.
   - Automatically deletes the texture when the last reference is destroyed, preventing memory leaks.

2. **Why Use `shared_ptr`?**
   - Multiple textures may be used simultaneously by different parts of the program.
   - By using `shared_ptr`, you avoid manually tracking and managing the texture's lifetime.

---

## Workflow Example
### Scenario: Loading a Texture for the First Time
1. The `path` key is not found in `_loadedTextureMap`.
2. A new `sf::Texture` is created and loaded from the file at `path`.
3. The texture is added to `_loadedTextureMap` with the `path` as its key.
4. The `shared_ptr` to the texture is returned.

### Scenario: Requesting an Already-Loaded Texture
1. The `path` key is found in `_loadedTextureMap`.
2. The function retrieves the `shared_ptr` stored in `found->second`.
3. The existing `shared_ptr` is returned without creating a new texture.

---

## Key Notes
- **Efficiency**:
  - Using a `Dictionary` ensures fast texture lookups and avoids redundant loading.
- **Memory Management**:
  - `shared_ptr` ensures textures are automatically cleaned up when no longer needed.
- **Error Handling**:
  - If a texture fails to load, the function returns `nullptr`, providing a clear way to signal errors.

---

## Example Output
```cpp
auto texture1 = AssetManager::Get().LoadTexture("player.png"); // Loads texture
auto texture2 = AssetManager::Get().LoadTexture("player.png"); // Reuses loaded texture
auto texture3 = AssetManager::Get().LoadTexture("invalid.png"); // Returns nullptr
```

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# AssetManager: CleanCycle()

## Purpose
The `CleanCycle` function ensures efficient memory management by cleaning up textures in `_loadedTextureMap` that are no longer being used. If a texture is exclusively owned by the `AssetManager` (i.e., its `shared_ptr` reference count is 1), it is removed from the map.

---

## Behavior
### **Key Steps**
1. **Iteration Through the Map**:
   - The function iterates over `_loadedTextureMap` using a `for` loop with an iterator (`auto iter`).

2. **Check for Exclusive Ownership**:
   - For each element, `iter->second.unique()` checks if the `shared_ptr` (pointed to by `iter->second`) is the only reference to the texture.

3. **Erase Unused Textures**:
   - If the texture is exclusively owned (`unique()` returns `true`), the iterator is updated by erasing the texture from `_loadedTextureMap` using `erase`.

4. **Advance the Iterator**:
   - If the texture is still in use (`unique()` returns `false`), the iterator is incremented with `++iter`.

---

## Key Concepts
### **`auto` in This Context**
- **Purpose**:
  - The `auto` keyword allows the compiler to deduce the type of the variable `iter` based on the type of `_loadedTextureMap.begin()`.
- **Deduced Type**:
  - Since `_loadedTextureMap` is a `Dictionary<std::string, shared_ptr<sf::Texture>>` (alias for `std::unordered_map`), the type of `iter` is deduced as:
    ```cpp
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>>::iterator
    ```
- **Why Use `auto`?**:
  - Improves code readability by avoiding lengthy type declarations.
  - Reduces the chance of errors when changing the container type (e.g., switching from `std::unordered_map` to another container).

---

### **`.second` in This Context**
- **Purpose**:
  - Accesses the value part of the key-value pair stored in `_loadedTextureMap`.
- **Details**:
  - Each element in a `std::unordered_map` is a `std::pair`, consisting of:
    ```cpp
    std::pair<const std::string, std::shared_ptr<sf::Texture>>
    ```
    - `.first`: The key (in this case, a `std::string` representing the texture path).
    - `.second`: The value (in this case, a `std::shared_ptr<sf::Texture>` pointing to the texture).
  - `iter->second` retrieves the `shared_ptr<sf::Texture>` associated with the current key.

---

### **`unique()` Method**
- **What It Does**:
  - `unique()` checks whether a `shared_ptr` is the sole owner of the resource it manages.
- **Returns**:
  - `true`: If the reference count is 1 (no other `shared_ptr` instances share ownership of the texture).
  - `false`: If the reference count is greater than 1 (other parts of the program are still using the texture).

---

### **`erase()` and Iterator Update**
- **`_loadedTextureMap.erase(iter)`**:
  - Removes the element pointed to by `iter` from `_loadedTextureMap`.
  - Returns an iterator pointing to the next element in the map.
- **Why Update `iter`?**:
  - After erasing an element, the iterator becomes invalid. Updating it ensures the loop continues safely.

---

## Workflow Example
### Scenario: Cleaning Up Unused Textures
1. `_loadedTextureMap` contains:
   ```cpp
   {
       {"texture1.png", shared_ptr<sf::Texture>}, // In use
       {"texture2.png", shared_ptr<sf::Texture>}, // Unique (unused)
       {"texture3.png", shared_ptr<sf::Texture>}  // In use
   }

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


# PhysicsSystem: Singleton Design and Protected Constructor

## Purpose of the Protected Constructor

The constructor for `PhysicsSystem` is **protected** to enforce the **singleton pattern**. This design prevents direct instantiation of the `PhysicsSystem` class outside the class itself or its friends, ensuring that the class can only be created and accessed through the static `Get()` function.

---

## How the `Get()` Function Works

```cpp
PhysicsSystem& PhysicsSystem::Get()
{
    if (!_physicsSystem)
        _physicsSystem = std::move(std::unique_ptr<PhysicsSystem>{new PhysicsSystem});

    return *_physicsSystem;
}
```

### Key Steps in `Get()`:
1. **Checks for Initialization**: 
   - If `_physicsSystem` is `nullptr`, it means the instance doesn't exist yet.
2. **Creates the Instance**:
   - A new `PhysicsSystem` object is allocated on the heap.
   - The constructor is called within the class, which is allowed due to the `protected` access specifier.
3. **Returns the Instance**:
   - The reference to the single `PhysicsSystem` object is returned, ensuring global access.

---

## Why Use a Protected Constructor?

1. **Prevents Direct Instantiation**:
   - Code like `PhysicsSystem ps;` or `PhysicsSystem* ps = new PhysicsSystem;` would result in a *compilation error* since the constructor isn't accessible outside the class.

2. **Encapsulates Creation**:
   - Ensures that all instances of `PhysicsSystem` are managed through the `Get()` function, maintaining strict control over how the instance is created and used.
   
   
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------   


# PhysicsSystem::AddListener()

This function integrates an `Actor` instance into the Box2D physics world by creating a `b2Body` based on the actor's properties. Here's a detailed breakdown of the code:

---

## Code Breakdown

### **1. Function Signature**

```cpp
b2Body* PhysicsSystem::AddListener(Actor* listener)
```

- **Purpose**: Adds an `Actor` to the physics system by creating a `b2Body` associated with it.
- **Returns**: A pointer to the created `b2Body`, or `nullptr` if the `Actor` is invalid.

---

### **2. Check for Pending Destruction**

```cpp
if (listener->IsPendingDestroy()) return nullptr;
```

- **Purpose**: Ensures the `Actor` is not marked for destruction before proceeding.
- **Effect**: Prevents adding invalid or soon-to-be-removed `Actors` to the physics world.

---

### **3. Create and Configure `b2BodyDef`**

```cpp
b2BodyDef bodyDef;
bodyDef.type = b2_dynamicBody;
bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(listener);
bodyDef.position.Set(listener->GetActorLocation().x * GetPhysicsScale(),
                     listener->GetActorLocation().y * GetPhysicsScale());
bodyDef.angle = DegreesToRadians(listener->GetActorRotation());
```

- **`b2BodyDef`**: Defines the properties of the physics body.
- **`bodyDef.type`**: Sets the body type to `b2_dynamicBody`, meaning the body can move and interact with forces.
- **`bodyDef.userData.pointer`**: Links the `Actor` to the `b2Body` for identification and interaction.
- **`bodyDef.position`**: Sets the initial position of the body, scaled to match the physics system's units.
- **`bodyDef.angle`**: Sets the initial rotation of the body in radians.

---

### **4. Create the `b2Body`**

```cpp
b2Body* body = _physicsWorld.CreateBody(&bodyDef);
```

- **Purpose**: Adds the configured body to the Box2D world.
- **Returns**: A pointer to the newly created `b2Body`.

---

### **5. Configure Collision Shape**

```cpp
b2PolygonShape shape;
auto bound = listener->GetActorGlobalBounds();
shape.SetAsBox(bound.width / 2.f * GetPhysicsScale(), bound.height / 2.f * GetPhysicsScale());
```

- **`b2PolygonShape`**: Represents a rectangular collision shape.
- **`GetActorGlobalBounds`**: Retrieves the actor's dimensions (width and height).
- **`SetAsBox`**: Configures the shape as a rectangle centered on the body.

---

### **6. Define `b2FixtureDef`**

```cpp
b2FixtureDef fixtureDef;
fixtureDef.shape = &shape;
fixtureDef.density = 1.0f;
fixtureDef.friction = 0.3f;
fixtureDef.isSensor = true;
```

- **`b2FixtureDef`**: Defines the physical properties of the shape.
  - **`shape`**: Links the collision shape to the fixture.
  - **`density`**: Determines the body's mass.
  - **`friction`**: Specifies how the body interacts with surfaces.
  - **`isSensor`**: Marks the body as a sensor, meaning it detects overlaps but does not collide.

---

### **7. Attach the Fixture**

```cpp
body->CreateFixture(&fixtureDef);
```

- **Purpose**: Adds the configured fixture to the `b2Body`, enabling collision detection.

---

### **8. Return the Created Body**

```cpp
return body;
```

- **Purpose**: Provides a reference to the created `b2Body` for further use or tracking.


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------   


# Understanding The Delegate System in `ly` Namespace

## Introduction
The `ly::Delegate` system is a robust implementation for event-driven programming in C++, designed to handle callbacks dynamically and manage listeners effectively. This enhanced system includes powerful features like weak pointer binding to avoid dangling references and automatic cleanup of expired listeners. This guide provides an in-depth explanation of its functionality and usage.

---

## Delegate Class
The `Delegate` class template is a generic solution for managing callbacks with any number of arguments (`Args...`).

### **Class Definition**
```cpp
#pragma once

#include <functional>
#include "framework/Core.h"

namespace ly {

    class Object;

    template<typename... Args>
    class Delegate {
    public:
        template<typename ClassName>
        void BindAction(std::weak_ptr<Object> object, void(ClassName::* callback)(Args...)) {
            std::function<bool(Args...)> callbackFunc = [object, callback](Args... args)->bool {
                if (!object.expired()) {
                    (static_cast<ClassName*>(object.lock().get())->*callback)(args...);
                    return true;
                }
                return false;
            };

            _callbacks.push_back(callbackFunc);
        }

        void BroadCast(Args... args) {
            for (auto iter = _callbacks.begin(); iter != _callbacks.end();) {
                if ((*iter)(args...))
                    ++iter;
                else
                    iter = _callbacks.erase(iter);
            }
        }

    private:
        List<std::function<bool(Args...)>> _callbacks;
    };
}
```

---

# Explanation of `BindAction` in the Delegate System

## Purpose of `BindAction`
The `BindAction` method is a fundamental component of the `Delegate` system, enabling dynamic registration of member functions to a delegate. This registration ensures:

1. When the delegate broadcasts an event, it invokes all registered member functions with the provided arguments.
2. The method uses **weak pointers** to avoid dangling references to destroyed objects.
3. It employs **lambdas** to encapsulate the binding and invocation logic into a single reusable construct.
4. The storage of callbacks in a flexible structure (`std::function`) allows for type-erased management of various callable objects.

---

## Detailed Syntax and Behavior

### **1. Template Parameters**
The `Delegate` class and `BindAction` method use variadic templates (`Args...`) to support callbacks with any number and type of arguments.

#### **Key Points About `Args...`:**
- **Variadic Templates:**
  - `Args...` allows the method to accept an arbitrary number of arguments with arbitrary types.
  - These arguments are passed to the bound member function when the delegate broadcasts an event.
- **Flexibility:**
  - This design makes `Delegate` applicable to a wide range of use cases, such as UI event handling, game logic, or physics callbacks.

---

### **2. The Weak Pointer Parameter (`std::weak_ptr<Object> object`)

#### **Why Use `std::weak_ptr`?**
- **Ownership and Lifetime:**
  - A `std::weak_ptr` does not contribute to the reference count of the object it references, unlike `std::shared_ptr`.
  - This ensures the delegate does not unintentionally extend the lifetime of the object.
- **Safe Access:**
  - Before accessing the object, the `weak_ptr` can be checked for validity using its `expired()` method.
  - To use the object, the `lock()` method creates a `shared_ptr`, ensuring safe access.

#### **Usage in `BindAction`:**
- The `object` parameter stores a weak reference to the object whose member function is being bound.
- At invocation, the lambda checks the validity of the weak pointer and safely accesses the object using `lock()`.

---

### **3. The Callback Parameter (`void(ClassName::* callback)(Args...)`)

#### **Understanding Member Function Pointers**
- **Syntax:**
  - A member function pointer has the syntax:
    ```cpp
    ReturnType(ClassName::* pointer)(Parameters...);
    ```
  - For example:
    ```cpp
    void (Spaceship_Base::*callback)(float);
    ```
    This is a pointer to a member function of `Spaceship_Base` that accepts a single `float` argument.

- **Invocation:**
  - Member function pointers require an instance of the class to be invoked:
    ```cpp
    (object.*callback)(arguments...);
    ```

---

### **4. Lambda Function Construction**
The `BindAction` method encapsulates the binding logic into a lambda function, which is stored in the `_callbacks` list.

#### **Lambda Structure:**
```cpp
std::function<bool(Args...)> callbackFunc = [object, callback](Args... args) -> bool {
    if (!object.expired()) {
        (static_cast<ClassName*>(object.lock().get())->*callback)(args...);
        return true;
    }
    return false;
};
```

#### **Breakdown of Lambda Logic:**
1. **Capture List (`[object, callback]`):**
   - Captures the weak pointer (`object`) and member function pointer (`callback`) by value.

2. **Object Expiry Check:**
   - `if (!object.expired())` ensures the object is still valid before invoking the callback.
   - Prevents accessing destroyed objects.

3. **Locking the Weak Pointer:**
   - `object.lock()` converts the `weak_ptr` into a `shared_ptr`.
   - This ensures safe access to the object during callback invocation.

4. **Static Casting:**
   - `static_cast<ClassName*>(object.lock().get())` casts the raw pointer obtained from the `shared_ptr` to the appropriate class type (`ClassName*`).
   - This is necessary because `Object` is a base class, and the actual type of the object is `ClassName` (or a derived type).

5. **Invoke the Callback:**
   - `(static_cast<ClassName*>(object.lock().get())->*callback)(args...)` dereferences the member function pointer and invokes it with the provided arguments.

6. **Return Value:**
   - Returns `true` if the callback executed successfully (i.e., the object was valid).
   - Returns `false` if the object was invalid (expired).

---

### **5. Storing the Lambda**
The lambda function is wrapped in a `std::function` and stored in the `_callbacks` list:
```cpp
_callbacks.push_back(callbackFunc);
```

#### **Why Use `std::function`:**
- **Type Erasure:**
  - `std::function` can store any callable object that matches the specified signature (`bool(Args...)`).
  - This allows the delegate to store and manage callbacks of varying types (lambdas, function pointers, `std::bind` expressions, etc.).
- **Uniform Interface:**
  - Simplifies the invocation of callbacks, as all stored objects conform to the same interface.

---

### **6. Advantages of This Design**

#### **1. Safety:**
- The use of `std::weak_ptr` ensures that callbacks tied to destroyed objects are not invoked, preventing undefined behavior or crashes.

#### **2. Flexibility:**
- The use of variadic templates (`Args...`) allows the delegate to support callbacks with any number and type of arguments.

#### **3. Encapsulation:**
- The lambda function encapsulates the complex logic for member function invocation into a reusable and easily storable format.

#### **4. Efficiency:**
- Expired callbacks are ignored during invocation, and no unnecessary strong references to objects are maintained.

---

## Conclusion
The `BindAction` method is a sophisticated mechanism for safely and efficiently binding member functions to delegates. By combining the power of weak pointers, lambdas, and type-erased storage, it ensures robust callback management while maintaining flexibility and safety. This makes it an essential tool for event-driven systems in modern C++ applications.


## Key Features and Benefits
1. **Weak Pointer Binding:**
   - Ensures no strong ownership of objects, preventing memory leaks or dangling references.

2. **Automatic Cleanup:**
   - Expired callbacks are removed during broadcasting, maintaining a clean and efficient callback list.

3. **Generic Design:**
   - Supports any number and type of arguments, making it highly versatile.

4. **Event Broadcasting:**
   - Triggers all bound callbacks safely and efficiently.

---

## Practical Example
### **Spaceship Health Event System**
The delegate system integrates seamlessly with game actors, like `Spaceship_Base`, to manage health-related events dynamically.

#### **Binding and Broadcasting**
```cpp
_healthComponent.BroadcastHealthChange.BindAction(GetWeakRef(), &Spaceship_Base::OnHealthChanged);
_healthComponent.BroadcastHealthChange.BroadCast(-25.0f, 75.0f, 100.0f);
```
- The first line binds the `OnHealthChanged` method to the health change event.
- The second line broadcasts a health reduction of `25.0f`, leaving the spaceship at `75.0f` health out of `100.0f`.

#### **Callback Method Implementation**
```cpp
void Spaceship_Base::OnHealthChanged(float amount, float currentHealth, float maxHealth) {
    std::cout << "Health changed by: " << amount 
              << ", Current: " << currentHealth 
              << ", Max: " << maxHealth << std::endl;
}
```
- Outputs details about the health change event.

---

## Conclusion
The updated `ly::Delegate` system is a powerful, generic tool for managing callbacks and events in a safe, efficient, and flexible manner. Its use of weak pointers and automatic cleanup ensures robust memory management, making it ideal for complex systems like games.

### **Key Takeaways**:
- **Flexibility:** Supports any number and type of arguments.
- **Safety:** Avoids dangling references with weak pointers.
- **Efficiency:** Automatically cleans up expired callbacks during broadcasts.

This system forms a core part of event-driven programming, promoting decoupled and maintainable codebases in game development or any application requiring dynamic callback management.



---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

# CODE FUNDEMENTALS     

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



# When to Forward Declare vs Include

This document provides guidelines on when to use forward declarations and when to include headers in your code.

---

## When to Use Forward Declaration

### Definition
- Forward declaration is the practice of declaring a class, struct, or function before its full definition is known.
- Example:
  ```cpp
  namespace ly {
      class Actor; // Forward declaration
  }
  ```

### Use Cases
1. **Pointers or References**:
   - If you only use a pointer or reference to a class in your header file, forward declare it to avoid unnecessary dependencies.
   - Example:
     ```cpp
     namespace ly {
         class Actor; // Forward declaration

         class Shooter {
         public:
             Shooter();

         protected:
             Shooter(Actor* actor); // Uses a pointer, forward declaration suffices
         };
     }
     ```

2. **Reduce Compilation Time**:
   - Forward declarations avoid including unnecessary headers in your header files, reducing dependencies and speeding up compilation.

3. **Break Cyclic Dependencies**:
   - When two classes depend on each other, forward declaration can help avoid a cyclic dependency.

### Caveats
- Forward declarations only work if you don’t need to know the size or members of the class.
- If you need to call methods or access members of the class, you must include its full definition.

---

## When to Include Headers

### Definition
- Including headers brings the full definition of a class, struct, or function into scope.
- Example:
  ```cpp
  #include "Actor.h"
  ```

### Use Cases
1. **Accessing Class Members**:
   - If you need to access members or call methods of a class, you must include its header.
   - Example:
     ```cpp
     namespace ly {
         #include "Actor.h" // Include needed to use Actor methods

         class Shooter {
         public:
             void InteractWithActor() {
                 Actor actor;
                 actor.DoSomething(); // Requires full definition
             }
         };
     }
     ```

2. **Declaring Non-Pointer/Reference Members**:
   - If your class contains an instance (not a pointer or reference) of another class, you must include its header to know its size.
   - Example:
     ```cpp
     namespace ly {
         #include "Actor.h"

         class Shooter {
         private:
             Actor actorInstance; // Requires full definition for size
         };
     }
     ```

3. **Templates**:
   - If your code involves templates, the full definition must be available in the translation unit where the template is instantiated.
   - Example:
     ```cpp
     #include <vector>
     #include "Actor.h"

     std::vector<Actor> actors; // Requires full definition of Actor
     ```

4. **Inline Methods**:
   - Inline methods in a class definition that use another class’s methods or members require the full definition.
   - Example:
     ```cpp
     namespace ly {
         #include "Actor.h"

         class Shooter {
         public:
             void Interact() {
                 Actor actor;
                 actor.DoSomething(); // Full definition needed
             }
         };
     }
     ```

---

## Best Practices

1. **Use Forward Declarations Whenever Possible**:
   - Place forward declarations in headers to reduce dependencies and speed up compilation.

2. **Include Headers in Implementation Files**:
   - In `.cpp` files, include the headers needed to fully define and use the classes.
   - Example:
     ```cpp
     #include "Shooter.h"
     #include "Actor.h"

     namespace ly {
         Shooter::Shooter(Actor* actor) {
             // Implementation here
         }
     }
     ```

3. **Avoid Including Unnecessary Headers**:
   - Only include headers when you need full definitions.
   - Prefer forward declarations in headers whenever possible.

4. **Use Include Guards or `#pragma once`**:
   - Protect your headers from multiple inclusions to prevent redefinition errors.
   - Example:
     ```cpp
     #pragma once

     namespace ly {
         class Actor;

         class Shooter {
             // Shooter definition
         };
     }
     ```

---

## Summary Table

| Situation                                      | Forward Declare | Include |
|-----------------------------------------------|-----------------|---------|
| Use of pointers or references                 | Yes             | No      |
| Access to class members or methods            | No              | Yes     |
| Declaring non-pointer/reference members       | No              | Yes     |
| Reducing compilation dependencies             | Yes             | No      |
| Templates                                     | No              | Yes     |
| Cyclic dependencies                           | Yes             | No      |


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


# Lambda Functions in C++

## Introduction
Lambda functions are a concise way to define inline functions directly within your code. They are commonly used for tasks such as callbacks, custom sort operations, or small operations where creating a separate function would be overkill. 
This lesson will cover their syntax, use cases, and examples to deepen your understanding.

---

## Syntax
A lambda function in C++ follows this structure:

```cpp
[ capture_list ] ( parameters ) -> return_type {
    // function body
};
```

### Components
1. **Capture List (`[]`)**: Specifies which variables from the surrounding scope the lambda captures and how it captures them (by value or reference).
2. **Parameters (`()`):** Optional; the arguments passed to the lambda function.
3. **Return Type (`-> type`)**: Optional; if omitted, the return type is deduced automatically.
4. **Function Body (`{}`):** The code that the lambda executes.

---

## Example
Here is a simple example to illustrate how to define and use a lambda function:

```cpp
#include <iostream>
#define LOG(msg, var) std::cout << msg << var << std::endl

int main() {
    // Defining a lambda function
    auto func = [](float var) {
        LOG("The value of var is ", var);
    };

    // Calling the lambda
    func(3.14f);

    return 0;
}
```

### Explanation:
1. **Capture List:** Empty (`[]`), meaning the lambda does not capture any variables from the surrounding scope.
2. **Parameters:** One parameter of type `float` named `var`.
3. **Return Type:** Not explicitly specified; deduced as `void` since the lambda does not return a value.
4. **Function Body:** Logs the value of `var` using a macro.

---

## Advanced Usage

### Capturing Variables
You can capture variables from the surrounding scope by value or by reference:

#### By Value
```cpp
int a = 10;
auto func = [a]() {
    std::cout << "Captured by value: " << a << std::endl;
};
func();
```

#### By Reference
```cpp
int a = 10;
auto func = [&a]() {
    a++;
    std::cout << "Captured by reference: " << a << std::endl;
};
func();
```

### Generic Lambdas
Lambdas can use `auto` in the parameter list to support generic operations:

```cpp
auto func = [](auto x, auto y) {
    return x + y;
};

std::cout << func(3, 4) << std::endl; // Outputs: 7
std::cout << func(3.5, 4.5) << std::endl; // Outputs: 8.0
```

### Stateful Lambdas
Lambdas can hold state when variables are captured by value and marked `mutable`:

```cpp
int counter = 0;
auto increment = [counter]() mutable {
    return ++counter;
};

std::cout << increment() << std::endl; // Outputs: 1
std::cout << increment() << std::endl; // Outputs: 2
```

---

## Best Practices
- Use lambdas for short, inline operations.
- Avoid overly complex lambdas; use named functions if the logic is intricate.
- Be mindful of variable capture to avoid unintended side effects.

---

## Exercises

1. Define a lambda that takes two integers and returns their product.
2. Create a lambda that captures a variable by reference and modifies it.
3. Write a generic lambda that concatenates two strings.

---

## Conclusion
Lambda functions are a powerful feature in C++, allowing for flexible and concise code. By mastering their syntax and use cases, you can write cleaner and more efficient programs.
