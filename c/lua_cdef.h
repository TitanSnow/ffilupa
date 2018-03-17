/*
** $Id: lua.h,v 1.331 2016/05/30 15:53:28 roberto Exp $
** Lua - A Scripting Language
** Lua.org, PUC-Rio, Brazil (http://www.lua.org)
** See Copyright Notice at the end of this file
*/


extern const char LUA_VERSION_MAJOR[];
extern const char LUA_VERSION_MINOR[];
extern const int LUA_VERSION_NUM;
extern const char LUA_VERSION_RELEASE[];

extern const char LUA_VERSION[];
extern const char LUA_RELEASE[];
extern const char LUA_COPYRIGHT[];
extern const char LUA_AUTHORS[];


/* mark for precompiled code ('<esc>Lua') */
extern const char LUA_SIGNATURE[];

/* option for multiple returns in 'lua_pcall' and 'lua_call' */
extern const int LUA_MULTRET;


/*
** Pseudo-indices
** (-LUAI_MAXSTACK is the minimum valid index; we keep some free empty
** space after that to help overflow detection)
*/
extern const int LUA_REGISTRYINDEX;
int lua_upvalueindex (int i);


/* thread status */
extern const int LUA_OK;
extern const int LUA_YIELD;
extern const int LUA_ERRRUN;
extern const int LUA_ERRSYNTAX;
extern const int LUA_ERRMEM;
extern const int LUA_ERRGCMM;
extern const int LUA_ERRERR;


typedef struct lua_State lua_State;


/*
** basic types
*/
extern const int LUA_TNONE;

extern const int LUA_TNIL;
extern const int LUA_TBOOLEAN;
extern const int LUA_TLIGHTUSERDATA;
extern const int LUA_TNUMBER;
extern const int LUA_TSTRING;
extern const int LUA_TTABLE;
extern const int LUA_TFUNCTION;
extern const int LUA_TUSERDATA;
extern const int LUA_TTHREAD;

extern const int LUA_NUMTAGS;



/* minimum Lua stack available to a C function */
extern const int LUA_MINSTACK;


/* predefined values in the registry */
extern const int LUA_RIDX_MAINTHREAD;
extern const int LUA_RIDX_GLOBALS;
extern const int LUA_RIDX_LAST;


/* type of numbers in Lua */
typedef float... lua_Number;


/* type for integer functions */
typedef int... lua_Integer;

/* unsigned integer type */
typedef int... lua_Unsigned;

/* type for continuation-function contexts */
typedef int... lua_KContext;	//>= 5.3


/*
** Type for C functions registered with Lua
*/
typedef int (*lua_CFunction) (lua_State *L);

/*
** Type for continuation functions
*/
typedef int (*lua_KFunction) (lua_State *L, int status, lua_KContext ctx);	//>= 5.3


/*
** Type for functions that read/write blocks when loading/dumping Lua chunks
*/
typedef const char * (*lua_Reader) (lua_State *L, void *ud, size_t *sz);

typedef int (*lua_Writer) (lua_State *L, const void *p, size_t sz, void *ud);


/*
** Type for memory-allocation functions
*/
typedef void * (*lua_Alloc) (void *ud, void *ptr, size_t osize, size_t nsize);


/*
** RCS ident string
*/
extern const char lua_ident[];


/*
** state manipulation
*/
lua_State *(lua_newstate) (lua_Alloc f, void *ud);
void       (lua_close) (lua_State *L);
lua_State *(lua_newthread) (lua_State *L);

lua_CFunction (lua_atpanic) (lua_State *L, lua_CFunction panicf);


const lua_Number *(lua_version) (lua_State *L);


/*
** basic stack manipulation
*/
int   (lua_absindex) (lua_State *L, int idx);
int   (lua_gettop) (lua_State *L);
void  (lua_settop) (lua_State *L, int idx);
void  (lua_pushvalue) (lua_State *L, int idx);
void  (lua_rotate) (lua_State *L, int idx, int n);		//>= 5.3
void  (lua_copy) (lua_State *L, int fromidx, int toidx);
int   (lua_checkstack) (lua_State *L, int n);

void  (lua_xmove) (lua_State *from, lua_State *to, int n);


/*
** access functions (stack -> C)
*/

int             (lua_isnumber) (lua_State *L, int idx);
int             (lua_isstring) (lua_State *L, int idx);
int             (lua_iscfunction) (lua_State *L, int idx);
int             (lua_isinteger) (lua_State *L, int idx);	//>= 5.3
int             (lua_isuserdata) (lua_State *L, int idx);
int             (lua_type) (lua_State *L, int idx);
const char     *(lua_typename) (lua_State *L, int tp);

lua_Number      (lua_tonumberx) (lua_State *L, int idx, int *isnum);
lua_Integer     (lua_tointegerx) (lua_State *L, int idx, int *isnum);
int             (lua_toboolean) (lua_State *L, int idx);
const char     *(lua_tolstring) (lua_State *L, int idx, size_t *len);
size_t          (lua_rawlen) (lua_State *L, int idx);
lua_CFunction   (lua_tocfunction) (lua_State *L, int idx);
void	       *(lua_touserdata) (lua_State *L, int idx);
lua_State      *(lua_tothread) (lua_State *L, int idx);
const void     *(lua_topointer) (lua_State *L, int idx);


