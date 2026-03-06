// include/string.h
// Emerging String Library
// Version 3.0

#ifndef STRING_H
#define STRING_H

#include "emerging.h"

// ×Ö·û´®³¤¶È
size_t strlen(const char* str);
size_t strnlen(const char* str, size_t maxlen);

// ×Ö·û´®¸´ÖÆ
char* strcpy(char* dest, const char* src);
char* strncpy(char* dest, const char* src, size_t count);
char* strdup(const char* src);

// ×Ö·û´®Á¬½Ó
char* strcat(char* dest, const char* src);
char* strncat(char* dest, const char* src, size_t count);

// ×Ö·û´®±È½Ï
int strcmp(const char* str1, const char* str2);
int strncmp(const char* str1, const char* str2, size_t count);
int stricmp(const char* str1, const char* str2);
int strnicmp(const char* str1, const char* str2, size_t count);

// ×Ö·û´®²éÕÒ
char* strchr(const char* str, int ch);
char* strrchr(const char* str, int ch);
char* strstr(const char* str, const char* substr);
char* strpbrk(const char* str, const char* accept);
size_t strspn(const char* str, const char* accept);
size_t strcspn(const char* str, const char* reject);

// ×Ö·û´®·Ö¸î
char* strtok(char* str, const char* delim);
char* strtok_r(char* str, const char* delim, char** saveptr);

// ÄÚ´æ²Ù×÷
void* memcpy(void* dest, const void* src, size_t n);
void* memmove(void* dest, const void* src, size_t n);
void* memset(void* dest, int c, size_t n);
int memcmp(const void* s1, const void* s2, size_t n);
void* memchr(const void* ptr, int value, size_t num);

// ×Ö·û´®×ª»»
int tolower(int c);
int toupper(int c);
char* strlwr(char* str);
char* strupr(char* str);

#endif // STRING_H