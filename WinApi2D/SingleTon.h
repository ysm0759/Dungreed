#pragma once

//========================================
//## 디자인 패턴 SingleTon				##
//========================================
/*
	싱글톤 패턴은 static member로 하나의 인스턴스만
	생성된다. 프로그램 안에서 전역적으로 접근이 가능하다.

	전역변수를 선언해도 하나의 인스턴스를 유지할수 있긴 하지만
	싱글톤패턴을 사용하면 클래스 자신이 자기의 유일한 인스턴스로
	접근하는 방법을 캡슐화 하여 관리 할수 있다.
	또한 상속, 객체생성 및 소멸, 인스턴스 개수 제어 등등등..
	활용에 유리하다.

	자기 스스로가 자기의 유일한 인스턴스로 접근하는
	방법을 자체적으로 관리하는 것이 좋다.
	이녀석은 다른 인스턴스가 생성되지 않도록 처리할수 있고
	접근 방법 또한 제한을 둘수 있다.
*/

// 싱글톤 매크로 정의
#define SINGLETON(type)								\
													\
public:												\
	static type* getInst()							\
	{												\
		static type _instance;						\
		return &_instance;							\
	}												\
private:											\
	type();											\
	~type();										


// 싱글톤 클래스 정의
template <typename T>
class SingleTon
{
protected:
	//싱글톤 인스턴스 선언하기
	static T* _instance;

	SingleTon() {};
	~SingleTon() {};

public:
	static T* getInst()
	{
		//싱글톤 객체가 없으면 새로 만들어 전달.
		if (nullptr == _instance)
			_instance = new T;

		return _instance;
	}
	void release()
	{
		//싱글톤 있으면 해제
		if (nullptr != _instance)
		{
			delete _instance;
			_instance = nullptr;
		}
	}

};

//싱글톤 인스턴스 선언
template <typename T>
T* SingleTon<T>::_instance = nullptr;
