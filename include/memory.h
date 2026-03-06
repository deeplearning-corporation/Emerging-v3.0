// include/memory.h
// Emerging Memory Management Library
// Version 3.0

#ifndef MEMORY_H
#define MEMORY_H

#include "emerging.h"

// 内存分配函数
void* malloc(size_t size);
void* calloc(size_t count, size_t size);
void* realloc(void* ptr, size_t new_size);
void free(void* ptr);

// 内存信息结构
typedef struct {
    size_t total_memory;
    size_t free_memory;
    size_t used_memory;
    size_t largest_free_block;
    uint32_t allocation_count;
    uint32_t free_count;
} memory_info_t;

// 内存管理函数
void memory_init(void* start, size_t size);
memory_info_t memory_get_info(void);
void memory_dump_info(void);
void* memory_align(void* ptr, size_t alignment);
int memory_check_ptr(void* ptr);

// 物理内存管理 (用于操作系统开发)
typedef struct {
    uint64_t base_addr;
    uint64_t length;
    uint32_t type;
    uint32_t reserved;
} memory_region_t;

#define MEMORY_REGION_AVAILABLE    1
#define MEMORY_REGION_RESERVED     2
#define MEMORY_REGION_ACPI         3
#define MEMORY_REGION_NVS          4

void physical_memory_init(void);
void* physical_alloc_page(void);
void physical_free_page(void* page);
int physical_alloc_region(uint64_t base, uint64_t size);
void physical_free_region(uint64_t base, uint64_t size);

// 虚拟内存管理
typedef uint64_t page_table_t;
typedef uint64_t virtual_addr_t;

#define PAGE_SIZE 4096
#define PAGE_PRESENT   (1 << 0)
#define PAGE_WRITABLE  (1 << 1)
#define PAGE_USER      (1 << 2)

void virtual_memory_init(void);
page_table_t* virtual_create_address_space(void);
void virtual_switch_address_space(page_table_t* table);
int virtual_map_page(page_table_t* table, virtual_addr_t virt, void* phys, uint32_t flags);
void virtual_unmap_page(page_table_t* table, virtual_addr_t virt);
void* virtual_phys_to_virt(void* phys);

#endif // MEMORY_H