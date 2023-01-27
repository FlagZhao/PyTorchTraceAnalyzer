#include "export.h"

#include <cstring>

Query _query;

void init(const char *torch_trace, const char *gpu_trace, int gpu_trace_count)
{
    _query.init(torch_trace, gpu_trace, gpu_trace_count);
}

bool loaded()
{
    return _query.loaded;
}

float query(const char *func_name,
            const char *usage_query_type_str,
            const char *time_query_type_str,
            const char *name_query_type_str)
{
    Query::UsageQueryType usage_query_type =
        std::strcmp(usage_query_type_str, "KernelUsage") == 0  ? Query::KernelUsage
        : std::strcmp(usage_query_type_str, "RangeUsage") == 0 ? Query::RangeUsage
                                                               : Query::KernelUsage;
    Query::TimeQueryType time_query_type =
        std::strcmp(time_query_type_str, "KernelTime") == 0  ? Query::KernelTime
        : std::strcmp(time_query_type_str, "RangeTime") == 0 ? Query::RangeTime
                                                             : Query::RangeTime;
    Query::NameQueryType name_query_type =
        std::strcmp(name_query_type_str, "FuzzyName") == 0     ? Query::FuzzyName
        : std::strcmp(name_query_type_str, "PreciseName") == 0 ? Query::PreciseName
                                                               : Query::PreciseName;
    return _query.query(func_name, usage_query_type, time_query_type, name_query_type);
}

float query_forward(const char *usage_query_type_str,
                    const char *time_query_type_str)
{
    return query(": forward", usage_query_type_str, time_query_type_str, "FuzzyName");
}

float query_backward(const char *usage_query_type_str,
                     const char *time_query_type_str)
{
    return query(": backward", usage_query_type_str, time_query_type_str, "FuzzyName");
}

float query_optimizer(const char *usage_query_type_str,
                      const char *time_query_type_str)
{
    return query("torch/optim/optimizer.py", usage_query_type_str, time_query_type_str, "FuzzyName");
}

float query_module(const char *module_name,
                   const char *usage_query_type_str,
                   const char *time_query_type_str)
{
    char *func_name = (char *)malloc(sizeof(char) * 0xFF);
    std::sprintf(func_name, "nn.Module: %s_", module_name);
    return query(func_name, usage_query_type_str, time_query_type_str, "FuzzyName");
}