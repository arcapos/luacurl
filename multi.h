#ifndef __MULTI_H__
#define __MULTI_H__

#define CURLM_METATABLE	"cURL multi handle"

extern int lcurl_multi_init(lua_State *);
extern int lcurl_multi_add_handle(lua_State *);
extern int lcurl_multi_fds(lua_State *);
extern int lcurl_multi_perform(lua_State *);
extern int lcurl_multi_remove_handle(lua_State *);

extern int lcurl_multi_gc(lua_State *);

#endif /* __MULTI_H__ */
