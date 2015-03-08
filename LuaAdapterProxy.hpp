﻿/**
@file   LuaAdapterProxy.hpp
@brief  To get all of parameters.
*/


#ifndef _LUAPP_ADAPTER_PROXY_HPP_
#define _LUAPP_ADAPTER_PROXY_HPP_


#include "Lua.hpp"



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
	ProxyReturn(){/*warning message*/}
};

template<typename C>
struct ProxyReturn<C,void> : public Proxy<C>
{
};

template<typename C>
struct ProxyReturn<C,lua::Int> : public Proxy<C>
{
	void ReturnValue(lua::Handle L,lua::Int num)
	{
		lua::PushInteger(L,num);
	}
};

template<typename C>
struct ProxyReturn<C,lua::Num> : public Proxy<C>
{
	void ReturnValue(lua::Handle L,lua::Num num)
	{
		lua::PushNumber(L,num);
	}
};

template<typename C>
struct ProxyReturn<C,lua::Str> : public Proxy<C>
{
	void ReturnValue(lua::Handle L,lua::Str num)
	{
		lua::PushString(L,num.c_str());
	}
};

//------------------------------------------------------------

template<typename C,typename R>
struct Proxy00 : public ProxyReturn<C,R>
{
	typedef R(C::*Func)();
	Proxy00(){}
	Proxy00(Func fn):func00(fn){}

	Func    func00;

	int Do(lua::Handle L,C *obj)
	{
		this->ReturnValue(L,(obj->*func00)());
		return (int)1;
	}
};

template<typename C>
struct Proxy00<C,void> : public ProxyReturn<C,void>
{
	typedef void R;
	typedef R(C::*Func)();
	Proxy00(){}
	Proxy00(Func fn):func00(fn){}
	Func    func00;

	int Do(lua::Handle,C *obj)
	{
		(obj->*func00)();
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1>
struct Proxy01 : public ProxyReturn<C,R>
{
	typedef R (C::*Func)(A1);
	Proxy01(Func){/*warning message*/}
};

template<typename C,typename R>
struct Proxy01<C,R,lua::Int> : public ProxyReturn<C,R>
{
	typedef lua::Int A1;
	typedef R (C::*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckInteger(L, 2);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,(obj->*fn)(p1));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1),A1 p1)
	{
		(obj->*fn)(p1);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue01(L);
		DoFunction(L,obj,func01,p1);
		return (int)1;
	}
};

template<typename C,typename R>
struct Proxy01<C,R,lua::Num> : public ProxyReturn<C,R>
{
	typedef lua::Num A1;
	typedef R (C::*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckNumber(L, 2);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,(obj->*fn)(p1));
	}

	template<typename tagC>
	void DoFunction(lua::Handle,  tagC *obj,void (tagC::*fn)(A1),A1 p1)
	{
		(obj->*fn)(p1);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue01(L);
		DoFunction(L,obj,func01,p1);
		return (int)1;
	}
};

template<typename C,typename R>
struct Proxy01<C,R,lua::Str> : public ProxyReturn<C,R>
{
	typedef lua::Str A1;
	typedef R (C::*Func)(A1);
	Proxy01(){}
	Proxy01(Func fn):func01(fn){}

	A1      p1;
	Func    func01;

