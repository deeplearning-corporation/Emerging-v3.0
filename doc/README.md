<div align="center">
<img width="198" height="193" alt="Emerging-Logo" src="https://github.com/user-attachments/assets/00a3dae5-8d76-422b-8c6c-bbbcc4f5f9d6" />

  <h1>Emerging 编程语言</h1>
  <h3>Emerging 编程语言 2.0 与 1.0 的升级版</h3>

  <p align="center">
    <a href="https://deeplearning-corporation.github.io">
      <img src="https://img.shields.io/badge/Deep%20Learning%20Corporation-官方网站-2ea44f?style=flat-square" alt="Deep Learning Corporation 官网">
    </a>
  </p>
</div>

## 概述
Emerging是一种用于操作系统开发的高级编程语言，可以直接接触底层硬件，同时保持高级语言的易用性。

## 特性
- 直接硬件访问 (inb/outb)
- 内存管理
- 多任务支持
- 中断处理
- DMA操作
- PCI配置

## 目录结构
- `include/` - 头文件
- `lib/` - 库文件
- `doc/` - 文档
- `emergingcompiler/` - 编译器核心

## 快速开始

### Hello World
```emerging
using "iostream.h"

out("Hello, Emerging World!\n");