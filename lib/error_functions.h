#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H /* 防止重复包含头文件 */

/**
 * @brief 打印错误消息，但不终止程序。
 * @param format 格式化字符串，类似于 printf 的使用方式。
 * @param ... 可变参数列表，用于格式化输出。
 */
void errMsg(const char *format, ...);

#ifdef __GNUC__

/*
   这个宏用于告诉GCC编译器，当使用以下标记为 NORETURN 的函数来终止
   main() 或其他非 void 返回类型的函数时，避免发出 "控制流到达非 void 函数末尾"
   的警告。它利用了 GCC 特有的 __attribute__ ((__noreturn__)) 特性。
*/
#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif

/**
 * @brief 打印错误消息并终止程序，使用 exit(3)。
 * @param format 格式化字符串，类似于 printf 的使用方式。
 * @param ... 可变参数列表，用于格式化输出。
 */
void errExit(const char *format, ...) NORETURN;

/**
 * @brief 打印错误消息并终止程序，使用 _exit(2)。
 * @param format 格式化字符串，类似于 printf 的使用方式。
 * @param ... 可变参数列表，用于格式化输出。
 */
void err_exit(const char *format, ...) NORETURN;

/**
 * @brief 打印指定错误代码的错误消息并终止程序，使用 exit(3)。
 * @param errnum 错误代码。
 * @param format 格式化字符串，类似于 printf 的使用方式。
 * @param ... 可变参数列表，用于格式化输出。
 */
void errExitEN(int errnum, const char *format, ...) NORETURN;

/**
 * @brief 打印致命错误消息并终止程序，使用 exit(3)。
 * @param format 格式化字符串，类似于 printf 的使用方式。
 * @param ... 可变参数列表，用于格式化输出。
 */
void fatal(const char *format, ...) NORETURN;

/**
 * @brief 打印命令使用错误消息并终止程序，使用 exit(3)。
 * @param format 格式化字符串，类似于 printf 的使用方式。
 * @param ... 可变参数列表，用于格式化输出。
 */
void usageErr(const char *format, ...) NORETURN;

/**
 * @brief 打印命令行参数使用错误消息并终止程序，使用 exit(3)。
 * @param format 格式化字符串，类似于 printf 的使用方式。
 * @param ... 可变参数列表，用于格式化输出。
 */
void cmdLineErr(const char *format, ...) NORETURN;

#endif /* ERROR_FUNCTIONS_H */