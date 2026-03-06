// include/system.h
// Emerging Language System Header
// Version 3.0

#ifndef SYSTEM_H
#define SYSTEM_H

// 底层系统调用声明
#ifdef __cplusplus
extern "C" {
#endif

    void outb(unsigned short port, unsigned char value);
    unsigned char inb(unsigned short port);
    void outw(unsigned short port, unsigned short value);
    unsigned short inw(unsigned short port);
    void outl(unsigned short port, unsigned int value);
    unsigned int inl(unsigned short port);

#ifdef __cplusplus
}
#endif

// 内存操作
void* memset(void* dest, int value, unsigned long long size);
void* memcpy(void* dest, const void* src, unsigned long long size);
int memcmp(const void* ptr1, const void* ptr2, unsigned long long size);

// 字符串操作
unsigned long long strlen(const char* str);
char* strcpy(char* dest, const char* src);
int strcmp(const char* str1, const char* str2);
char* strcat(char* dest, const char* src);

// 系统调用
void system_halt(void);
void system_reboot(void);
void system_shutdown(void);

#endif // SYSTEM_H