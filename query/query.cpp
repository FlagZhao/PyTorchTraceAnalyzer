#include "query.h"
#include "../metrics/flops.h"
#include "../tree/event.h"

#include <cstring>
#include <iostream>

float query(const Tree &tree, Metrics &metrics, const std::string &query_str,
            const UsageQueryType &usage_query_type,
            const TimeQueryType &time_query_type,
            const NameQueryType &name_query_type)
{
    std::vector<std::string> name_query_list;
    if (name_query_type == FuzzyName)
    {
        name_query_list = split(query_str, '|');
    }
    if (name_query_type == PreciseName)
    {
        name_query_list.push_back(query_str);
    }
    std::vector<Event *> cuda_ptr_list;
    int found_count = 0;
    float fp32active_sum = 0;
    float duration_sum = 0;
    // Scale between gpu trace time and torch trace time
    const float scale = static_cast<float>(metrics.end_time - metrics.start_time) /
                        metrics.iter_count / tree.duration;
    for (auto i = tree.event_list.begin(); i < tree.event_list.end(); i++)
    {
        if (name_match(tree.string_table[i->name_id], name_query_list, name_query_type))
        {
            printf("%s\n", tree.string_table[i->name_id].c_str());
            found_count++;
            if (usage_query_type == RangeUsage)
            {
                const int lookup_start = (i->timestamp - tree.start_time - i->duration) * scale;
                const int lookup_end = (i->timestamp - tree.start_time) * scale;
                fp32active_sum += metrics.sumup(lookup_start, lookup_end);
            }
            if (time_query_type == RangeTime)
            {
                duration_sum += i->duration;
            }
            const int64_t end_time = i->timestamp + i->duration;
            // Find cuda invokes in the following events
            for (i++; i < tree.event_list.end() && i->timestamp < end_time; i++)
            {
                if (i->cat == Event::cuda_runtime)
                {
                    cuda_ptr_list.push_back((Event *)(&*i));
                }
            }
            // Go back to the last child function
            i--;
        }
    }

    if (found_count)
    {
        if (usage_query_type == KernelUsage || time_query_type == KernelTime)
        {
            if (cuda_ptr_list.size())
            {
                auto i = cuda_ptr_list.begin();
                for (const Event &kernel : tree.kernel_list)
                {
                    // Find kernel event correlated with the cuda event
                    if (i < cuda_ptr_list.end() &&
                        (*i)->correlation == kernel.correlation)
                    {
                        if (usage_query_type == KernelUsage)
                        {
                            const int lookup_start = (kernel.timestamp - tree.start_time - kernel.duration) * scale;
                            const int lookup_end = (kernel.timestamp - tree.start_time) * scale;
                            fp32active_sum += metrics.sumup(lookup_start, lookup_end);
                        }
                        if (time_query_type == KernelTime)
                        {
                            duration_sum += kernel.duration;
                        }
                        i++;
                    }
                }
            }
            else
            {
                printf("This function does not evoke kernel\n");
                return 0;
            }
        }
    }
    else
    {
        printf("Function not found\n");
        return 0;
    }
    float fp32active_avg = fp32active_sum / duration_sum;
    return fp32active_avg;
}

std::vector<std::string> split(std::string_view sv, char delims)
{
    std::vector<std::string> output;
    size_t start = 0;
    while (start < sv.size())
    {
        const std::size_t end = sv.find_first_of(delims, start);
        if (start != end)
        {
            output.emplace_back(sv.substr(start, end - start));
        }
        if (end == std::string_view::npos)
        {
            break;
        }
        start = end + 1;
    }
    return output;
}

bool name_match(const std::string &str, const std::vector<std::string> &match_list, const NameQueryType &match_type)
{
    for (const std::string &match_str : match_list)
    {
        if (match_type == FuzzyName && std::strstr(str.c_str(), match_str.c_str()) ||
            match_type == PreciseName && str == match_str)
        {
            return true;
        }
    }
    return false;
}
