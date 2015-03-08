/**
@file   LuaWrapperProxy.hpp
@brief  To get all of parameters.
*/


#ifndef _LUAPP_WRAPPER_PROXY_HPP_
#define _LUAPP_WRAPPER_PROXY_HPP_


#include "Lua.hpp"


namespace lua{
namespace wrapper{


//------------------------------------------------------------

struct Proxy
{
	virtual ~Proxy(){}
	virtual int Do(lua::Handle)=0;
};

//------------------------------------------------------------


template<typename R>
struct ProxyReturn : public Proxy
{
	ProxyReturn(){/*warning message*/}
};

template<>
struct ProxyReturn<void> : public Proxy
{
};

template<>
struct ProxyReturn<lua::Int> : public Proxy
{
	void ReturnValue(lua::Handle L,lua::Int num)
	{
		lua::PushInteger(L,num);
	}
};

template<>
struct ProxyReturn<lua::Num> : public Proxy
{
	void ReturnValue(lua::Handle L,lua::Num num)
	{
		lua::PushNumber(L,num);
	}
};

template<>
struct ProxyReturn<lua::Str> : public Proxy
{
	void ReturnValue(lua::Handle L,lua::Str num)
	{
		lua::PushString(L,num.c_str());
	}
};


//------------------------------------------------------------

template<typename R>
struct Proxy00 : public ProxyReturn<R>
{
	typedef R(*Func)();
	Proxy00(){}
	Proxy00(Func fn):func00(fn){}

	Func    func00;

	int Do(lua::Handle L)
	{
		this->ReturnValue(L,func00());
		return (int)1;
	}
};

template<>
struct Proxy00<void> : public ProxyReturn<void>
{
	typedef void R;
	typedef R(*Func)();
	Proxy00(){}
	Proxy00(Func fn):func00(fn){}

	Func    func00;

	int Do(lua::Handle)
	{
		func00();
		return (int)1;
	}
};


//------------------------------------------------------------

template<typename R,typename A1>
struct Proxy01 : public ProxyReturn<R>
{
	typedef R (*Func)(A1);
	Proxy01(Func){/*warning message*/}
};

template<typename R>
struct Proxy01<R,lua::Int> : public ProxyReturn<R>
{
	typedef lua::Int A1;
	typedef R (*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckInteger(L, 1);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,fn(p1));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1),A1 p1)
	{
		fn(p1);
	}

	int Do(lua::Handle L)
	{
		GetValue01(L);
		DoFunction(L,func01,p1);
		return (int)1;
	}
};

template<typename R>
struct Proxy01<R,lua::Num> : public ProxyReturn<R>
{
	typedef lua::Num A1;
	typedef R (*Func)(lua::Num);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckNumber(L, 1);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,fn(p1));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1),A1 p1)
	{
		fn(p1);
	}

	int Do(lua::Handle L)
	{
		GetValue01(L);
		DoFunction(L,func01,p1);
		return (int)1;
	}
};

template<typename R>
struct Proxy01<R,lua::Str> : public ProxyReturn<R>
{
	typedef lua::Str A1;
	typedef R (*Func)(lua::Str);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckString(L, 1);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,fn(p1));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1),A1 p1)
	{
		fn(p1);
	}

	int Do(lua::Handle L)
	{
		GetValue01(L);
		DoFunction(L,func01,p1);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2>
struct Proxy02 : public Proxy01<R,A1>
{
	typedef R (*Func)(A1,A2);
	Proxy02(Func){/*warning message*/}
};

template<typename R,typename A1>
struct Proxy02<R,A1,lua::Int> : public Proxy01<R,A1>
{
	typedef lua::Int A2;
	typedef R (*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckInteger(L, 2);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,fn(p1,p2));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2),A1 p1,A2 p2)
	{
		fn(p1,p2);
	}

	int Do(lua::Handle L)
	{
		GetValue02(L);
		DoFunction(L,func02,this->p1,p2);
		return (int)1;
	}
};

template<typename R,typename A1>
struct Proxy02<R,A1,lua::Num> : public Proxy01<R,A1>
{
	typedef lua::Num A2;
	typedef R(*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckNumber(L, 2);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,fn(p1,p2));
	}

	template<typename tagT>
	void DoFunction(lua::Handle  ,void (*fn)(A1,A2),A1 p1,A2 p2)
	{
		fn(p1,p2);
	}

	int Do(lua::Handle L)
	{
		GetValue02(L);
		DoFunction(L,func02,this->p1,p2);
		return (int)1;
	}
};

