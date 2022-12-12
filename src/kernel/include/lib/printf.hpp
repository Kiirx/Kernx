#ifndef PRINTF_H_
#define PRINTF_H_

#ifdef __cplusplus
# include <stdarg.h>
# include <stddef.h>
extern "C" {
#else
# include <stdarg.h>
# include <stddef.h>
#endif

#ifdef __GNUC__
# define ATTR_PRINTF(one_based_format_index, first_arg) \
__attribute__((format(__printf__, (one_based_format_index), (first_arg))))
# define ATTR_VPRINTF(one_based_format_index) ATTR_PRINTF((one_based_format_index), 0)
#else
# define ATTR_PRINTF((one_based_format_index), (first_arg))
# define ATTR_VPRINTF(one_based_format_index)
#endif

#ifndef PRINTF_ALIAS_STANDARD_FUNCTION_NAMES
#define PRINTF_ALIAS_STANDARD_FUNCTION_NAMES 1 /* Forced this to 0, because it wouldn't work the intended way, probably just me being stupid */
#endif

#if PRINTF_ALIAS_STANDARD_FUNCTION_NAMES
# define printf_    printf
# define sprintf_   sprintf
# define vsprintf_  vsprintf
# define snprintf_  snprintf
# define vsnprintf_ vsnprintf
# define vprintf_   vprintf
#endif

#ifndef PRINTF_VISIBILITY
#define PRINTF_VISIBILITY
#endif

PRINTF_VISIBILITY
void putchar_(char c);

PRINTF_VISIBILITY
int printf_(const char* format, ...) ATTR_PRINTF(1, 2);
PRINTF_VISIBILITY
int vprintf_(const char* format, va_list arg) ATTR_VPRINTF(1);


PRINTF_VISIBILITY
int  sprintf_(char* s, const char* format, ...) ATTR_PRINTF(2, 3);
PRINTF_VISIBILITY
int vsprintf_(char* s, const char* format, va_list arg) ATTR_VPRINTF(2);


PRINTF_VISIBILITY
int  snprintf_(char* s, size_t count, const char* format, ...) ATTR_PRINTF(3, 4);
PRINTF_VISIBILITY
int vsnprintf_(char* s, size_t count, const char* format, va_list arg) ATTR_VPRINTF(3);


PRINTF_VISIBILITY
int fctprintf(void (*out)(char c, void* extra_arg), void* extra_arg, const char* format, ...) ATTR_PRINTF(3, 4);
PRINTF_VISIBILITY
int vfctprintf(void (*out)(char c, void* extra_arg), void* extra_arg, const char* format, va_list arg) ATTR_VPRINTF(3);

#ifdef __cplusplus
} // extern "C"
#endif

#if PRINTF_ALIAS_STANDARD_FUNCTION_NAMES
# undef printf_
# undef sprintf_
# undef vsprintf_
# undef snprintf_
# undef vsnprintf_
# undef vprintf_
#endif

#endif  // PRINTF_H_