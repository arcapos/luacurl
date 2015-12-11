/*
 * Copyright (c) 2013 Micro Systems Marc Balmer, CH-5073 Gipf-Oberfrick.
 * All rights reserved.
 *
 * This source code is the proprietary confidential property of Micro Systems
 * Marc Balmer, and is provided to licensee solely for documentation and
 * educational purposes. Reproduction, publication, or distribution in any form
 * to any party other than the licensee is strictly prohibited.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

/* Lua binding for CURL */

#ifndef __LUACURL_H__
#define __LUACURL_H__

#define LUACURL_LIBNAME	"curl"
#define CURL_METATABLE	"cURL easy handle"

#define MAKE_VERSION_NUM(x,y,z) (z + (y << 8) + (x << 16))
#define CURL_NEWER(x,y,z) (MAKE_VERSION_NUM(x,y,z) <= LIBCURL_VERSION_NUM)
#define CURL_OLDER(x,y,z) (MAKE_VERSION_NUM(x,y,z) > LIBCURL_VERSION_NUM)

/* wrap values of arbitrary type */
union luaValueT
{
	struct curl_slist	*slist;
	curl_read_callback	 rcb;
	curl_write_callback	 wcb;
	curl_progress_callback	 pcb;
#if CURL_NEWER(7,12,3)
	curl_ioctl_callback	 icb;
#endif
	long			 nval;
	char			*sval;
	void			*ptr;
};

/* CURL object wrapper type */
typedef struct
{
	CURL		*curl;
	lua_State	*L;
	int 		 fwriterRef;
	int		 wudtype;
	union luaValueT	 wud;
	int		 freaderRef;
	int		 rudtype;
	union luaValueT	 rud;
	int		 fprogressRef;
	int		 pudtype;
	union luaValueT	 pud;
	int		 fheaderRef;
	int		 hudtype;
	union luaValueT	 hud;
	int		 fioctlRef;
	int		 iudtype;
	union		 luaValueT iud;
} curlT;

struct int_constant {
	char *name;
	long value;
};

struct str_constant {
	char *name;
	char *value;
};

extern size_t num_curl_int(void);

#endif /* __LUACURL_H__ */
