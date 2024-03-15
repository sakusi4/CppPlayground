#pragma once
  
#include <mutex>
#include <memory>

template <typename T>
class SingletonTemplate
{
protected:
	static T * instance;
	static std::mutex staticSingletonMutex;
	static std::once_flag onceFlag;
protected:
	SingletonTemplate(){}
	virtual ~SingletonTemplate(){}
public:
	static T * getInstance()
	{
		call_once(onceFlag, []()
			{
				instance = new T();
			}
		);

		return instance;
	};
	
	static void destroyInstance()
	{
		std::unique_lock<std::mutex> lock(staticSingletonMutex);
		if (instance)
		{
			delete instance;
			instance = nullptr;
		}
		lock.unlock();
	};
};
  
template<typename T> T* SingletonTemplate<T>::instance = nullptr;
template<typename T> std::mutex SingletonTemplate<T>::staticSingletonMutex;
template<typename T> std::once_flag SingletonTemplate<T>::onceFlag;