	void GetValue01(lua::Handle L)
	{
		p1 = lua::CheckString(L, 2);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1),A1 p1)
	{
		this->ReturnValue(L,(obj->*fn)(p1));
	}

	template<typename tagC>
	void DoFunction(lua::Handle,  tagC *obj,void (tagC::*fn)(A1),A1 p1)
	{
		(obj->*fn)(p1);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue01(L);
		DoFunction(L,obj,func01,p1);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2>
struct Proxy02 : public Proxy01<C,R,A1>
{
	typedef R (C::*Func)(A1,A2);
	Proxy02(Func){/*warning message*/}
};

template<typename C,typename R,typename A1>
struct Proxy02<C,R,A1,lua::Int> : public Proxy01<C,R,A1>
{
	typedef lua::Int A2;
	typedef R(C::*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckInteger(L, 3);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		(obj->*fn)(p1,p2);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue02(L);
		DoFunction(L,obj,func02,this->p1,p2);
		return (int)1;
	}
};

template<typename C,typename R,typename A1>
struct Proxy02<C,R,A1,lua::Num> : public Proxy01<C,R,A1>
{
	typedef lua::Num A2;
	typedef R(C::*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckNumber(L, 3);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		(obj->*fn)(p1,p2);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue02(L);
		DoFunction(L,obj,func02,this->p1,p2);
		return (int)1;
	}
};

template<typename C,typename R,typename A1>
struct Proxy02<C,R,A1,lua::Str> : public Proxy01<C,R,A1>
{
	typedef lua::Str A2;
	typedef R(C::*Func)(A1,A2);

	Proxy02(){}
	Proxy02(Func fn):func02(fn){}
	A2      p2;
	Func    func02;

	void GetValue02(lua::Handle L)
	{
		this->GetValue01(L);
		p2 = lua::CheckString(L, 3);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2),A1 p1,A2 p2)
	{
		(obj->*fn)(p1,p2);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue02(L);
		DoFunction(L,obj,func02,this->p1,p2);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3>
struct Proxy03 : public Proxy02<C,R,A1,A2>
{
	typedef R (C::*Func)(A1,A2,A3);
	Proxy03(Func){/*warning message*/}
};

template<typename C,typename R,typename A1,typename A2>
struct Proxy03<C,R,A1,A2,lua::Int> : public Proxy02<C,R,A1,A2>
{
	typedef lua::Int A3;
	typedef R(C::*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func03(fn){}
	A3      p3;
	Func    func03;

	void GetValue03(lua::Handle L)
	{
		this->GetValue02(L);
		p3 = lua::CheckInteger(L, 4);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		(obj->*fn)(p1,p2,p3);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue03(L);
		DoFunction(L,obj,func03,this->p1,this->p2,p3);
		return (int)1;
	}
};

template<typename C,typename R,typename A1,typename A2>
struct Proxy03<C,R,A1,A2,lua::Num> : public Proxy02<C,R,A1,A2>
{
	typedef lua::Num A3;
	typedef R(C::*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func03(fn){}
	A3      p3;
	Func    func03;

	void GetValue03(lua::Handle L)
	{
		this->GetValue02(L);
		p3 = lua::CheckNumber(L, 4);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		(obj->*fn)(p1,p2,p3);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue03(L);
		DoFunction(L,obj,func03,this->p1,this->p2,p3);
		return (int)1;
	}
};

template<typename C,typename R,typename A1,typename A2>
struct Proxy03<C,R,A1,A2,lua::Str> : public Proxy02<C,R,A1,A2>
{
	typedef lua::Str A3;
	typedef R(C::*Func)(A1,A2,A3);

	Proxy03(){}
	Proxy03(Func fn):func03(fn){}
	A3      p3;
	Func    func03;

	void GetValue03(lua::Handle L)
	{
		this->GetValue02(L);
		p3 = lua::CheckString(L, 4);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3),A1 p1,A2 p2,A3 p3)
	{
		(obj->*fn)(p1,p2,p3);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue03(L);
		DoFunction(L,obj,func03,this->p1,this->p2,p3);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy04 : public Proxy03<C,R,A1,A2,A3>
{
	typedef R (C::*Func)(A1,A2,A3,A4);
	Proxy04(Func){/*warning message*/}
};

template<typename C,typename R,typename A1,typename A2,typename A3>
struct Proxy04<C,R,A1,A2,A3,lua::Int> : public Proxy03<C,R,A1,A2,A3>
{
	typedef lua::Int A4;
	typedef R(C::*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func04(fn){}
	A4      p4;
	Func    func04;

	void GetValue04(lua::Handle L)
	{
		this->GetValue03(L);
		p4 = lua::CheckInteger(L, 5);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3,p4));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		(obj->*fn)(p1,p2,p3,p4);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue04(L);
		DoFunction(L,obj,func04,this->p1,this->p2,this->p3,p4);
		return (int)1;
	}
};

template<typename C,typename R,typename A1,typename A2,typename A3>
struct Proxy04<C,R,A1,A2,A3,lua::Num> : public Proxy03<C,R,A1,A2,A3>
{
	typedef lua::Num A4;
	typedef R(C::*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func04(fn){}
	A4      p4;
	Func    func04;

	void GetValue04(lua::Handle L)
	{
		this->GetValue03(L);
		p4 = lua::CheckNumber(L, 5);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3,p4));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		(obj->*fn)(p1,p2,p3,p4);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue04(L);
		DoFunction(L,obj,func04,this->p1,this->p2,this->p3,p4);
		return (int)1;
	}
};

template<typename C,typename R,typename A1,typename A2,typename A3>
struct Proxy04<C,R,A1,A2,A3,lua::Str> : public Proxy03<C,R,A1,A2,A3>
{
	typedef lua::Str A4;
	typedef R(C::*Func)(A1,A2,A3,A4);

	Proxy04(){}
	Proxy04(Func fn):func04(fn){}
	A4      p4;
	Func    func04;

	void GetValue04(lua::Handle L)
	{
		this->GetValue03(L);
		p4 = lua::CheckString(L, 5);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3,p4));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3,A4),A1 p1,A2 p2,A3 p3,A4 p4)
	{
		(obj->*fn)(p1,p2,p3,p4);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue04(L);
		DoFunction(L,obj,func04,this->p1,this->p2,this->p3,p4);
		return (int)1;
	}
};

