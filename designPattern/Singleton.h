#pragma once


/*
单例模式+模板
不使用锁，此处基本不需要担心死锁等问题
使用方法，子类只需要进行继承即可
https://blog.csdn.net/xfgryujk/article/details/69486685
https://blog.csdn.net/yaolong336/article/details/54288742
*/

template <typename T>
class Singleton
{
public:
	static T* getInstance()
	{
		if (m_pInstance == NULL)   //判断是否第一次调用
			m_pInstance = new T();		
		return m_pInstance;
	}


protected:
	//使继承者无法public构造函数和析构函数
	Singleton(){}
	~Singleton(){}

private:
	static T* m_pInstance;
	//禁止拷贝构造和赋值运算符. The only way is getInstance()
	Singleton(const Singleton& src){}
	Singleton &operator=(const Singleton& src){};
	class Garbo   //它的唯一工作就是在析构函数中析构Singleton的实例，所以private
	{
	public:
		~Garbo()
		{
			if (Singleton::m_pInstance)
			{
				delete Singleton::m_pInstance;
				Singleton::m_pInstance = NULL;
			}
		}
	};
	static Garbo garbo;  //定义一个静态成员变量，程序结束时，系统会自动调用它的析构函数，我们不需要访问这个变量，所以不需要初始化


};
template <class T>
T* Singleton<T>::m_pInstance = NULL; //必须初始化这个静态成员，初始化的过程中会分配内存，否则无法访问


/*
为了避免当子类的构造函数为private时，父类不能构建的问题，故使用以下
声明在子类中即可
*/
#define  DECL_SINGLETON(T) friend class Singleton<T>
