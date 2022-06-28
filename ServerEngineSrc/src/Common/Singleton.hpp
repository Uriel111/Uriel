#pragma once
#include <assert.h>
template <typename T> class Singleton {
protected:
	Singleton();

public:
	static T &Instance(){
		static T instance_;
		return instance_;
	}
	~Singleton() {}
};