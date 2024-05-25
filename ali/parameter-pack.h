#pragma once
#include <iostream>

template<typename Func, typename T, typename... Args>
void for_each(Func&& func, T&& first, Args&&... args) {
    // Process the first parameter using the provided callable
    func(std::forward<T>(first));

    // Recursively call for_each() for the remaining parameters
    for_each(func, std::forward<Func>(func), std::forward<Args>(args)...);
}