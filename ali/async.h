#pragma once
#include <type_traits>
#include <thread>
#include <stdexcept>
#include <iostream>

#define _ALI_BEGIN namespace ali{
#define _ALI_END }

_ALI_BEGIN

template <typename T>
struct return_type;

template <typename R, typename... Args>
struct return_type<R(Args...)> {
	using value = R;
};

template <typename R, typename... Args>
struct return_type<R(*)(Args...)> {
	using value = R;
};

template<typename _Ret>
class promise {
public:
	promise(std::thread* t, bool* f, _Ret* rv) {
		thread = t;
		b_finished = f;
		t_return = rv;
	}

	~promise() {
		if (!(*b_finished))
			thread->join();
		delete thread;
		delete b_finished;
		delete t_return;
	}

	bool finished() {
		return *b_finished;
	}

	_Ret await() {
		thread->join();
		return *t_return;
	}

	_Ret get() {
		if (!(*b_finished)) throw new std::runtime_error("The task hasn't finished yet!");
		return *t_return;
	}
private:
	std::thread* thread;
	bool* b_finished;
	_Ret* t_return;
};

template<typename _Func>
class async {
public:
	using Return = return_type<_Func>::value;

	async(_Func f) {
		func = f;
	}

	template<typename... _Args>
	promise<Return> operator()(_Args... args) {
		bool* f = new bool(false);
		Return* rv = new Return(0);
		std::thread* t = new std::thread([](_Func(*fun), _Args... a, bool* finished, Return* retVal) {
			*retVal = fun(a...);
			*finished = true;
			}, func, args..., f, rv);
		return promise<Return>(t, f, rv);
	}
private:
	_Func(*func);
};

_ALI_END