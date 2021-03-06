/**
 * @file   AdapterProxy.hpp
 * @brief  To get all of parameters.
 */

#pragma once

#include "luapp/Standard.hpp"


namespace lua{
namespace adapter{


//------------------------------------------------------------

template<typename C>
struct Proxy
{
	virtual ~Proxy(){}
	virtual int Do(lua::Handle,C*)=0;
};

//------------------------------------------------------------

template<typename C,typename R>
struct ProxyReturn : public Proxy<C>
{
	void returnValue(lua::Handle L,R num)
	{
		PushVarToLua(L,num);
	}
};

//------------------------------------------------------------

template<typename C,typename R>
struct Proxy00 : public ProxyReturn<C,R>
{
	typedef R(C::*Func)();
	Proxy00(){}
	Proxy00(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		this->returnValue(L,(obj->*func)());
		return (int)1;
	}
};

template<typename C>
struct Proxy00<C,void> : public ProxyReturn<C,void>
{
	typedef void(C::*Func)();
	Proxy00(){}
	Proxy00(Func fn):func(fn){}
	Func    func;

	int Do(lua::Handle,C *obj)
	{
		(obj->*func)();
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1>
struct Proxy01 : public ProxyReturn<C,R>
{
	typedef R (C::*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		lua::CheckVarFromLua(L,&p1,2);
		this->returnValue(L,(obj->*func)(p1));
		return (int)1;
	}
};

template<typename C,typename A1>
struct Proxy01<C,void,A1>
{
	typedef void (C::*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		lua::CheckVarFromLua(L,&p1,2);
		(obj->*func)(p1);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2>
struct Proxy02 : public ProxyReturn<C,R>
{
	typedef R(C::*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		this->returnValue(L,(obj->*func)(p1,p2));
		return (int)1;
	}
};

template<typename C,typename A1,typename A2>
struct Proxy02<C,void,A1,A2>
{
	typedef void(C::*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		(obj->*func)(p1,p2);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3>
struct Proxy03 : public ProxyReturn<C,R>
{
	typedef R(C::*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		lua::CheckVarFromLua(L,&p3,4);
		this->returnValue(L,(obj->*func)(p1,p2,p3));
		return (int)1;
	}
};

template<typename C,typename A1,typename A2,typename A3>
struct Proxy03<C,void,A1,A2,A3>
{
	typedef void(C::*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		lua::CheckVarFromLua(L,&p3,4);
		(obj->*func)(p1,p2,p3);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy04 : public ProxyReturn<C,R>
{
	typedef R(C::*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		lua::CheckVarFromLua(L,&p3,4);
		lua::CheckVarFromLua(L,&p4,5);
		this->returnValue(L,(obj->*func)(p1,p2,p3,p4));
		return (int)1;
	}
};

template<typename C,typename A1,typename A2,typename A3,typename A4>
struct Proxy04<C,void,A1,A2,A3,A4>
{
	typedef void(C::*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		lua::CheckVarFromLua(L,&p3,4);
		lua::CheckVarFromLua(L,&p4,5);
		(obj->*func)(p1,p2,p3,p4);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
struct Proxy05 : public ProxyReturn<C,R>
{
	typedef R(C::*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		A5      p5;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		lua::CheckVarFromLua(L,&p3,4);
		lua::CheckVarFromLua(L,&p4,5);
		lua::CheckVarFromLua(L,&p5,6);
		this->returnValue(L,(obj->*func)(p1,p2,p3,p4,p5));
		return (int)1;
	}
};

template<typename C,typename A1,typename A2,typename A3,typename A4,typename A5>
struct Proxy05<C,void,A1,A2,A3,A4,A5>
{
	typedef void(C::*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		A5      p5;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		lua::CheckVarFromLua(L,&p3,4);
		lua::CheckVarFromLua(L,&p4,5);
		lua::CheckVarFromLua(L,&p5,6);
		(obj->*func)(p1,p2,p3,p4,p5);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct Proxy06 : public ProxyReturn<C,R>
{
	typedef R(C::*Func)(A1,A2,A3,A4,A5,A6);

	Proxy06(){}
	Proxy06(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		A5      p5;
		A6      p6;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		lua::CheckVarFromLua(L,&p3,4);
		lua::CheckVarFromLua(L,&p4,5);
		lua::CheckVarFromLua(L,&p5,6);
		lua::CheckVarFromLua(L,&p6,7);
		this->returnValue(L,(obj->*func)(p1,p2,p3,p4,p5,p6));
		return (int)1;
	}
};

template<typename C,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct Proxy06<C,void,A1,A2,A3,A4,A5,A6>
{
	typedef void(C::*Func)(A1,A2,A3,A4,A5,A6);

	Proxy06(){}
	Proxy06(Func fn):func(fn){}

	Func    func;

	int Do(lua::Handle L,C *obj)
	{
		A1      p1;
		A2      p2;
		A3      p3;
		A4      p4;
		A5      p5;
		A6      p6;
		lua::CheckVarFromLua(L,&p1,2);
		lua::CheckVarFromLua(L,&p2,3);
		lua::CheckVarFromLua(L,&p3,4);
		lua::CheckVarFromLua(L,&p4,5);
		lua::CheckVarFromLua(L,&p5,6);
		lua::CheckVarFromLua(L,&p6,7);
		(obj->*func)(p1,p2,p3,p4,p5,p6);
		return (int)1;
	}
};

//------------------------------------------------------------

template <typename C,typename R>
static Proxy<C>* GetProxy(R(C::*f)())
{
	return (Proxy<C>*)new Proxy00<C,R>(f);
}

template <typename C,typename R,typename A1>
static Proxy<C>* GetProxy(R(C::*f)(A1))
{
	return (Proxy<C>*)new Proxy01<C,R,A1>(f);
}

template <typename C,typename R,typename A1,typename A2>
static Proxy<C>* GetProxy(R(C::*f)(A1,A2))
{
	return (Proxy<C>*)new Proxy02<C,R,A1,A2>(f);
}

template <typename C,typename R,typename A1,typename A2,typename A3>
static Proxy<C>* GetProxy(R(C::*f)(A1,A2,A3))
{
	return (Proxy<C>*)new Proxy03<C,R,A1,A2,A3>(f);
}

template <typename C,typename R,typename A1,typename A2,typename A3,typename A4>
static Proxy<C>* GetProxy(R(C::*f)(A1,A2,A3,A4))
{
	return (Proxy<C>*)new Proxy04<C,R,A1,A2,A3,A4>(f);
}

template <typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
static Proxy<C>* GetProxy(R(C::*f)(A1,A2,A3,A4,A5))
{
	return (Proxy<C>*)new Proxy05<C,R,A1,A2,A3,A4,A5>(f);
}

template <typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
static Proxy<C>* GetProxy(R(C::*f)(A1,A2,A3,A4,A5,A6))
{
	return (Proxy<C>*)new Proxy06<C,R,A1,A2,A3,A4,A5,A6>(f);
}

//------------------------------------------------------------





}//namespace adapter
}//namespace lua
