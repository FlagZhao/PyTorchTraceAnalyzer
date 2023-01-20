#ifndef QUERY_H
#define QUERY_H

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

enum NameQueryType
{
    FuzzyName,
    PreciseName
};

float query(const Tree &tree, Metrics &metrics, const std::string &func_name,
            const UsageQueryType &usage_query_type = KernelUsage,
            const TimeQueryType &time_query_type = RangeTime,
            const NameQueryType &name_query_type = PreciseName);
std::vector<std::string> split(std::string_view sv, char delims);
bool name_match(const std::string &str, const std::vector<std::string> &match_list, const NameQueryType &match_type);

#endif // QUERY_H
