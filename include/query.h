#ifndef QUERY_H
#define QUERY_H

#include "metrics.h"
#include "tree.h"

class Query
{
public:
    Tree tree;
    Metrics metrics;
    bool loaded = false;

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

    Query();
    Query(const char *torch_trace, const char *gpu_trace, const int &gpu_trace_count = 1);
    ~Query();

    void init(const char *torch_trace, const char *gpu_trace, const int &gpu_trace_count = 1);

    float query(const std::string &func_name,
                const UsageQueryType &usage_query_type = KernelUsage,
                const TimeQueryType &time_query_type = RangeTime,
                const NameQueryType &name_query_type = PreciseName);

private:
    std::vector<std::string> split(std::string_view sv, char delims);

    bool name_match(const std::string &str,
                    const std::vector<std::string> &match_list,
                    const NameQueryType &match_type);
};

#endif // QUERY_H
