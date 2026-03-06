// lib/libemerging.cpp
// Emerging Language Library Implementation
// Version 3.0
// Fixed with proper includes

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cstdlib>  // 添加这个头文件用于 exit()
#include <cstdio>   // 用于 printf, getchar, scanf
#include <cstdarg>  // 用于可变参数
#include <cstring>  // 用于 strlen 等（但我们会避免使用）

// 包含Emerging头文件
#include "../include/emerging.h"
#include "../include/emerging_io.h"
#include "../include/emerging_mem.h"
#include "../include/emerging_sys.h"

// ==================== 输出函数实现 ====================

void em_out_char(char c) {
    printf("%c", c);
}

void em_out_string(const char* str) {
    if (str) {
        printf("%s", str);
    }
}

void em_out_int(int num) {
    printf("%d", num);
}

void em_out_uint(unsigned int num) {
    printf("%u", num);
}

void em_out_hex(unsigned int num) {
    printf("0x%X", num);
}

void em_out_ptr(const void* ptr) {
    printf("%p", ptr);
}

void em_out_newline(void) {
    printf("\n");
}

// ==================== 输入函数实现 ====================

char em_in_char(void) {
    return getchar();
}

char* em_in_string(char* buffer, int maxlen) {
    if (buffer && maxlen > 0) {
        fgets(buffer, maxlen, stdin);
        // 移除换行符
        size_t len = 0;
        while (buffer[len] != '\0') len++;
        if (len > 0 && buffer[len-1] == '\n') {
            buffer[len-1] = '\0';
        }
        return buffer;
    }
    return nullptr;
}

int em_in_int(void) {
    int value;
    scanf("%d", &value);
    return value;
}

// ==================== 内存操作实现 ====================

void* em_memset(void* dest, int value, em_size size) {
    if (dest) {
        unsigned char* d = (unsigned char*)dest;
        for (em_size i = 0; i < size; i++) {
            d[i] = (unsigned char)value;
        }
    }
    return dest;
}

void* em_memcpy(void* dest, const void* src, em_size size) {
    if (dest && src) {
        unsigned char* d = (unsigned char*)dest;
        const unsigned char* s = (const unsigned char*)src;
        for (em_size i = 0; i < size; i++) {
            d[i] = s[i];
        }
    }
    return dest;
}

int em_memcmp(const void* ptr1, const void* ptr2, em_size size) {
    if (!ptr1 && !ptr2) return 0;
    if (!ptr1) return -1;
    if (!ptr2) return 1;
    
    const unsigned char* p1 = (const unsigned char*)ptr1;
    const unsigned char* p2 = (const unsigned char*)ptr2;
    
    for (em_size i = 0; i < size; i++) {
        if (p1[i] != p2[i]) {
            return (p1[i] < p2[i]) ? -1 : 1;
        }
    }
    return 0;
}

void* em_memmove(void* dest, const void* src, em_size size) {
    if (!dest || !src) return dest;
    
    unsigned char* d = (unsigned char*)dest;
    const unsigned char* s = (const unsigned char*)src;
    
    if (d < s) {
        // 正向复制
        for (em_size i = 0; i < size; i++) {
            d[i] = s[i];
        }
    } else if (d > s) {
        // 反向复制
        for (em_size i = size; i > 0; i--) {
            d[i-1] = s[i-1];
        }
    }
    
    return dest;
}

// ==================== 内存分配实现 ====================

#define EM_HEAP_SIZE (1024 * 1024) // 1MB堆
static unsigned char em_heap[EM_HEAP_SIZE];
static em_size em_heap_used = 0;

void* em_malloc(em_size size) {
    if (size == 0) return nullptr;
    
    // 对齐到8字节
    size = (size + 7) & ~7;
    
    if (em_heap_used + size > EM_HEAP_SIZE) {
        return nullptr;
    }
    
    void* ptr = em_heap + em_heap_used;
    em_heap_used += size;
    return ptr;
}

void* em_calloc(em_size count, em_size size) {
    em_size total = count * size;
    void* ptr = em_malloc(total);
    if (ptr) {
        em_memset(ptr, 0, total);
    }
    return ptr;
}

void em_free(void* ptr) {
    // 简单实现，不实际释放
    (void)ptr;
}

// ==================== 字符串操作实现 ====================

em_size em_strlen(const char* str) {
    if (!str) return 0;
    em_size len = 0;
    while (str[len]) len++;
    return len;
}

char* em_strcpy(char* dest, const char* src) {
    if (!dest || !src) return dest;
    
    char* d = dest;
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}

