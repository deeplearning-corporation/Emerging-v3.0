// include/emerging_io.h
// Emerging I/O Library
// Version 3.0

#ifndef EMERGING_IO_H
#define EMERGING_IO_H

#include "emerging.h"

// 简化输出宏 - 使用em_out前缀
#define out_char(c)    em_out_char(c)
#define out_string(s)  em_out_string(s)
#define out_int(n)     em_out_int(n)
#define out_hex(n)     em_out_hex(n)
#define out_ptr(p)     em_out_ptr(p)
#define out_newline()  em_out_newline()

// 通用输出宏（C11风格，仅在C语言中使用）
#ifdef __cplusplus
// C++使用重载
inline void out(char c) { em_out_char(c); }
inline void out(const char* s) { em_out_string(s); }
inline void out(int n) { em_out_int(n); }
inline void out(unsigned int n) { em_out_uint(n); }
#else
// C语言使用_Generic
#define out(x) _Generic((x), \
    char: em_out_char, \
    const char*: em_out_string, \
    char*: em_out_string, \
    int: em_out_int, \
    unsigned int: em_out_uint, \
    default: em_out_ptr \
    )(x)
#endif

// 输入宏
#define in_char()      em_in_char()
#define in_string(b,l) em_in_string(b,l)
#define in_int()       em_in_int()

// 控制台宏
#define set_color(f,b) em_set_color(f,b)
#define clear_screen() em_clear_screen()
#define gotoxy(x,y)    em_gotoxy(x,y)

#endif // EMERGING_IO_H