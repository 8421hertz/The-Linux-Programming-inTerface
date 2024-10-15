#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "get_num.h"

/**
 * @brief 辅助函数，用于处理错误情况并退出程序。
 * @param fname 调用此函数的函数名，用于标识错误来源。
 * @param msg 错误消息的描述。
 * @param arg 引起错误的文本（如果有）。
 * @param name 引起错误的变量或参数名（如果有）。
 */
static void gnFail(const char *fname, const char *msg, const char *arg, const char *name)
{
    fprintf(stderr, "%s error", fname); // 打印错误信息，包含函数名
    if (name != NULL)
        fprintf(stderr, " (in %s)", name); // 如果提供了name，输出附加信息
    fprintf(stderr, ": %s\n", msg);        // 输出错误消息
    if (arg != NULL && *arg != '\0')
        fprintf(stderr, " offending text: %s\n", arg); // 如果有问题的文本，输出它
    exit(EXIT_FAILURE);                                // 退出程序
}

/**
 * @brief 将字符串转换为长整型数值，并根据标志执行额外的检查。
 * @param fname 调用此函数的函数名，用于标识错误来源。
 * @param arg 待转换的字符串。
 * @param flags 控制转换行为的标志。
 * @param name 引起错误的变量或参数名（如果有）。
 * @return 转换后的长整型数值。
 */
static long getNum(const char *fname, const char *arg, int flags, const char *name)
{
    long res;
    char *endptr;
    int base;

    // 检查arg是否为空或空字符串
    if (arg == NULL || *arg == '\0')
        gnFail(fname, "null or empty string", arg, name);

    // 设置数字转换的基数，依据flags
    base = (flags & GN_ANY_BASE) ? 0 : (flags & GN_BASE_8) ? 8
                                   : (flags & GN_BASE_16)  ? 16
                                                           : 10;

    errno = 0;                        // 重置errno以检测strtol的错误
    res = strtol(arg, &endptr, base); // 将字符串转换为长整型数字

    // 检查strtol是否发生错误
    if (errno != 0)
        gnFail(fname, "strtol() failed", arg, name);

    // 检查是否有非数字字符
    if (*endptr != '\0')
        gnFail(fname, "nonnumeric characters", arg, name);

    // 检查标志，确保值不为负
    if ((flags & GN_NONNEG) && res < 0)
        gnFail(fname, "negative value not allowed", arg, name);

    // 检查标志，确保值大于0
    if ((flags & GN_GT_0) && res <= 0)
        gnFail(fname, "value must be > 0", arg, name);

    return res; // 返回转换后的值
}

/**
 * @brief 获取长整型数字，封装了getNum函数。
 * @param arg 待转换的字符串。
 * @param flags 控制转换行为的标志。
 * @param name 引起错误的变量或参数名（如果有）。
 * @return 转换后的长整型数值。
 */
long getLong(const char *arg, int flags, const char *name)
{
    return getNum("getLong", arg, flags, name); // 调用getNum函数，获取长整型
}

/**
 * @brief 获取整型数字，封装了getNum函数，并进行范围检查。
 * @param arg 待转换的字符串。
 * @param flags 控制转换行为的标志。
 * @param name 引起错误的变量或参数名（如果有）。
 * @return 转换后的整型数值。
 */
int getInt(const char *arg, int flags, const char *name)
{
    long res;
    res = getNum("getInt", arg, flags, name); // 调用getNum函数，获取长整型

    // 检查结果是否超出整型范围
    if (res > INT_MAX || res < INT_MIN)
        gnFail("getInt", "integer out of range", arg, name);

    return (int)res; // 转换为整型并返回
}