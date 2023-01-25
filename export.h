#ifndef EXPORT_H
#define EXPORT_H

#include "include/query.h"

#ifdef __cplusplus
#define EXTERNC extern "C"
#else
#define EXTERNC
#endif

#if defined(_MSC_VER)
#define _exported __declspec(dllexport)
#else
#define _exported
#endif

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

#endif // EXPORT_H
