/**
 * @file   State.hpp
 * @brief  The main interface of luapp.
 */


#pragma once

#include "luapp/Adapter.hpp"
#include "luapp/Wrapper.hpp"
#include "luapp/Function.hpp"
#include "luapp/FunctionExt.hpp"
#include "luapp/Searcher.hpp"


namespace lua{


//-----------------ClassTypeFilter-----------------start
template<typename F>
struct ClassTypeFilter{};

template<typename R,typename C>
struct ClassTypeFilter<R (C::*)()>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1>
struct ClassTypeFilter<R (C::*)(A1)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2>
struct ClassTypeFilter<R (C::*)(A1,A2)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2,typename A3>
struct ClassTypeFilter<R (C::*)(A1,A2,A3)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2,typename A3,typename A4>
struct ClassTypeFilter<R (C::*)(A1,A2,A3,A4)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2,typename A3,typename A4,typename A5>
struct ClassTypeFilter<R (C::*)(A1,A2,A3,A4,A5)>
{
	typedef C ClassType;
};
template<typename R,typename C,typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
struct ClassTypeFilter<R (C::*)(A1,A2,A3,A4,A5,A6)>
{
	typedef C ClassType;
};
//-----------------ClassTypeFilter-----------------end


/// The main interface of luapp.
template<int N=0>
class State
{
	public:

		State(lua::Handle h = (lua::Handle)0):_lua(h),_moduleMode(0)
		{
			if ( _lua )
			{
				_moduleMode = 1;
			}
			else
			{
				this->init();
			}
		}

		~State()
		{
			if(_lua)drop();
		}

		void bind(lua::Str name,lua::CFunction func)
		{
			if ( _moduleMode )
			{
				_funcReg.add(name,func);
			}
			else
			{
				lua::PushFunction(_lua, func);
				lua::SetGlobal(_lua, name);
			}
		}

		/// Let lua script could use given class type.
		template<typename C>
		void bindClass(lua::Str class_name)
		{
			if ( _moduleMode )
			{
				_funcReg.add(class_name,adapter::Adapter<C,N>::getConstructor(_lua,class_name));
			}
			else
			{
				adapter::Adapter<C,N>::registerClass(_lua,class_name);
			}
		}

		/**
		 * Let lua script could use given class type.
		 * It have a faster constructor. But lua need to store more information.
		 * Always call it after all bindMethod().
		 */
		template<typename C>
		void bindClassEx(lua::Str class_name)
		{
			if ( _moduleMode )
			{
				_funcReg.add(class_name,adapter::Adapter<C,N>::getConstructor2(_lua,class_name));
			}
			else
			{
				adapter::Adapter<C,N>::registerClassEx(_lua,class_name);
			}
		}

		/**
		 * Let lua script could use given member function.
		 * Don't use it without bindClass() or bindClassEx().
		 */
		template<typename F>
		void bindMethod(lua::Str name,F fn)
		{
			typedef typename ClassTypeFilter<F>::ClassType C;
			struct adapter::Adapter<C,N>::Pack     myF( name,adapter::GetProxy(fn));
			adapter::Adapter<C,N>::pushPack(myF);
		}

		/// Let lua script could use given global function.
		template<typename F>
		void bind(lua::Str name,F fn)
		{
			if ( _moduleMode )
			{
				lua::log::Cout<<"error:bind(lua::Str name,F fn) not support module mode."<<lua::log::End;
				return;
			}

			wrapper::Wrapper<N>::registerFunction(_lua,name,fn);
		}

		/**
		 * Let lua script could use given member function.
		 * This member function will be looks like a global function in lua.
		 */
		template<typename F,typename C>
		void bind(lua::Str name,F fn,C *obj)
		{
			if ( _moduleMode )
			{
				lua::log::Cout<<"error:bind(lua::Str name,F fn,C *obj) not support module mode."<<lua::log::End;
				return;
			}

			// Add class type checked here some times later.
			wrapper::Wrapper<N>::registerFunction(_lua,name,fn,obj);
		}

		int init()
		{
			if ( _moduleMode )
			{
				return (int)1;
			}

			if ( _lua )
			{
				return (int)1;
			}

			_lua=lua::CreateHandle();

			if ( ! _lua )
			{
				return (int)0;
			}

			lua::OpenLibs(_lua);

			return (int)1;
		}

		void drop()
		{
			if ( _moduleMode )
			{
				this->build_module();
			}
			else
			{
				lua::DestroyHandle(_lua);
			}
			_lua=(lua::Handle)0;
		}

		int load(lua::Str name,lua::Str& code)
		{
			int result = lua::LoadScript(_lua,name,code);

			if ( ! result )
			{
				lua::log::Cout<<"lua::State::load(name,code):"<<this->error()<<lua::log::End;
			}

			return result;
		}

		int load(lua::Str filename)
		{
			int result = lua::LoadScript(_lua,filename);

			if ( ! result )
			{
				lua::log::Cout<<"lua::State::load(filename):"<<this->error()<<lua::log::End;
			}

			return result;
		}

