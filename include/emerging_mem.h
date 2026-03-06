// include/emerging_mem.h
// Emerging Memory Management Library
// Version 3.0

#ifndef EMERGING_MEM_H
#define EMERGING_MEM_H

#include "emerging.h"

// ÄÚ´æ²Ù×÷ºê
#define memset(d,v,s)  em_memset(d,v,s)
#define memcpy(d,s,n)  em_memcpy(d,s,n)
#define memcmp(p1,p2,n) em_memcmp(p1,p2,n)
#define memmove(d,s,n) em_memmove(d,s,n)

// ÄÚ´æ·ÖÅäºê
#define malloc(s)      em_malloc(s)
#define calloc(c,s)    em_calloc(c,s)
#define free(p)        em_free(p)

// ×Ö·û´®²Ù×÷ºê
#define strlen(s)      em_strlen(s)
#define strcpy(d,s)    em_strcpy(d,s)
#define strncpy(d,s,n) em_strncpy(d,s,n)
#define strcmp(s1,s2)  em_strcmp(s1,s2)
#define strncmp(s1,s2,n) em_strncmp(s1,s2,n)
#define strcat(d,s)    em_strcat(d,s)
#define strncat(d,s,n) em_strncat(d,s,n)
#define strchr(s,c)    em_strchr(s,c)
#define strstr(s,sub)  em_strstr(s,sub)

#endif // EMERGING_MEM_H