// include/stdio.h
// Emerging Standard I/O Library
// Version 3.0

#ifndef STDIO_H
#define STDIO_H

#include "emerging.h"

// 文件结构
typedef struct {
    void* handle;
    int mode;
    char* buffer;
    size_t position;
    size_t size;
    int error;
    int eof;
} FILE;

// 标准文件
extern FILE* stdin;
extern FILE* stdout;
extern FILE* stderr;

// 文件模式
#define FILE_READ   0x01
#define FILE_WRITE  0x02
#define FILE_BINARY 0x04
#define FILE_TEXT   0x08

// 文件操作
FILE* fopen(const char* filename, const char* mode);
int fclose(FILE* stream);
size_t fread(void* ptr, size_t size, size_t count, FILE* stream);
size_t fwrite(const void* ptr, size_t size, size_t count, FILE* stream);
int fseek(FILE* stream, long offset, int origin);
long ftell(FILE* stream);
void rewind(FILE* stream);
int feof(FILE* stream);
int ferror(FILE* stream);
int fflush(FILE* stream);

// 格式化I/O
int printf(const char* format, ...);
int fprintf(FILE* stream, const char* format, ...);
int sprintf(char* buffer, const char* format, ...);
int snprintf(char* buffer, size_t size, const char* format, ...);
int scanf(const char* format, ...);
int fscanf(FILE* stream, const char* format, ...);
int sscanf(const char* buffer, const char* format, ...);

// 字符I/O
int fgetc(FILE* stream);
int fputc(int c, FILE* stream);
char* fgets(char* str, int count, FILE* stream);
int fputs(const char* str, FILE* stream);
int getc(FILE* stream);
int putc(int c, FILE* stream);
int getchar(void);
int putchar(int c);

// 字符串转换
int atoi(const char* str);
long atol(const char* str);
long long atoll(const char* str);
double atof(const char* str);

#endif // STDIO_H