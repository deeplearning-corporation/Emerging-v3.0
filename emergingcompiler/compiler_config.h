// emergingcompiler/compiler_config.h
// Emerging Compiler Configuration
// Version 3.0

#ifndef COMPILER_CONFIG_H
#define COMPILER_CONFIG_H

// 编译器版本
#define EMERGING_VERSION_MAJOR 3
#define EMERGING_VERSION_MINOR 0
#define EMERGING_VERSION_PATCH 0

// 目标平台
#define TARGET_X86     1
#define TARGET_X64     2
#define TARGET_ARM     3

// 输出格式
#define FORMAT_ELF     1
#define FORMAT_PE      2
#define FORMAT_BIN     3
#define FORMAT_COM     4

// 优化级别
#define OPT_NONE       0
#define OPT_SIZE       1
#define OPT_SPEED      2

// 默认配置
#define DEFAULT_TARGET TARGET_X86
#define DEFAULT_FORMAT FORMAT_PE
#define DEFAULT_OPT    OPT_SPEED

#endif // COMPILER_CONFIG_H