#ifndef EF_BTYPE_H
#define EF_BTYPE_H

#ifdef __linux
#include <sys/types.h>
#endif



#ifdef __linux
typedef	u_int64_t	uint64;
typedef	int64_t		sint64;
typedef	int64_t		int64;
typedef	u_int32_t	uint32;
typedef	int32_t		sint32;
typedef	int32_t		int32;
typedef	u_int16_t	uint16;
typedef	int16_t		sint16;
typedef	int16_t		int16;
typedef	u_int8_t	uint8;
typedef	int8_t		sint8;
typedef	int8_t		int8;
#else
typedef unsigned long long  uint64;
typedef long long           sint64;
typedef long long           int64;
typedef unsigned long       ulong;
typedef unsigned int        uint32;
typedef int                 sint32;
typedef int                 int32;
typedef unsigned short int  uint16;
typedef short int           sint16;
typedef short int           int16;
typedef unsigned char       uint8;
typedef char                sint8;
typedef char                int8;
#endif


#endif

