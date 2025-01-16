#include "EntryPoint.h"
#include "framework/Application.h"

int main()
{
	ly::Application* app = GetApplication();																				// creates a new GameApplication object. The GameApplication object is treated as an Application due to inheritance.
	app->Run();																												// Why use pointers here? Enables polymorphism, allowing the base class pointer (Application*) to invoke overridden methods in the derived class (GameApplication).

	delete app;
}