// include/emerging.h
// Emerging Programming Language Standard Library
// Version 3.0
// Completely independent from C standard library

#ifndef EMERGING_H
#define EMERGING_H

// 定义我们自己的类型，避免与标准库冲突
#ifndef EMERGING_TYPES_DEFINED
#define EMERGING_TYPES_DEFINED

// 基本整数类型
typedef unsigned char      em_uint8;
typedef unsigned short     em_uint16;
typedef unsigned int       em_uint32;
typedef unsigned long long em_uint64;

typedef signed char        em_int8;
typedef short              em_int16;
typedef int                em_int32;
typedef long long          em_int64;

typedef em_uint32          em_size;
typedef em_uint32          em_uintptr;

#endif // EMERGING_TYPES_DEFINED

// 布尔值
#define EM_TRUE  1
#define EM_FALSE 0

// Emerging语言内置函数
#ifdef __cplusplus
extern "C" {
#endif

    // 输出函数
    void em_out_char(char c);
    void em_out_string(const char* str);
    void em_out_int(int num);
    void em_out_uint(unsigned int num);
    void em_out_hex(unsigned int num);
    void em_out_ptr(const void* ptr);
    void em_out_newline(void);

    // 输入函数
    char em_in_char(void);
    char* em_in_string(char* buffer, int maxlen);
    int em_in_int(void);

    // 底层端口操作
    em_uint8 em_inb(em_uint16 port);
    void em_outb(em_uint16 port, em_uint8 value);
    em_uint16 em_inw(em_uint16 port);
    void em_outw(em_uint16 port, em_uint16 value);
    em_uint32 em_inl(em_uint16 port);
    void em_outl(em_uint16 port, em_uint32 value);

    // 内存操作
    void* em_memset(void* dest, int value, em_size size);
    void* em_memcpy(void* dest, const void* src, em_size size);
    int em_memcmp(const void* ptr1, const void* ptr2, em_size size);
    void* em_memmove(void* dest, const void* src, em_size size);

    // 内存分配
    void* em_malloc(em_size size);
    void* em_calloc(em_size count, em_size size);
    void em_free(void* ptr);

    // 字符串操作
    em_size em_strlen(const char* str);
    char* em_strcpy(char* dest, const char* src);
    char* em_strncpy(char* dest, const char* src, em_size n);
    int em_strcmp(const char* str1, const char* str2);
    int em_strncmp(const char* str1, const char* str2, em_size n);
    char* em_strcat(char* dest, const char* src);
    char* em_strncat(char* dest, const char* src, em_size n);
    char* em_strchr(const char* str, int ch);
    char* em_strstr(const char* str, const char* substr);

    // 系统调用
    void em_system_halt(void);
    void em_system_reboot(void);
    void em_system_shutdown(void);
    void em_system_beep(em_uint32 freq, em_uint32 duration);

    // 控制台
    void em_set_color(int foreground, int background);
    void em_clear_screen(void);
    void em_gotoxy(int x, int y);

    // 定时器
    em_uint32 em_timer_get_ticks(void);
    void em_timer_sleep(em_uint32 milliseconds);

#ifdef __cplusplus
}
#endif

// 端口定义
#define EM_KEYBOARD_DATA_PORT    0x60
#define EM_KEYBOARD_STATUS_PORT  0x64
#define EM_COM1_PORT             0x3F8
#define EM_VGA_PORT              0x3D4
#define EM_PIC_MASTER_PORT       0x20
#define EM_PIC_SLAVE_PORT        0xA0

// 颜色定义
#define EM_COLOR_BLACK     0
#define EM_COLOR_BLUE      1
#define EM_COLOR_GREEN     2
#define EM_COLOR_CYAN      3
#define EM_COLOR_RED       4
#define EM_COLOR_MAGENTA   5
#define EM_COLOR_BROWN     6
#define EM_COLOR_LIGHT_GRAY 7
#define EM_COLOR_DARK_GRAY 8
#define EM_COLOR_LIGHT_BLUE 9
#define EM_COLOR_LIGHT_GREEN 10
#define EM_COLOR_LIGHT_CYAN 11
#define EM_COLOR_LIGHT_RED 12
#define EM_COLOR_LIGHT_MAGENTA 13
#define EM_COLOR_YELLOW    14
#define EM_COLOR_WHITE     15

#endif // EMERGING_H