//------------------------------------------------------------

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4,typename A5>
struct Proxy05 : public Proxy04<C,R,A1,A2,A3,A4>
{
	typedef R (C::*Func)(A1,A2,A3,A4,A5);
	Proxy05(Func){/*warning message*/}
};

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy05<C,R,A1,A2,A3,A4,lua::Int> : public Proxy04<C,R,A1,A2,A3,A4>
{
	typedef lua::Int A5;
	typedef R(C::*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func05(fn){}
	A5      p5;
	Func    func05;

	void GetValue05(lua::Handle L)
	{
		this->GetValue04(L);
		p5 = lua::CheckInteger(L, 6);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3,p4,p5));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		(obj->*fn)(p1,p2,p3,p4,p5);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue05(L);
		DoFunction(L,obj,func05,this->p1,this->p2,this->p3,this->p4,p5);
		return (int)1;
	}
};

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy05<C,R,A1,A2,A3,A4,lua::Num> : public Proxy04<C,R,A1,A2,A3,A4>
{
	typedef lua::Num A5;
	typedef R(C::*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func05(fn){}
	A5      p5;
	Func    func05;

	void GetValue05(lua::Handle L)
	{
		this->GetValue04(L);
		p5 = lua::CheckNumber(L, 6);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3,p4,p5));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		(obj->*fn)(p1,p2,p3,p4,p5);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue05(L);
		DoFunction(L,obj,func05,this->p1,this->p2,this->p3,this->p4,p5);
		return (int)1;
	}
};

template<typename C,typename R,typename A1,typename A2,typename A3,typename A4>
struct Proxy05<C,R,A1,A2,A3,A4,lua::Str> : public Proxy04<C,R,A1,A2,A3,A4>
{
	typedef lua::Str A5;
	typedef R(C::*Func)(A1,A2,A3,A4,A5);

	Proxy05(){}
	Proxy05(Func fn):func05(fn){}
	A5      p5;
	Func    func05;

	void GetValue05(lua::Handle L)
	{
		this->GetValue04(L);
		p5 = lua::CheckString(L, 6);
	}

	template<typename tagC,typename tagR>
	void DoFunction(lua::Handle L,tagC *obj,tagR (tagC::*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		this->ReturnValue(L,(obj->*fn)(p1,p2,p3,p4,p5));
	}

	template<typename tagC>
	void DoFunction(lua::Handle  ,tagC *obj,void (tagC::*fn)(A1,A2,A3,A4,A5),A1 p1,A2 p2,A3 p3,A4 p4,A5 p5)
	{
		(obj->*fn)(p1,p2,p3,p4,p5);
	}

	int Do(lua::Handle L,C *obj)
	{
		GetValue05(L);
		DoFunction(L,obj,func05,this->p1,this->p2,this->p3,this->p4,p5);
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

//------------------------------------------------------------





}//namespace adapter
}//namespace lua

#endif//_LUAPP_ADAPTER_PROXY_HPP_