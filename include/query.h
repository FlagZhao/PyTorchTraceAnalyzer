#ifndef QUERY_H
#define QUERY_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#endif

#include "metrics.h"
#include "tree.h"


#ifndef _MICROS_H_
#define _MICROS_H_
#if defined(_MSC_VER)

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
    _exported Tree tree;
    _exported Metrics metrics;

    typedef enum
    {
        KernelUsage,
        RangeUsage
    } UsageQueryType;

    typedef enum
    {
        KernelTime,
        RangeTime
    } TimeQueryType;

    typedef enum
    {
        FuzzyName,
        PreciseName
    } NameQueryType;

    _exported void init(const char *torch_trace, const char *gpu_trace);

    _exported float query(const std::string &func_name,
                                      const UsageQueryType &usage_query_type = KernelUsage,
                                      const TimeQueryType &time_query_type = RangeTime,
                                      const NameQueryType &name_query_type = PreciseName);

    std::vector<std::string> split(std::string_view sv, char delims);

    bool name_match(const std::string &str, const std::vector<std::string> &match_list, const NameQueryType &match_type);

    _exported float query_forward(const UsageQueryType &usage_query_type = KernelUsage,
                                              const TimeQueryType &time_query_type = RangeTime);

    _exported float query_backward(const UsageQueryType &usage_query_type = KernelUsage,
                                               const TimeQueryType &time_query_type = RangeTime);

    _exported float query_optimizer(const UsageQueryType &usage_query_type = KernelUsage,
                                                const TimeQueryType &time_query_type = RangeTime);

    _exported float query_module(const UsageQueryType &usage_query_type = KernelUsage,
                                             const TimeQueryType &time_query_type = RangeTime,
                                             const NameQueryType &name_query_type = PreciseName);
}

#endif // QUERY_H
