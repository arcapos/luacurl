#include <lua.h>
#include <lauxlib.h>

#include <curl/curl.h>

#include "luacurl.h"
#include "multi.h"

int
lcurl_multi_init(lua_State *L)
{
	CURLM *multi_handle, **m;

	multi_handle = curl_multi_init();
	if (multi_handle == NULL)
		return luaL_error(L, "internal curl error");
	m = lua_newuserdata(L, sizeof(CURLM *));
	*m = multi_handle;
	luaL_getmetatable(L, CURLM_METATABLE);
	lua_setmetatable(L, -2);
	return 1;
}

int
lcurl_multi_add_handle(lua_State *L)
{
	CURLM **multi_handle = (CURLM **)luaL_checkudata(L, 1, CURLM_METATABLE);
	curlT *c = (curlT *)luaL_checkudata(L, 2, CURL_METATABLE);

	curl_multi_add_handle(*multi_handle, c->curl);
	lua_pushboolean(L, 1);
	return 1;
}

int
lcurl_multi_perform(lua_State *L)
{
	CURLM **multi_handle = (CURLM **)luaL_checkudata(L, 1, CURLM_METATABLE);
	int running_handles;

	curl_multi_perform(*multi_handle, &running_handles);
	lua_pushinteger(L, running_handles);
	return 1;
}

int
lcurl_multi_fds(lua_State *L)
{
	CURLM **multi_handle = (CURLM **)luaL_checkudata(L, 1, CURLM_METATABLE);
	fd_set readfds, writefds, excfds;
	int fd, max_fd, ridx, widx, eidx;

	FD_ZERO(&readfds);
	FD_ZERO(&writefds);
	FD_ZERO(&excfds);
	curl_multi_fdset(*multi_handle, &readfds, &writefds, &excfds, &max_fd);
	lua_newtable(L);
	lua_newtable(L);
	lua_newtable(L);

	ridx = widx = eidx = 1;

	for (fd = 0; fd < max_fd; fd++) {
		if (FD_ISSET(fd, &readfds)) {
			lua_pushinteger(L, ridx++);
			lua_pushinteger(L, fd);
			lua_settable(L, -5);
		}

		if (FD_ISSET(fd, &writefds)) {
			lua_pushinteger(L, widx++);
			lua_pushinteger(L, fd);
			lua_settable(L, -4);
		}

		if (FD_ISSET(fd, &excfds)) {
			lua_pushinteger(L, eidx++);
			lua_pushinteger(L, fd);
			lua_settable(L, -3);
		}
	}
	return 3;
}

int
lcurl_multi_remove_handle(lua_State *L)
{
	CURLM **multi_handle = (CURLM **)luaL_checkudata(L, 1, CURLM_METATABLE);
	curlT *c = (curlT *)luaL_checkudata(L, 2, CURL_METATABLE);

	curl_multi_remove_handle(*multi_handle, c->curl);
	lua_pushboolean(L, 1);
	return 1;
}

int
lcurl_multi_gc(lua_State *L)
{
	CURLM **multi_handle = (CURLM **)luaL_checkudata(L, 1, CURLM_METATABLE);

	if (*multi_handle)
		curl_multi_cleanup(*multi_handle);
	return 0;

}
