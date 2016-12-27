#ifndef ZHIHE_GUARD_trace_h__
#define ZHIHE_GUARD_trace_h__

#include "./types.h"
#include <stdio.h>

#define  printlog(l, fl, fmt, ...) printf(l);printf(fmt);printf("\r\n", fl);

#define _QUOTE_INPLACE_(x) #x
#define QUOTE(x) _QUOTE_INPLACE_(x)
#define __FILE__LINE__ &__FILE__"(" QUOTE(__LINE__) ")"

#define LOG_E(...) printf(__VA_ARGS__);printf("\r\n");//{printlog("E:",__FILE__LINE__,__VA_ARGS__);}
#define LOG_I(...) printf(__VA_ARGS__);printf("\r\n");//{printlog("I:",__FILE__LINE__,__VA_ARGS__);}
#define LOG_P(...) printf(__VA_ARGS__);printf("\r\n");//{printf(__VA_ARGS__);}
#define LOG_D(d,...) {int tmp = d + 1;while(tmp--)printf("  ");printf(__VA_ARGS__);printf("\r\n");}//{printf(__VA_ARGS__);}
#define LOG_F(...) printf(__VA_ARGS__);printf("\r\n");
#define LOG_A(expr,...) {if(!(expr)){LOG_F(__VA_ARGS__);}}
#define DebugCode(...)  __VA_ARGS__

#endif // GUARD_trace_h__
