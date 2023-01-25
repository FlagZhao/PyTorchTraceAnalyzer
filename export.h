#ifndef EXPORT_H
#define EXPORT_H

#include "include/query.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#ifndef _MICROS_H_
#define _MICROS_H_
#if defined(_MSC_VER)

#define DB_CREATE_DLL
#if defined(DB_CREATE_DLL)
#define _exported __declspec(dllexport) // creator of dll
#elif defined(DB_USE_DLL)
#define _exported __declspec(dllimport) // user of dll
#else
#define _exported // static lib creator or user
#endif

#else /* _MSC_VER */

#define _exported

#endif /* _MSC_VER */

#endif /* _MICROS_H_ */

EXTERNC
{
    _exported void init(const char *torch_trace, const char *gpu_trace, int gpu_trace_count);

    _exported float query(const char *func_name,
                          const char *usage_query_type_str,
                          const char *time_query_type_str,
                          const char *name_query_type_str);

    _exported float query_forward(const char *usage_query_type_str,
                                  const char *time_query_type_str);

    _exported float query_backward(const char *usage_query_type_str,
                                   const char *time_query_type_str);

    _exported float query_optimizer(const char *usage_query_type_str,
                                    const char *time_query_type_str);

    _exported float query_module(const char *module_name,
                                 const char *usage_query_type_str,
                                 const char *time_query_type_str);
}

#endif /* EXPORT_H */