char* em_strncpy(char* dest, const char* src, em_size n) {
    if (!dest || !src || n == 0) return dest;
    
    char* d = dest;
    em_size i;
    for (i = 0; i < n && src[i]; i++) {
        d[i] = src[i];
    }
    for (; i < n; i++) {
        d[i] = '\0';
    }
    return dest;
}

int em_strcmp(const char* str1, const char* str2) {
    if (!str1 && !str2) return 0;
    if (!str1) return -1;
    if (!str2) return 1;
    
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    
    return (unsigned char)*str1 - (unsigned char)*str2;
}

int em_strncmp(const char* str1, const char* str2, em_size n) {
    if (n == 0) return 0;
    if (!str1 && !str2) return 0;
    if (!str1) return -1;
    if (!str2) return 1;
    
    for (em_size i = 0; i < n; i++) {
        if (str1[i] != str2[i]) {
            return (unsigned char)str1[i] - (unsigned char)str2[i];
        }
        if (str1[i] == '\0') break;
    }
    return 0;
}

char* em_strcat(char* dest, const char* src) {
    if (!dest || !src) return dest;
    
    char* d = dest;
    while (*d) d++;
    while (*src) {
        *d++ = *src++;
    }
    *d = '\0';
    return dest;
}

char* em_strncat(char* dest, const char* src, em_size n) {
    if (!dest || !src || n == 0) return dest;
    
    char* d = dest;
    while (*d) d++;
    
    em_size i;
    for (i = 0; i < n && src[i]; i++) {
        d[i] = src[i];
    }
    d[i] = '\0';
    return dest;
}

char* em_strchr(const char* str, int ch) {
    if (!str) return nullptr;
    
    while (*str) {
        if (*str == ch) {
            return (char*)str;
        }
        str++;
    }
    return (ch == '\0') ? (char*)str : nullptr;
}

char* em_strstr(const char* str, const char* substr) {
    if (!str || !substr) return nullptr;
    if (*substr == '\0') return (char*)str;
    
    while (*str) {
        const char* s1 = str;
        const char* s2 = substr;
        
        while (*s1 && *s2 && *s1 == *s2) {
            s1++;
            s2++;
        }
        
        if (*s2 == '\0') {
            return (char*)str;
        }
        str++;
    }
    return nullptr;
}

// ==================== 系统函数实现 ====================

em_uint8 em_inb(em_uint16 port) {
    // Windows下模拟
    (void)port;
    return 0;
}

void em_outb(em_uint16 port, em_uint8 value) {
    (void)port;
    (void)value;
}

em_uint16 em_inw(em_uint16 port) {
    (void)port;
    return 0;
}

void em_outw(em_uint16 port, em_uint16 value) {
    (void)port;
    (void)value;
}

em_uint32 em_inl(em_uint16 port) {
    (void)port;
    return 0;
}

void em_outl(em_uint16 port, em_uint32 value) {
    (void)port;
    (void)value;
}

void em_system_halt(void) {
    while (1) {
        Sleep(1000);
    }
}

void em_system_reboot(void) {
    exit(0);
}

void em_system_shutdown(void) {
    exit(0);
}

void em_system_beep(em_uint32 freq, em_uint32 duration) {
    Beep(freq, duration);
}

// ==================== 控制台函数实现 ====================

void em_set_color(int foreground, int background) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        SetConsoleTextAttribute(hConsole, (WORD)(foreground | (background << 4)));
    }
}

void em_clear_screen(void) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        DWORD count;
        DWORD cellCount;
        COORD homeCoords = {0, 0};
        
        if (GetConsoleScreenBufferInfo(hConsole, &csbi)) {
            cellCount = csbi.dwSize.X * csbi.dwSize.Y;
            FillConsoleOutputCharacter(hConsole, ' ', cellCount, homeCoords, &count);
            FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cellCount, homeCoords, &count);
            SetConsoleCursorPosition(hConsole, homeCoords);
        }
    }
}

void em_gotoxy(int x, int y) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hConsole != INVALID_HANDLE_VALUE) {
        COORD coord;
        coord.X = (SHORT)x;
        coord.Y = (SHORT)y;
        SetConsoleCursorPosition(hConsole, coord);
    }
}

// ==================== 定时器函数 ====================

em_uint32 em_timer_get_ticks(void) {
    return GetTickCount();
}

void em_timer_sleep(em_uint32 milliseconds) {
    Sleep(milliseconds);
}

// ==================== DLL入口 ====================

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD  ul_reason_for_call,
                      LPVOID lpReserved) {
    (void)hModule;
    (void)lpReserved;
    
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