/*
** Comparison and arithmetic functions
*/

extern const int LUA_OPADD;
extern const int LUA_OPSUB;
extern const int LUA_OPMUL;
extern const int LUA_OPMOD;
extern const int LUA_OPPOW;
extern const int LUA_OPDIV;
extern const int LUA_OPIDIV;	//>= 5.3
extern const int LUA_OPBAND;	//>= 5.3
extern const int LUA_OPBOR;		//>= 5.3
extern const int LUA_OPBXOR;	//>= 5.3
extern const int LUA_OPSHL;		//>= 5.3
extern const int LUA_OPSHR;		//>= 5.3
extern const int LUA_OPUNM;
extern const int LUA_OPBNOT;	//>= 5.3

void  (lua_arith) (lua_State *L, int op);

extern const int LUA_OPEQ;
extern const int LUA_OPLT;
extern const int LUA_OPLE;

int   (lua_rawequal) (lua_State *L, int idx1, int idx2);
int   (lua_compare) (lua_State *L, int idx1, int idx2, int op);


/*
** push functions (C -> stack)
*/
void        (lua_pushnil) (lua_State *L);
void        (lua_pushnumber) (lua_State *L, lua_Number n);
void        (lua_pushinteger) (lua_State *L, lua_Integer n);
const char *(lua_pushlstring) (lua_State *L, const char *s, size_t len);
const char *(lua_pushstring) (lua_State *L, const char *s);
const char *(lua_pushfstring) (lua_State *L, const char *fmt, ...);
void  (lua_pushcclosure) (lua_State *L, lua_CFunction fn, int n);
void  (lua_pushboolean) (lua_State *L, int b);
void  (lua_pushlightuserdata) (lua_State *L, void *p);
int   (lua_pushthread) (lua_State *L);


/*
** get functions (Lua -> stack)
*/
int (lua_getglobal) (lua_State *L, const char *name);		//>= 5.3
void (lua_getglobal) (lua_State *L, const char *name);		//<  5.3
int (lua_gettable) (lua_State *L, int idx);					//>= 5.3
void (lua_gettable) (lua_State *L, int idx);				//<  5.3
int (lua_getfield) (lua_State *L, int idx, const char *k);	//>= 5.3
void (lua_getfield) (lua_State *L, int idx, const char *k);	//<  5.3
int (lua_geti) (lua_State *L, int idx, lua_Integer n);		//>= 5.3
int (lua_rawget) (lua_State *L, int idx);					//>= 5.3
void (lua_rawget) (lua_State *L, int idx);					//<  5.3
int (lua_rawgeti) (lua_State *L, int idx, lua_Integer n);	//>= 5.3
void (lua_rawgeti) (lua_State *L, int idx, lua_Integer n);	//<  5.3
int (lua_rawgetp) (lua_State *L, int idx, const void *p);	//>= 5.3
void (lua_rawgetp) (lua_State *L, int idx, const void *p);	//<  5.3

void  (lua_createtable) (lua_State *L, int narr, int nrec);
void *(lua_newuserdata) (lua_State *L, size_t sz);
int   (lua_getmetatable) (lua_State *L, int objindex);
int  (lua_getuservalue) (lua_State *L, int idx);			//>= 5.3
void  (lua_getuservalue) (lua_State *L, int idx);			//<  5.3


/*
** set functions (stack -> Lua)
*/
void  (lua_setglobal) (lua_State *L, const char *name);
void  (lua_settable) (lua_State *L, int idx);
void  (lua_setfield) (lua_State *L, int idx, const char *k);
void  (lua_seti) (lua_State *L, int idx, lua_Integer n);	//>= 5.3
void  (lua_rawset) (lua_State *L, int idx);
void  (lua_rawseti) (lua_State *L, int idx, lua_Integer n);
void  (lua_rawsetp) (lua_State *L, int idx, const void *p);
int   (lua_setmetatable) (lua_State *L, int objindex);
void  (lua_setuservalue) (lua_State *L, int idx);


/*
** 'load' and 'call' functions (load and run Lua code)
*/
void  (lua_callk) (lua_State *L, int nargs, int nresults,		//>= 5.3
                           lua_KContext ctx, lua_KFunction k);	//>= 5.3
void lua_call (lua_State *L, int nargs, int nresults);

int   (lua_pcallk) (lua_State *L, int nargs, int nresults, int errfunc,	//>= 5.3
                            lua_KContext ctx, lua_KFunction k);			//>= 5.3
int lua_pcall (lua_State *L, int nargs, int nresults, int msgh);

int   (lua_load) (lua_State *L, lua_Reader reader, void *dt,
                          const char *chunkname, const char *mode);

int (lua_dump) (lua_State *L, lua_Writer writer, void *data, int strip);	//>= 5.3
int (lua_dump) (lua_State *L, lua_Writer writer, void *data);				//<  5.3


