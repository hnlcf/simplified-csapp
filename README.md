# CSAPP

这是一个学习 **CSAPP** 的代码练习，学习过程参考 B 站视频[深入理解计算机系统](https://space.bilibili.com/4564101/video?tid=0&page=1&keyword=&order=pubdate)，在此十分感谢 Up 主`yaaangmin`的视频教学。

## Content

- [CSAPP](#csapp)
  - [Content](#content)
  - [Road Map](#road-map)
  - [Learning process](#learning-process)
    - [Chapter 03 - Machine-level Representation of C Programs](#chapter-03---machine-level-representation-of-c-programs)
      - [2021-12-4](#2021-12-4)
      - [2021-12-5](#2021-12-5)
      - [2021-12-6](#2021-12-6)

## Road Map

1. A simple simulation
2. cache
   - SRAM
   - LRU
3. mmu--memory management unit
   - pagetable
   - TLB
4. linker
5. linux kernel
   - process
   - fork()
   - kill()
   - wait()
   - malloc()
     - size list
     - RBT
   - free()

## Learning process

学习历程按 **CSAPP** 各个篇章的完成日期排列。

### Chapter 03 - Machine-level Representation of C Programs

- register
- instruction
- assembly

#### 2021-12-4

完成寄存器模拟器，利用结构体和联合体来描述寄存器。

完成指令(instruction)的数据结构 `INST_STRUCT/inst_t`，包括指令操作符 `Operator/op_t`，操作数 `Operand/od_t`以及操作数的类型构成 `OperandType/od_type_t` 。

设计CPU指令周期，利用句柄表，以指令函数名枚举为索引，对指令函数(具有相同类型函数指针)进行初始化注册。执行了第一条汇编指令。

#### 2021-12-5

封装实现了对内存读写接口 `read64bits_dram(), write64bits_dram()` 便于统一，其中读写的数据格式标准化为 `uint64_t` 。

添加了便于调试的 `print_register(), print_stack()` 函数来打印信息。

完成了 `call` 指令。

#### 2021-12-6

树与归约与栈

Reduce --> Tree --> Stack

```txt
// expr --> value

e.g. 1 + 2 + 3

--> [1] + 2 + 3
--> [1, +] 2 + 3
--> [1, +, 2] + 3
--> [3] + 3
--> [3, +] 3
--> [3, +, 3]
--> [6]

```

实现了 `push_reg pop_reg ret mov_reg_mem mov_mem_reg` 指令。
