#pragma once
#include <type_traits>
#include <thread>
#include <stdexcept>
#include <iostream>

#define _ALI_BEGIN namespace ali{
#define _ALI_END }
#define _ALL_ALI true

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
    promise(const promise& other) {
        t_return = new _Ret(*other.t_return);
        thread = other.thread ? new std::thread(std::move(*other.thread)) : nullptr;
    }

    promise& operator=(const promise& other) {
        if (this == &other) return *this;

        if (thread && thread->joinable()) {
            thread->join();
        }
        delete thread;
        delete t_return;

        t_return = new _Ret(*other.t_return);
        thread = other.thread ? new std::thread(std::move(*other.thread)) : nullptr;

        return *this;
    }

    promise(std::thread* t, _Ret* rv) : thread(t), t_return(rv) {}

    ~promise() {
        if (thread->joinable())
            thread->join();
        delete thread;
        delete t_return;
    }

    bool finished() {
        return !thread->joinable();
    }

    _Ret await() {
        if (thread->joinable())
            thread->join();
        return *t_return;
    }

    _Ret get() {
        if (thread->joinable()) throw new std::runtime_error("The task hasn't finished yet!");
        return *t_return;
    }

    template<typename _Func,
        std::enable_if_t<!std::is_same_v<typename return_type<_Func>::value, void>, bool> = true> // I am so good at this
    auto then(_Func func) -> promise<typename return_type<_Func>::value> {
        using NextReturn = typename return_type<_Func>::value;
        NextReturn* nextRet = new NextReturn();

        std::thread* nextThread = new std::thread([this, func, nextRet]() {
            this->await();
            *nextRet = func(this->get());
            });

        return promise<NextReturn>(nextThread, nextRet);
    }

    template<typename _Func,
        std::enable_if_t<std::is_same_v<typename return_type<_Func>::value, void>, bool> = true>
    auto then(_Func func) -> promise<void> {
        using NextReturn = void;

        std::thread* nextThread = new std::thread([this, func]() {
            this->await();
            func(this->get());
            });

        return promise<NextReturn>(nextThread, nullptr);
    }

private:
    std::thread* thread;
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
		Return* rv = new Return(0);
		std::thread* t = new std::thread([](_Func(*fun), _Args... a, Return* retVal) {
			*retVal = fun(a...);
			}, func, args..., rv);
		return promise<Return>(t, rv);
	}
private:
	_Func(*func);
};

template<>
class promise<void> {
public:
	promise(std::thread* t) {
		thread = t;
	}

	~promise() {
		if (thread->joinable())
			thread->join();
		delete thread;
	}

	bool finished() {
		return !thread->joinable();
	}

	void await() {
		if (thread->joinable())
			thread->join();
	}

    template<typename _Func,
        std::enable_if_t<!std::is_same_v<typename return_type<_Func>::value, void>, bool> = true>
    auto then(_Func func) -> promise<typename return_type<_Func>::value> {
        using NextReturn = typename return_type<_Func>::value;
        NextReturn* nextRet = new NextReturn();

        std::thread* nextThread = new std::thread([this, func, nextRet]() {
            this->await();
            *nextRet = func();
            });

        return promise<NextReturn>(nextThread, nextRet);
    }

    template<typename _Func,
        std::enable_if_t<std::is_same_v<typename return_type<_Func>::value, void>, bool> = true>
    auto then(_Func func) -> promise<void> {
        using NextReturn = void;

        std::thread* nextThread = new std::thread([this, func]() {
            this->await();
            func();
            });

        return promise<NextReturn>(nextThread);
    }
private:
	std::thread* thread;
};

template<typename... _Args>
class async<void(_Args...)> {
public:
	using Return = void;

	async(void(*f)(_Args...)) : func(f) {}

	promise<Return> operator()(_Args... args) {
		std::thread* t = new std::thread([args...](void(*func)(_Args...)) {
			func(args...);
			}, func);
		return promise<Return>(t);
	}

private:
	void(*func)(_Args...);
};

_ALI_END