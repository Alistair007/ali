#pragma once
#include <thread>

//template<typename _Func, typename _Args>
//class promise
//{
//public:
//	promise(_Func(*Func), _Args&&... Args_) {
//		Func(Args_...);
//	}
//	~promise();
//
//private:
//
//};
//
//template<typename _Func>
//class async
//{
//public:
//	async(_Func&& Func_) {
//		Func = _Func;
//	}
//	
//	template<typename _Args>
//	promise<_Func, _Args> operator()(_Args&&... Args_) {
//		return promise<_Func, _Args>(Args_);
//	}
//private:
//	_Func Func;
//};

//#include <Windows.h>
//#include <condition_variable>
//#include <type_traits>
//#include <functional>
//
//#define _ALI_BEGIN namespace ali{
//#define _ALI_END }
//
//_ALI_BEGIN
//template<typename T>
//class promise
//{
//public:
//	promise(std::function<T()> func) {
//		thread = new std::thread([&] {
//			value = func();
//			done = true;
//			});
//	}
//	//~promise();
//	T await() {
//		thread->join();
//		return value;
//	}
//	bool finished() {
//		return done;
//	}
//	T get() {
//		if (done)
//			return value;
//		else throw("Didn't finish the task!");
//	}
//private:
//	std::thread* thread = nullptr;
//	bool done = false;
//	T value;
//};
//
//
//template<typename T>
//class async
//{
//public:
//	template<typename Func, typename... Args>
//	async(Func&& func, Args&&... args) {
//		// Use std::bind to create a callable object from the provided function and arguments
//		auto bound_func = std::bind(std::forward<Func>(func), std::forward<Args>(args)...);
//
//		this->func = bound_func;
//	}
//
//	promise<T> operator()() {
//		return promise<T>(func);
//	}
//
//private:
//	std::function<T()> func;
//};
//_ALI_END
///*
//	async(T(*func)()) {
//		thread = new std::thread([&] {
//			value = func();
//			done = true;
//			});
//	}
//	async(T(*func)(), void(*then)(T)) {
//		thread = new std::thread([&] {
//			value = func();
//			then(T);
//			done = true;
//			});
//	}
//	async(T(*func)(), size_t wait) {
//		thread = new std::thread([&] {
//			Sleep(wait);
//			value = func();
//			done = true;
//			});
//	}
//	async(T(*func)(), void(*then)(T), size_t wait) {
//		thread = new std::thread([&] {
//			Sleep(wait);
//			value = func();
//			then(value);
//			done = true;
//			});
//	}
//	bool await() {
//		bool ret = !thread->joinable();
//		thread->join();
//		return ret;
//	}
//	T get() {
//		thread->join();
//		return value;
//	}
//	 */