/*
** coroutine functions
*/
int  (lua_yieldk)     (lua_State *L, int nresults, lua_KContext ctx,	//>= 5.3
                               lua_KFunction k);						//>= 5.3
int  (lua_resume)     (lua_State *L, lua_State *from, int narg);
int  (lua_status)     (lua_State *L);
int (lua_isyieldable) (lua_State *L);	//>= 5.3

int lua_yield (lua_State *L, int nresults);


/*
** garbage-collection function and options
*/

extern const int LUA_GCSTOP;
extern const int LUA_GCRESTART;
extern const int LUA_GCCOLLECT;
extern const int LUA_GCCOUNT;
extern const int LUA_GCCOUNTB;
extern const int LUA_GCSTEP;
extern const int LUA_GCSETPAUSE;
extern const int LUA_GCSETSTEPMUL;
extern const int LUA_GCISRUNNING;

int (lua_gc) (lua_State *L, int what, int data);


/*
** miscellaneous functions
*/

int   (lua_error) (lua_State *L);

int   (lua_next) (lua_State *L, int idx);

void  (lua_concat) (lua_State *L, int n);
void  (lua_len)    (lua_State *L, int idx);

size_t   (lua_stringtonumber) (lua_State *L, const char *s);	//>= 5.3

lua_Alloc (lua_getallocf) (lua_State *L, void **ud);
void      (lua_setallocf) (lua_State *L, lua_Alloc f, void *ud);



/*
** {==============================================================
** some useful macros
** ===============================================================
*/

void *lua_getextraspace (lua_State *L);	//>= 5.3

lua_Number lua_tonumber (lua_State *L, int index);
lua_Integer lua_tointeger (lua_State *L, int index);

void lua_pop (lua_State *L, int n);

void lua_newtable (lua_State *L);

void lua_register (lua_State *L, const char *name, lua_CFunction f);

void lua_pushcfunction (lua_State *L, lua_CFunction f);

int lua_isfunction (lua_State *L, int index);
int lua_istable (lua_State *L, int index);
int lua_islightuserdata (lua_State *L, int index);
int lua_isnil (lua_State *L, int index);
int lua_isboolean (lua_State *L, int index);
int lua_isthread (lua_State *L, int index);
int lua_isnone (lua_State *L, int index);
int lua_isnoneornil (lua_State *L, int index);

void lua_pushglobaltable (lua_State *L);

const char *lua_tostring (lua_State *L, int index);


void lua_insert (lua_State *L, int index);

void lua_remove (lua_State *L, int index);

void lua_replace (lua_State *L, int index);

/* }============================================================== */


/*
** {======================================================================
** Debug API
** =======================================================================
*/


/*
** Event codes
*/
extern const int LUA_HOOKCALL;
extern const int LUA_HOOKRET;
extern const int LUA_HOOKLINE;
extern const int LUA_HOOKCOUNT;
extern const int LUA_HOOKTAILCALL;


/*
** Event masks
*/
extern const int LUA_MASKCALL;
extern const int LUA_MASKRET;
extern const int LUA_MASKLINE;
extern const int LUA_MASKCOUNT;

typedef struct lua_Debug lua_Debug;  /* activation record */


/* Functions to be called by the debugger in specific events */
typedef void (*lua_Hook) (lua_State *L, lua_Debug *ar);


int (lua_getstack) (lua_State *L, int level, lua_Debug *ar);
int (lua_getinfo) (lua_State *L, const char *what, lua_Debug *ar);
const char *(lua_getlocal) (lua_State *L, const lua_Debug *ar, int n);
const char *(lua_setlocal) (lua_State *L, const lua_Debug *ar, int n);
const char *(lua_getupvalue) (lua_State *L, int funcindex, int n);
const char *(lua_setupvalue) (lua_State *L, int funcindex, int n);

void *(lua_upvalueid) (lua_State *L, int fidx, int n);
void  (lua_upvaluejoin) (lua_State *L, int fidx1, int n1,
                                               int fidx2, int n2);

void (lua_sethook) (lua_State *L, lua_Hook func, int mask, int count);
lua_Hook (lua_gethook) (lua_State *L);
int (lua_gethookmask) (lua_State *L);
int (lua_gethookcount) (lua_State *L);


struct lua_Debug {
  int event;
  const char *name;	/* (n) */
  const char *namewhat;	/* (n) 'global', 'local', 'field', 'method' */
  const char *what;	/* (S) 'Lua', 'C', 'main', 'tail' */
  const char *source;	/* (S) */
  int currentline;	/* (l) */
  int linedefined;	/* (S) */
  int lastlinedefined;	/* (S) */
  unsigned char nups;	/* (u) number of upvalues */
  unsigned char nparams;/* (u) number of parameters */
  char isvararg;        /* (u) */
  char istailcall;	/* (t) */
  char short_src[]; /* (S) */
  /* private part */
  ...;
};

/* }====================================================================== */


/******************************************************************************
* Copyright (C) 1994-2016 Lua.org, PUC-Rio.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
******************************************************************************/