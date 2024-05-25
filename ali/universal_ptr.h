#pragma once
#include <iostream>

class universal_ptr {
private:
    void* ptr;

public:
    universal_ptr(void* p) : ptr(p) {}

    template <typename T>
    T* get() const {
        return static_cast<T*>(ptr);
    }

    template<typename T>
    T getv() const {
        return *static_cast<T*>(ptr);
    }
};

class smart_universal_ptr {
private:
    void* ptr;

public:
    smart_universal_ptr(void* p) : ptr(p) {}

    ~smart_universal_ptr() { delete ptr; }

    template<typename T>
    T getv() const {
        return *static_cast<T*>(ptr);
    }

    template <typename T>
    T* get() const {
        return static_cast<T*>(ptr);
    }
};