#ifndef TLPI_HDR_H
#define TLPI_HDR_H /* 防止重复包含头文件 */

#include <sys/types.h> /* 包含许多程序使用的类型定义，如pid_t、size_t等 */
#include <stdio.h>     /* 标准输入输出函数的声明，如printf, scanf等 */
#include <stdlib.h>    /* 常用库函数的原型声明，如malloc, free, exit等，以及EXIT_SUCCESS和EXIT_FAILURE常量 */
#include <unistd.h>    /* 声明了许多系统调用的原型，如fork, exec, getpid等 */
#include <errno.h>     /* 声明了errno变量，并定义了许多错误常量 */
#include <string.h>    /* 常用的字符串处理函数的声明，如strcpy, strlen, strcmp等 */

#include "get_num.h" /* 声明了处理数值参数的函数，如getInt(), getLong() */

#include "error_functions.h" /* 声明了错误处理函数，如errMsg(), errExit()等 */

/* 定义了一个枚举类型Boolean，用于表示布尔值FALSE(0)和TRUE(1) */
typedef enum
{
    FALSE,
    TRUE
} Boolean;

/* 定义两个宏，用于计算两个值的最小值和最大值 */
#define min(m, n) ((m) < (n) ? (m) : (n))
#define max(m, n) ((m) > (n) ? (m) : (n))

#endif /* TLPI_HDR_H */