		int run()
		{
			if ( _moduleMode )
			{
				lua::log::Cout<<"error:You can't do this. Because module mode didn't run its own script."<<lua::log::End;
				return (int)0;
			}

			if ( lua::PCall(_lua,0,0,0) )
			{
				return 0;
			}

			return 1;
		}

		int run(lua::Str name,lua::Str& code,std::function<lua::Str&(lua::Str)> loader)
		{
			if ( _moduleMode )
			{
				lua::log::Cout<<"error:You can't do this. Because module mode didn't run its own script."<<lua::log::End;
				return (int)0;
			}

			if ( loader )
			{
				this->searcher(loader);
			}

			int result = lua::DoScript(_lua,name,code);

			if ( ! result )
			{
				lua::log::Cout<<"lua::State::run(name,code,loader):"<<this->error()<<lua::log::End;
			}

			return result;
		}

		int run(lua::Str str)
		{
			if ( _moduleMode )
			{
				lua::log::Cout<<"error:You can't do this. Because module mode didn't run its own script."<<lua::log::End;
				return (int)0;
			}

			int result = lua::DoScript(_lua,str);

			if ( ! result )
			{
				lua::log::Cout<<"lua::State::run(str):"<<this->error()<<lua::log::End;
			}

			return result;
		}

		int run(lua::Str path,lua::Str script)
		{
			this->path(path);
			return this->run(path+"/"+script);
		}

		/// Let luapp know where to read more lua scripts.
		void path(lua::Str path)
		{
			if(_lua)
			{
				path+="/";
				add_script_path_to_lua(path);
			}
		}

		/// Set global variable to lua script. Don't try to send function.
		template<typename T>
		void setGlobal(lua::Str name,T t)
		{
			PushVarToLua(_lua,t);
			lua::SetGlobal(_lua,name);
		}

		/// Get global variable from lua script.
		template<typename T>
		void getGlobal(lua::Str name,T t)
		{
			lua::GetGlobal(_lua,name);
			CheckVarFromLua(_lua,t,-1);
			lua::Pop(_lua,1);
		}

		/// Get global function(one or no return value).
		template<typename F>
		void getFunc(const char *name,lua::Function<F> *func)
		{
			func->_lua=_lua;
			func->_funcName=name;
		}

		/// Get global function(more than one return value).
		template<typename R,typename P>
		void getFunc(const char *name,lua::FunctionExt<R,P> *func)
		{
			func->_lua=_lua;
			func->_funcName=name;
		}

		/// Call global function that don't have return value.
		void call(lua::Str name)
		{
			lua::GetGlobal(_lua,name);
			lua::PCall(_lua,0,0,0);
		}

		template<typename A1>
		void call(lua::Str name,A1 a1)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PCall(_lua,1,0,0);
		}

		template<typename A1,typename A2>
		void call(lua::Str name,A1 a1,A2 a2)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PCall(_lua,2,0,0);
		}

		template<typename A1,typename A2,typename A3>
		void call(lua::Str name,A1 a1,A2 a2,A3 a3)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PCall(_lua,3,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4>
		void call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PCall(_lua,4,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4,typename A5>
		void call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PushVarToLua(_lua,a5);
			lua::PCall(_lua,5,0,0);
		}

		template<typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
		void call(lua::Str name,A1 a1,A2 a2,A3 a3,A4 a4,A5 a5,A6 a6)
		{
			lua::GetGlobal(_lua,name);
			lua::PushVarToLua(_lua,a1);
			lua::PushVarToLua(_lua,a2);
			lua::PushVarToLua(_lua,a3);
			lua::PushVarToLua(_lua,a4);
			lua::PushVarToLua(_lua,a5);
			lua::PushVarToLua(_lua,a6);
			lua::PCall(_lua,6,0,0);
		}

		void searcher(std::function<lua::Str&(lua::Str)> loader)
		{
			Searcher<N>::setup(_lua,loader);
		}

	private:

		void add_script_path_to_lua(lua::Str str)
		{
			                                 // ...
			lua::GetGlobal(_lua,"package");  // ... package
			lua::GetField(_lua,-1, "path");  // ... package path
			lua::PushString(_lua,str+"?.lua;"+lua::CheckString(_lua,-1));
			                                 // ... package path new_path
			lua::SetField(_lua,-3, "path");  // ... package path
			lua::Pop(_lua,2);                // ...
		}

		void build_module()
		{
			_funcReg.refresh();
			lua::NewModule(_lua,_funcReg);
		}

		lua::Str error()
		{
			lua::Var  var;
			lua::CheckVarFromLua(_lua,&var,-1);

			lua::Str  str("error message not found");

			if ( lua::VarType<lua::Str>(var) )
			{
				str = lua::VarCast<lua::Str>(var);
			//	lua::Pop(_lua,-1);    I can't make sure it is error message.
			}

			return str;
		}

		lua::Handle      _lua;
		bool             _moduleMode;
		lua::FuncReg     _funcReg;      // Only work for module mode.
};



}//namespace lua
