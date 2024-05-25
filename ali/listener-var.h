#pragma once
#include <type_traits>
#define _ALI_BEGIN namespace ali{
#define _ALI_END }

_ALI_BEGIN
template<typename T>
class listener_var
{
public:
	listener_var(void(*onUpdate)(T), T value = NULL) {
		data = value;
		onChange = onUpdate;
	}
	void silentUpdate(T update)
	{
		data = update;
	}
	void operator=(T value)
	{
		data = value;
		onChange(value);
	}
	operator T() const {
		return data;
	}
	void (*onChange)(T);
private:
	T data;
};
template<typename T>
class listener_ptr {
public:
	listener_ptr(void(*onUpdate)(T), T value = NULL) {
		data = value;
		onChange = onUpdate;
	}
	void silentUpdate(T update) {
		data = update;
	}
	void (*onChange)(T);
private:
	T data;
};
_ALI_END