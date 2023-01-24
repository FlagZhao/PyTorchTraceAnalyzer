#ifndef QUERY_H
#define QUERY_H

#ifdef __cplusplus
#define EXTERNC extern "C"
#endif

#include "../metrics/metrics.h"
#include "../tree/tree.h"

EXTERNC
{
    __declspec(dllexport) Tree tree;
    __declspec(dllexport) Metrics metrics;

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

    __declspec(dllexport) void init(const char *torch_trace, const char *gpu_trace);

    __declspec(dllexport) float query(const std::string &func_name,
                                      const UsageQueryType &usage_query_type = KernelUsage,
                                      const TimeQueryType &time_query_type = RangeTime,
                                      const NameQueryType &name_query_type = PreciseName);

    std::vector<std::string> split(std::string_view sv, char delims);

    bool name_match(const std::string &str, const std::vector<std::string> &match_list, const NameQueryType &match_type);

    __declspec(dllexport) float query_forward(const UsageQueryType &usage_query_type = KernelUsage,
                                              const TimeQueryType &time_query_type = RangeTime,
                                              const NameQueryType &name_query_type = PreciseName);

    __declspec(dllexport) float query_backward(const UsageQueryType &usage_query_type = KernelUsage,
                                               const TimeQueryType &time_query_type = RangeTime,
                                               const NameQueryType &name_query_type = PreciseName);

    __declspec(dllexport) float query_optimizer(const UsageQueryType &usage_query_type = KernelUsage,
                                                const TimeQueryType &time_query_type = RangeTime,
                                                const NameQueryType &name_query_type = PreciseName);

    __declspec(dllexport) float query_module(const UsageQueryType &usage_query_type = KernelUsage,
                                             const TimeQueryType &time_query_type = RangeTime,
                                             const NameQueryType &name_query_type = PreciseName);
}

#endif // QUERY_H
