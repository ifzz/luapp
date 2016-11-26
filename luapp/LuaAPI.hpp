/**
 * @file   LuaAPI.hpp
 * @brief  It's just a wrapper of lua.
 */

#pragma once


#include "lua.hpp"
#include "luapp/DataType.hpp"
#include "luapp/FuncReg.hpp"

namespace lua{


//------------------------------------------------------------------------------
inline void NewModule(Handle h,FuncReg &reg)
{
	luaL_newlib(h,(luaL_Reg*)(reg._get()));
}
//------------------------------------------------------------------------------
inline Handle CreateHandle()
{
	return luaL_newstate();
}
//------------------------------------------------------------------------------
inline void DestroyHandle(Handle h)
{
	lua_close(h);
}
//------------------------------------------------------------------------------
inline int PCall(Handle h,int num01,int num02,int num03)
{
	return lua_pcall(h,num01,num02,num03);
}
//------------------------------------------------------------------------------
inline void OpenLibs(Handle h)
{
	luaL_openlibs(h);
}
//------------------------------------------------------------------------------
// Remove it in next version.
inline Str GetError(Handle h)
{
	Str  str(lua_tostring(h, -1));
	lua_pop(h, 1);

	return str;
}
//------------------------------------------------------------------------------
inline void DoString(Handle h,lua::Str code)
{
	luaL_dostring(h, code.c_str());
}
//------------------------------------------------------------------------------
inline void _PrintScriptLoadingError(int error_code,lua::Str& filename)
{
	switch ( error_code )
	{
		case 0:
			lua::log::Cout<<"warning:big mistake! It's not a error."<<lua::log::End;
			break;
		case LUA_ERRFILE:
			lua::log::Cout<<"error:cannot open the file:"<<filename<<lua::log::End;
			break;
		case LUA_ERRSYNTAX:
			lua::log::Cout<<"error:syntax error during pre-compilation"<<lua::log::End;
			break;
		case LUA_ERRMEM:
			lua::log::Cout<<"error:memory allocation error"<<lua::log::End;
			break;
		default:
			lua::log::Cout<<"error:load script failed for some reason"<<lua::log::End;
	}
}
//------------------------------------------------------------------------------
inline int LoadScript(Handle h,lua::Str name,lua::Str& code)
{
	if ( name.empty() )
	{
		lua::log::Cout<<"error:script name is empty string"<<lua::log::End;
		return 0;
	}
	else
	{
		int result = luaL_loadbuffer(h,code.c_str(), code.size(), name.c_str());

		if ( result )
		{
			_PrintScriptLoadingError(result,name);
			return 0;
		}
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int LoadScript(Handle h,lua::Str filename)
{
	if ( filename.empty() )
	{
		lua::log::Cout<<"error:file name is empty string"<<lua::log::End;
		return 0;
	}
	else
	{
		int result = luaL_loadfile(h,filename.c_str());

		if ( result )
		{
			_PrintScriptLoadingError(result,filename);
			return 0;
		}
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int DoScript(Handle h,lua::Str name,lua::Str& code)
{
	if ( name.empty() )
	{
		lua::log::Cout<<"error:script name is empty string"<<lua::log::End;
		return 0;
	}
	else
	{
		int result = luaL_loadbuffer(h,code.c_str(), code.size(), name.c_str());

		if ( result )
		{
			_PrintScriptLoadingError(result,name);
			return 0;
		}
	}

	if( lua_pcall(h,0,0,0) )
	{
		return 0;
	}

	return 1;
}
//------------------------------------------------------------------------------
inline int DoScript(Handle h,lua::Str filename)
{
	if ( filename.empty() )
	{
		lua::log::Cout<<"error:file name is empty string"<<lua::log::End;
		return 0;
	}
	else
	{
		int result = luaL_loadfile(h,filename.c_str());

		if ( result )
		{
			_PrintScriptLoadingError(result,filename);
			return 0;
		}
	}

	if( lua_pcall(h,0,0,0) )
	{
		return 0;
	}

	return 1;
}
//------------------------------------------------------------------------------
inline void NewTable(Handle h)
{
	lua_newtable(h);
}
//------------------------------------------------------------------------------
inline int NewMetaTable(Handle h,lua::Str tname)
{
	#ifdef _LUAPP_CHECK_CAREFUL_
	luaL_getmetatable(h,tname.c_str());
	if ( lua_type(h, -1)!=LUA_TNIL )
	{
		lua::log::Cout<<"error:this meta table already exist."<<lua::log::End;
	}
	lua_pop(h,1);
	#endif

	return luaL_newmetatable(h,tname.c_str());
}
//------------------------------------------------------------------------------
inline void* NewUserData(Handle h,size_t size)
{
	return lua_newuserdata(h,size);
}
//------------------------------------------------------------------------------
inline void SetGlobal(Handle h,lua::Str var)
{
	#ifdef _LUAPP_CHECK_CAREFUL_
	lua_getglobal(h,var.c_str());
	if ( lua_type(h, -1)!=LUA_TNIL )
	{
		lua::log::Cout<<"warning:this global variable already exist."<<lua::log::End;
	}
	lua_pop(h,1);
	#endif

	lua_setglobal(h,var.c_str());
}
//------------------------------------------------------------------------------
inline void GetGlobal(Handle h,lua::Str var)
{
	lua_getglobal(h,var.c_str());
}
//------------------------------------------------------------------------------
inline void SetTable(Handle h,int index)
{
	lua_settable(h,index);
}
//------------------------------------------------------------------------------
inline void GetTable(Handle h,int index)
{
	lua_gettable(h,index);
}
//------------------------------------------------------------------------------
inline void SetField(Handle h,int index, lua::Str name)
{
	lua_setfield(h,index,name.c_str());
}
//------------------------------------------------------------------------------
inline void GetField(Handle h,int index, lua::Str k)
{
	lua_getfield(h,index,k.c_str());
}
//------------------------------------------------------------------------------
inline int SetMetaTable(Handle h,int index)
{
	return lua_setmetatable(h,index);
}
//------------------------------------------------------------------------------
inline void GetMetaTable(Handle h,lua::Str name)
{
	luaL_getmetatable(h,name.c_str());
}
//------------------------------------------------------------------------------
inline void PushClosure(Handle h,CFunction fn,int n)
{
	lua_pushcclosure(h, fn, n);
}
//------------------------------------------------------------------------------
inline void PushFunction(Handle h,CFunction fn)
{
	lua_pushcfunction(h,fn);
}
//------------------------------------------------------------------------------
inline void PushString(Handle h,lua::Str str)
{
	lua_pushstring(h, str.c_str());
}
//------------------------------------------------------------------------------
inline void PushValue(Handle h,int index)
{
	lua_pushvalue(h,index);
}
//------------------------------------------------------------------------------
inline void PushNumber(Handle h,double n)
{
	lua_pushnumber(h,n);
}
//------------------------------------------------------------------------------
inline void PushBoolean(Handle h,bool num)
{
	lua_pushboolean(h,(int)num);
}
//------------------------------------------------------------------------------
inline void PushInteger(Handle h,int num)
{
	lua_pushinteger(h,num);
}
//------------------------------------------------------------------------------
template<typename S>
inline void PushUserData(Handle h,S ud)
{
	                                               // ...
	void*  ptr = lua::NewUserData(h, sizeof(S));   // ... [UD]
	*((S*)ptr) = ud;
}
//------------------------------------------------------------------------------
template<typename S>
inline void PushUserData(Handle h,S ud, lua::Str tname)
{
	                                               // ...
	void*  ptr = lua::NewUserData(h, sizeof(S));   // ... [UD]
	*((S*)ptr) = ud;
	lua::GetMetaTable(h, tname.c_str());           // ... [UD] [MT]
	lua::SetMetaTable(h, -2);                      // ... [UD]
}
//------------------------------------------------------------------------------
inline double CheckNumber(Handle h,int index)
{
//	return luaL_checknumber(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h,index)!=LUA_TNUMBER )
	{
		lua::log::Cout<<"error:lua::CheckNumber"<<lua::log::End;
		return 0.0;
	}
	#endif

	return lua_tonumber(h,index);
}
//------------------------------------------------------------------------------
inline bool CheckBoolean(Handle h,int index)
{
//	return luaL_checkboolean(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h,index)!=LUA_TBOOLEAN )
	{
		lua::log::Cout<<"error:lua::CheckBoolean"<<lua::log::End;
		return false;
	}
	#endif

	return lua_toboolean(h,index)==0 ? false:true;
}
//------------------------------------------------------------------------------
inline int CheckInteger(Handle h,int index)
{
//	return luaL_checkinteger(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TNUMBER )
	{
		lua::log::Cout<<"error:lua::CheckInteger"<<lua::log::End;
		return 0;
	}
	else if ( ! lua_isinteger(h,index) )
	{
		lua::log::Cout<<"error:lua::CheckInteger: not a integer"<<lua::log::End;
		return 0;
	}
	#endif

	return (int)lua_tointeger(h,index);
}
//------------------------------------------------------------------------------
inline Str CheckString(Handle h,int index)
{
//	return Str(luaL_checkstring(h,index));

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TSTRING )
	{
		lua::log::Cout<<"error:lua::CheckString"<<lua::log::End;
		return Str("none");
	}
	#endif

	return lua_tostring(h,index);
}
//------------------------------------------------------------------------------
inline void* CheckUserData(Handle h,int index)
{
	return lua_touserdata(h,index);
}
//------------------------------------------------------------------------------
inline void* CheckUserData(Handle h,int index, lua::Str tname)
{
	return luaL_checkudata(h, index, tname.c_str());
}
//------------------------------------------------------------------------------
inline void PushPointer(Handle h,Ptr ptr)
{
	lua_pushlightuserdata(h,ptr);
}
//------------------------------------------------------------------------------
#ifdef _LUAPP_CPP11_
inline void PushPointer(Handle h,std::nullptr_t)
{
	lua_pushlightuserdata(h,(void*)0);
}
#endif
//------------------------------------------------------------------------------
inline Ptr CheckPointer(Handle h,int index)
{
//	return (Ptr)luaL_checklightudata(h,index);

	#ifdef _LUAPP_CHECK_DATA_TYPE_
	if ( lua_type(h, index)!=LUA_TLIGHTUSERDATA )
	{
		lua::log::Cout<<"error:lua::CheckPointer"<<lua::log::End;
		#ifdef _LUAPP_CPP11_
		return nullptr;
		#else
		return NULL;
		#endif
	}
	#endif

    return (Ptr)lua_topointer(h, index);
}
//------------------------------------------------------------------------------
inline int UpValueIndex(int index)
{
	return lua_upvalueindex(index);
}
//------------------------------------------------------------------------------
inline void Pop(Handle h,int num)
{
	lua_pop(h,num);
}
//------------------------------------------------------------------------------
inline void SetTop(Handle h,int num)
{
	lua_settop(h,num);
}
//------------------------------------------------------------------------------
inline int GetTop(Handle h)
{
	return lua_gettop(h);
}
//------------------------------------------------------------------------------

}
