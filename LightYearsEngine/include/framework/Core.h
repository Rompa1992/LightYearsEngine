#pragma once

#include <stdio.h>
#include <map>
#include <memory>
#include <unordered_map>
#include <unordered_set>

namespace ly
{
	template<typename T>
	using unique_ptr = std::unique_ptr<T>;		  																			// The using keyword is a modern replacement for typedef, introduced in C++11.

	template<typename T>
	using shared_ptr = std::shared_ptr<T>;

	template<typename T>
	using weak_ptr = std::weak_ptr<T>;

	template<typename T>
	using List = std::vector<T>;

	template<typename keyType, typename valType, typename predicate = std::less<keyType>>									// predicate "less" = Ascending order (1 -> 2 -> 3), predicate "greater" = Decending order (3 -> 2 -> 1)
	using Map = std::map<keyType, valType, predicate>;

	template<typename keyType, typename valType, typename hasher = std::hash<keyType>>										// hash: A function or object that generates a unique hash value for a given key.
	using Dictionary = std::unordered_map<keyType, valType, hasher>;

	template<typename T>										
	using Set = std::unordered_set<T>;


#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
/**
 * LOG(M, ...) Macro:
 * - This is a variadic (variable number of arguments) macro used for logging formatted messages to the console.
 *
 * Components:
 * 1. `M`: The first parameter, which represents the main format string (like in printf).
 * 2. `...`: The variadic arguments, allowing for additional values to be passed and formatted
 *    in the message.
 *
 * Behavior:
 * - Expands to a call to `printf` with the following format:
 *   - `M "\n"`: The format string `M` is concatenated with a newline character `\n` to ensure
 *     the log message ends with a newline.
 *   - `##__VA_ARGS__`: Inserts the variadic arguments passed to the macro, if any.
 *     - If no arguments are passed, `##__VA_ARGS__` ensures there is no trailing comma error.
 *
 * Example Usage:
 * LOG("Hello, %s!", "World");
 * - Expands to: printf("Hello, %s!\n", "World");
 * - Output: Hello, World!
 *
 * Notes:
 * - Useful for lightweight logging in debug or development builds.
 * - Ensure the format string `M` and arguments match, as with `printf`, to avoid runtime errors.
 */


}