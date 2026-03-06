// include/iostream.h
// Emerging I/O Stream Library
// Version 3.0

#ifndef IOSTREAM_H
#define IOSTREAM_H

#include "emerging.h"

// 输出函数重载
#define out(x) _Generic((x), \
    char: out_char, \
    const char*: out_string, \
    char*: out_string, \
    int: out_int, \
    unsigned int: out_uint, \
    default: out_ptr \
    )(x)

// 输入函数
#define in(type) _Generic((type), \
    int: in_int, \
    char: in_char, \
    default: in_string \
    )

// 控制台颜色
#define COLOR_BLACK     0
#define COLOR_BLUE      1
#define COLOR_GREEN     2
#define COLOR_CYAN      3
#define COLOR_RED       4
#define COLOR_MAGENTA   5
#define COLOR_BROWN     6
#define COLOR_LIGHT_GRAY 7
#define COLOR_DARK_GRAY 8
#define COLOR_LIGHT_BLUE 9
#define COLOR_LIGHT_GREEN 10
#define COLOR_LIGHT_CYAN 11
#define COLOR_LIGHT_RED 12
#define COLOR_LIGHT_MAGENTA 13
#define COLOR_YELLOW    14
#define COLOR_WHITE     15

// 控制台函数
void set_color(int foreground, int background);
void clear_screen(void);
void gotoxy(int x, int y);

#endif // IOSTREAM_H