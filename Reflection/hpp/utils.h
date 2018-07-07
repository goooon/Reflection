#ifndef ZHIHE_Utils_GUARD_h__
#define ZHIHE_Utils_GUARD_h__

#include "./make.h"

#ifndef  SAFE_DELETE
#define  SAFE_DELETE(p) {if(p){del_me p;p=NULL;};}
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(a) {if(a){del_me[] a;a=NULL;}}
#endif

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) {if(p){(p)->decRef();p=NULL;}}
#endif

#ifndef ARRAY_SIZE
//#define ARRAY_SIZE(array) ((int)(sizeof(array)/sizeof(array[0])))

template <unsigned int START, unsigned int END>
struct Range
{
	Range() {}
	const static unsigned int array_size = END - START + 1;
	unsigned int operator [](unsigned int index)const { return START + index; }
};

/*template <int S,int E>
struct Range
{
const static int array_size = E - S + 1;
int operator [](int index)const {return S + index;}
};*/

template<typename T, long N>
char(&ArraySizeHelper(T(&array)[N]))[N];

template<typename RANGE>
char(&ArraySizeHelper(RANGE&))[RANGE::array_size];

#define ARRAY_SIZE(array) ((unsigned int)sizeof(ArraySizeHelper(array)))
#define ARRAY_LAST_INDEX(array) (ARRAY_SIZE(array) - 1)
#endif

/** Returns x rounded up to a multiple of 2
*/
#define MeAlign2(x)     (((x) + 1) >> 1 << 1)
/** Returns x rounded up to a multiple of 4
*/
#define MeAlign4(x)     (((x) + 3) >> 2 << 2)

#endif // ZHIHE_Utils_GUARD_h__
