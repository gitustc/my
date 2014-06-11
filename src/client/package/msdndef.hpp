#ifndef _msdn_def_hpp_
#define _msdn_def_hpp_


#include <stdint.h>

typedef void        VOID,       *PVOID,     *LPVOID; 

typedef int32_t     BOOL,       *PBOOL,     *LPBOOL; 
typedef uint8_t     BOOLEAN,    *PBOOLEAN;

typedef uint8_t     BYTE,       *PBYTE,     *LPBYTE; 
typedef uint16_t    WORD,       *PWORD,     *LPWORD; 
typedef uint32_t    DWORD,      *PDWORD,    *LPDWORD; 

typedef float       FLOAT;
typedef double      DOUBLE; 

typedef char        CHAR,       *PCHAR; 
typedef int16_t     SHORT; 
typedef int32_t     INT,        *LPINT; 
typedef int32_t     LONG,       *PLONG,     *LPLONG; 


typedef struct _RECT {
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *PRECT;



#ifdef FALSE
#undef FALSE
#endif
#define FALSE 0

#ifdef TRUE
#undef TRUE
#endif
#define TRUE  1


#endif
