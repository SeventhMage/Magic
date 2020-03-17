#ifndef _MAGIC_COMMON_BASE_C_SINGLETON_H_INC_
#define _MAGIC_COMMON_BASE_C_SINGLETON_H_INC_

namespace magic
{
template <typename T>
class CSingleton
{
public:
	static T *NewInstance()
	{
		if (!_instance)
			_instance = new T;
		return _instance;
	}

	static void DeleteInstance()
	{
		if (_instance)
		{
			delete _instance;
			_instance = 0;
		}
	}

	static T *Instance()
	{
		if (_instance)
			return _instance;
		else
			return NewInstance();
	}

protected:
	CSingleton<T>() {}
	CSingleton<T>(const CSingleton<T> &) {}
	CSingleton<T> &operator=(const CSingleton<T> &) { return *this; }
	virtual ~CSingleton<T>() {}

	static T *_instance;
};

template <typename T>
T *CSingleton<T>::_instance = 0;
} // namespace magic

#endif