template<typename R,typename A1>
struct Proxy02<R,A1,lua::Str> : public Proxy01<R,A1>
{
	typedef lua::Str A2;
	typedef R(*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckString(L, 2);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,fn(p1,p2));
	}

	template<typename tagT>
	void DoFunction(lua::Handle  ,void (*fn)(A1,A2),A1 p1,A2 p2)
	{
		fn(p1,p2);
	}

	int Do(lua::Handle L)
	{
		GetValue02(L);
		DoFunction(L,func02,this->p1,p2);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2,typename A3>
struct Proxy03 : public Proxy02<R,A1,A2>
{
	typedef R (*Func)(A1,A2,A3);
	Proxy03(Func){/*warning message*/}
};

template<typename R,typename A1,typename A2>
struct Proxy03<R,A1,A2,lua::Int> : public Proxy02<R,A1,A2>
{
	typedef lua::Int A3;
	typedef R (*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func03(fn){}
	A3      p3;
	Func    func03;

	void GetValue03(lua::Handle L)
	{
		this->GetValue02(L);
		p3 = lua::CheckInteger(L, 3);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		this->ReturnValue(L,fn(p1,p2,p3));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		fn(p1,p2,p3);
	}

	int Do(lua::Handle L)
	{
		GetValue03(L);
		DoFunction(L,func03,this->p1,this->p2,p3);
		return (int)1;
	}
};

template<typename R,typename A1,typename A2>
struct Proxy03<R,A1,A2,lua::Num> : public Proxy02<R,A1,A2>
{
	typedef lua::Num A3;
	typedef R(*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func03(fn){}
	A3      p3;
	Func    func03;

	void GetValue03(lua::Handle L)
	{
		this->GetValue02(L);
		p3 = lua::CheckNumber(L, 3);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		this->ReturnValue(L,fn(p1,p2,p3));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		fn(p1,p2,p3);
	}

	int Do(lua::Handle L)
	{
		GetValue03(L);
		DoFunction(L,func03,this->p1,this->p2,p3);
		return (int)1;
	}
};

template<typename R,typename A1,typename A2>
struct Proxy03<R,A1,A2,lua::Str> : public Proxy02<R,A1,A2>
{
	typedef lua::Str A3;
	typedef R(*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func03(fn){}
	A3      p3;
	Func    func03;

	void GetValue03(lua::Handle L)
	{
		this->GetValue02(L);
		p3 = lua::CheckString(L, 3);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		this->ReturnValue(L,fn(p1,p2,p3));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		fn(p1,p2,p3);
	}

	int Do(lua::Handle L)
	{
		GetValue03(L);
		DoFunction(L,func03,this->p1,this->p2,p3);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy04 : public Proxy03<R,A1,A2,A3>
{
	typedef R (*Func)(A1,A2,A3,A4);
	Proxy04(Func){/*warning message*/}
};

template<typename R,typename A1,typename A2,typename A3>
struct Proxy04<R,A1,A2,A3,lua::Int> : public Proxy03<R,A1,A2,A3>
{
	typedef lua::Int A4;
	typedef R (*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func04(fn){}
	A4      p4;
	Func    func04;

	void GetValue04(lua::Handle L)
	{
		this->GetValue03(L);
		p4 = lua::CheckInteger(L, 4);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		this->ReturnValue(L,fn(p1,p2,p3,p4));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		fn(p1,p2,p3,p4);
	}

	int Do(lua::Handle L)
	{
		GetValue04(L);
		DoFunction(L,func04,this->p1,this->p2,this->p3,p4);
		return (int)1;
	}
};

template<typename R,typename A1,typename A2,typename A3>
struct Proxy04<R,A1,A2,A3,lua::Num> : public Proxy03<R,A1,A2,A3>
{
	typedef lua::Num A4;
	typedef R (*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func04(fn){}
	A4      p4;
	Func    func04;

	void GetValue04(lua::Handle L)
	{
		this->GetValue03(L);
		p4 = lua::CheckNumber(L, 4);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		this->ReturnValue(L,fn(p1,p2,p3,p4));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		fn(p1,p2,p3,p4);
	}

	int Do(lua::Handle L)
	{
		GetValue04(L);
		DoFunction(L,func04,this->p1,this->p2,this->p3,p4);
		return (int)1;
	}
};

template<typename R,typename A1,typename A2,typename A3>
struct Proxy04<R,A1,A2,A3,lua::Str> : public Proxy03<R,A1,A2,A3>
{
	typedef lua::Str A4;
	typedef R (*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func04(fn){}
	A4      p4;
	Func    func04;

	void GetValue04(lua::Handle L)
	{
		this->GetValue03(L);
		p4 = lua::CheckString(L, 4);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		this->ReturnValue(L,fn(p1,p2,p3,p4));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		fn(p1,p2,p3,p4);
	}

	int Do(lua::Handle L)
	{
		GetValue04(L);
		DoFunction(L,func04,this->p1,this->p2,this->p3,p4);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
struct Proxy05 : public Proxy04<R,A1,A2,A3,A4>
{
	typedef R (*Func)(A1,A2,A3,A4,A5);
	Proxy05(Func){/*warning message*/}
};

template<typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy05<R,A1,A2,A3,A4,lua::Int> : public Proxy04<R,A1,A2,A3,A4>
{
	typedef lua::Int A5;
	typedef R (*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func05(fn){}
	A5      p5;
	Func    func05;

	void GetValue05(lua::Handle L)
	{
		this->GetValue04(L);
		p5 = lua::CheckInteger(L, 5);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		this->ReturnValue(L,fn(p1,p2,p3,p4,p5));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		fn(p1,p2,p3,p4,p5);
	}

	int Do(lua::Handle L)
	{
		GetValue05(L);
		DoFunction(L,func05,this->p1,this->p2,this->p3,this->p4,p5);
		return (int)1;
	}
};

template<typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy05<R,A1,A2,A3,A4,lua::Num> : public Proxy04<R,A1,A2,A3,A4>
{
	typedef lua::Num A5;
	typedef R (*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func05(fn){}
	A5      p5;
	Func    func05;

	void GetValue05(lua::Handle L)
	{
		this->GetValue04(L);
		p5 = lua::CheckNumber(L, 5);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		this->ReturnValue(L,fn(p1,p2,p3,p4,p5));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		fn(p1,p2,p3,p4,p5);
	}

	int Do(lua::Handle L)
	{
		GetValue05(L);
		DoFunction(L,func05,this->p1,this->p2,this->p3,this->p4,p5);
		return (int)1;
	}
};

template<typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy05<R,A1,A2,A3,A4,lua::Str> : public Proxy04<R,A1,A2,A3,A4>
{
	typedef lua::Str A5;
	typedef R (*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func05(fn){}
	A5      p5;
	Func    func05;

	void GetValue05(lua::Handle L)
	{
		this->GetValue04(L);
		p5 = lua::CheckString(L, 5);
	}

	template<typename tagR>
	void DoFunction(lua::Handle L,tagR (*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		this->ReturnValue(L,fn(p1,p2,p3,p4,p5));
	}

	void DoFunction(lua::Handle  ,void (*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		fn(p1,p2,p3,p4,p5);
	}

	int Do(lua::Handle L)
	{
		GetValue05(L);
		DoFunction(L,func05,this->p1,this->p2,this->p3,this->p4,p5);
		return (int)1;
	}
};

//------------------------------------------------------------

template <typename R>
static Proxy* GetProxy(R(*f)())
{
	return (Proxy*)new Proxy00<R>(f);
}

template <typename R,typename A1>
static Proxy* GetProxy(R(*f)(A1))
{
	return (Proxy*)new Proxy01<R,A1>(f);
}

template <typename R,typename A1,typename A2>
static Proxy* GetProxy(R(*f)(A1,A2))
{
	return (Proxy*)new Proxy02<R,A1,A2>(f);
}

template <typename R,typename A1,typename A2,typename A3>
static Proxy* GetProxy(R(*f)(A1,A2,A3))
{
	return (Proxy*)new Proxy03<R,A1,A2,A3>(f);
}

template <typename R,typename A1,typename A2,typename A3,typename A4>
static Proxy* GetProxy(R(*f)(A1,A2,A3,A4))
{
	return (Proxy*)new Proxy04<R,A1,A2,A3,A4>(f);
}

template <typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
static Proxy* GetProxy(R(*f)(A1,A2,A3,A4,A5))
{
	return (Proxy*)new Proxy05<R,A1,A2,A3,A4,A5>(f);
}

//------------------------------------------------------------


}//namespace wrapper
}//namespace lua

#endif//_LUAPP_WRAPPER_PROXY_HPP_