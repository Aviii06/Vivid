#pragma once
#include <sys/fcntl.h>

namespace Vivid
{
	template <class T>
	class Singleton
	{
	public:
		static T* GetInstance() {
			if ( p == nullptr ) p = new T();
			return p;
		}
	protected:
		Singleton() = default;

		Singleton(Singleton const &) = delete;
		Singleton &operator=(const Singleton &) = delete;

	private:
		static T *p;
	};

	template <class T>
	T* Singleton<T>::p = nullptr;
}
