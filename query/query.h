#include "../metrics/metrics.h"
#include "../tree/tree.h"

enum UsageQueryType
{
    KernelUsage,
    RangeUsage
};

enum TimeQueryType
{
    KernelTime,
    RangeTime
};

float query(const Tree &tree, Metrics &metrics, const std::string &func_name,
            const UsageQueryType &usage_query_type = KernelUsage,
            const TimeQueryType &time_query_type = KernelTime);
