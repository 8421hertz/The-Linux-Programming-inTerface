#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc" /* 包含了错误名称数组 'ename' 和常量 'MAX_ENAME' 的定义 */

#define MAX_ENAME 100 // 假设 100 是适当的值

#ifdef __GNUC__
__attribute__ ((__noreturn__)) // 指定函数不会返回给调用者。用于优化目的，例如省略函数返回后的代码。
#endif

/**
 * @brief 终止程序，根据条件决定是否生成 core dump 或调用不同的退出函数。
 * @param useExit3 如果为真，则调用 exit(3)，否则调用 _exit(2)。
 */
static void terminate(Boolean useExit3)
{
    char *s;
    // 检查环境变量 EF_DUMPCORE 是否已定义且非空。
    // 如果定义了，调用 abort() 来转储核心（生成 core dump）。
    // 如果没有定义，根据 'useExit3' 的值选择调用 exit(3) 或 _exit(2) 以终止程序。
    s = getenv("EF_DUMPCORE");
    if (s != NULL && *s != '\0')
        abort();
    else if (useExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

/**
 * @brief 格式化错误消息并输出到标准错误输出，必要时刷新输出缓冲区。
 * @param useErr 如果为真，包含错误代码及其描述在输出中。
 * @param err 错误代码。
 * @param flushStdout 如果为真，刷新标准输出缓冲区。
 * @param format 格式化字符串，类似 printf。
 * @param ap 可变参数列表，用于格式化输出。
 */
static void outputError(Boolean useErr, int err, Boolean flushStdout,
                        const char *format, va_list ap)
{
    #define BUF_SIZE 500
    char buf[BUF_SIZE], userMsg[BUF_SIZE], errText[BUF_SIZE];
    
    // 格式化用户消息，将其存储在 userMsg 中。
    vsnprintf(userMsg, BUF_SIZE, format, ap);
    
    // 如果 useErr 为真，则将错误代码及其描述格式化到 errText 中。
    // 否则，将 errText 设置为 ":"。
    if (useErr)
        snprintf(errText, BUF_SIZE, " [%s %s]",
                 (err > 0 && err <= MAX_ENAME) ?
                 ename[err] : "?UNKNOWN?", strerror(err));
    else
        snprintf(errText, BUF_SIZE, ":");
    
    // 将最终的错误消息格式化到 buf 中，包括错误描述和用户消息。
    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, userMsg);

    // 如果需要，刷新标准输出缓冲区。
    if (flushStdout)
        fflush(stdout);
    
    // 将错误消息输出到标准错误输出，并刷新标准错误输出缓冲区。
    fputs(buf, stderr);
    fflush(stderr);
}

/**
 * @brief 打印错误消息，并保持 errno 不变。
 * @param format 格式化字符串，类似 printf。
 */
void errMsg(const char *format, ...)
{
    va_list argList;
    int savedErrno;
    
    savedErrno = errno; /* 保存当前的 errno，以防被修改 */
    va_start(argList, format);
    
    // 调用 outputError 输出错误消息，包括错误代码。
    outputError(TRUE, errno, TRUE, format, argList);
    
    va_end(argList);
    errno = savedErrno; /* 恢复 errno */
}

/**
 * @brief 打印错误消息后终止程序，使用 exit(3)。
 * @param format 格式化字符串，类似 printf。
 */
void errExit(const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    
    // 调用 outputError 输出错误消息，并终止程序。
    outputError(TRUE, errno, TRUE, format, argList);
    
    va_end(argList);
    terminate(TRUE);
}

/**
 * @brief 打印错误消息后终止程序，使用 _exit(2)。
 * @param format 格式化字符串，类似 printf。
 */
void err_exit(const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    
    // 调用 outputError 输出错误消息，并终止程序。
    outputError(TRUE, errno, FALSE, format, argList);
    
    va_end(argList);
    terminate(FALSE);
}

/**
 * @brief 打印指定错误代码的错误消息后终止程序，使用 exit(3)。
 * @param errnum 错误代码。
 * @param format 格式化字符串，类似 printf。
 */
void errExitEN(int errnum, const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    
    // 调用 outputError 输出错误消息，并终止程序。
    outputError(TRUE, errnum, TRUE, format, argList);
    
    va_end(argList);
    terminate(TRUE);
}

/**
 * @brief 打印致命错误消息后终止程序，使用 exit(3)。
 * @param format 格式化字符串，类似 printf。
 */
void fatal(const char *format, ...)
{
    va_list argList;
    va_start(argList, format);
    
    // 调用 outputError 输出错误消息，并终止程序。
    outputError(FALSE, 0, TRUE, format, argList);
    
    va_end(argList);
    terminate(TRUE);
}

/**
 * @brief 打印命令使用错误消息后终止程序，使用 exit(3)。
 * @param format 格式化字符串，类似 printf。
 */
void usageErr(const char *format, ...)
{
    va_list argList;
    fflush(stdout); /* 刷新标准输出缓冲区 */
    fprintf(stderr, "Usage: ");
    
    va_start(argList, format);
    
    // 将命令使用错误消息输出到标准错误输出。
    vfprintf(stderr, format, argList);
    
    va_end(argList);
    fflush(stderr); /* 刷新标准错误缓冲区 */
    exit(EXIT_FAILURE);
}

/**
 * @brief 打印命令行参数使用错误消息后终止程序，使用 exit(3)。
 * @param format 格式化字符串，类似 printf。
 */
void cmdLineErr(const char *format, ...)
{
    va_list argList;
    fflush(stdout); /* 刷新标准输出缓冲区 */
    fprintf(stderr, "Command-line usage error: ");
    
    va_start(argList, format);
    
    // 将命令行参数使用错误消息输出到标准错误输出。
    vfprintf(stderr, format, argList);
    
    va_end(argList);
    fflush(stderr); /* 刷新标准错误缓冲区 */
    exit(EXIT_FAILURE);
}

