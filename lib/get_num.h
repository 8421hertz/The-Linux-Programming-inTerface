#ifndef GET_NUM_H
#define GET_NUM_H /* 防止重复包含头文件 */

#define GN_NONNEG 01 /* 值必须 >= 0 */
#define GN_GT_0 02   /* 值必须 > 0 */

/* 默认情况下，整数是十进制的 */
#define GN_ANY_BASE 0100 /* 可以使用任何进制 - 类似于 strtol(3) */
#define GN_BASE_8 0200   /* 值以八进制表示 */
#define GN_BASE_16 0400  /* 值以十六进制表示 */

/**
 * @brief 将字符串转换为长整型数值，支持多种进制和标志。
 * @param arg 待转换的字符串。
 * @param flags 控制转换行为的标志（如进制选择、非负数等）。
 * @param name 用于标识参数或变量的名称（可用于错误信息中）。
 * @return 转换后的长整型数值。
 */
long getLong(const char *arg, int flags, const char *name);

/**
 * @brief 将字符串转换为整型数值，支持多种进制和标志。
 * @param arg 待转换的字符串。
 * @param flags 控制转换行为的标志（如进制选择、非负数等）。
 * @param name 用于标识参数或变量的名称（可用于错误信息中）。
 * @return 转换后的整型数值。
 */
int getInt(const char *arg, int flags, const char *name);

#endif /* GET_NUM_H */