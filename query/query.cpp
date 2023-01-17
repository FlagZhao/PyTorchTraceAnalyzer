#include "query.h"
#include "../metrics/flops.h"
#include "../tree/event.h"

#include <iostream>

float query(const Tree &tree, Metrics &metrics, const std::string &func_name,
            const UsageQueryType &usage_query_type,
            const TimeQueryType &time_query_type)
{
    std::vector<Event *> cuda_ptr_list;
    int found_count = 0;
    float fp32active_sum = 0;
    float duration_sum = 0;
    float scale = static_cast<float>(metrics.end_time - metrics.start_time) /
                  metrics.iter_count / tree.duration;
    for (auto i = tree.event_list.begin(); i < tree.event_list.end(); i++)
    {
        if (tree.string_table[i->name_id] == func_name)
        {
            found_count++;
            if (usage_query_type == RangeUsage)
            {
                int lookup_start = (i->timestamp - tree.start_time - i->duration) * scale;
                int lookup_end = (i->timestamp - tree.start_time) * scale;
                fp32active_sum += metrics.lookup(lookup_start, lookup_end) * i->duration;
            }
            if (time_query_type == RangeTime)
            {
                duration_sum += i->duration;
            }
            const int64_t end_time = i->timestamp + i->duration;
            for (i++; i < tree.event_list.end() && i->timestamp < end_time; i++)
            {
                if (i->cat == Event::cuda_runtime)
                {
                    cuda_ptr_list.push_back((Event *)(&*i));
                }
            }
            i--; // Go back to the last child function
        }
    }

    if (usage_query_type == KernelUsage || time_query_type == KernelTime)
    {
        if (found_count)
        {
            auto i = cuda_ptr_list.begin();
            for (const Event &kernel : tree.kernel_list)
            {
                if (i < cuda_ptr_list.end() &&
                    (*i)->correlation == kernel.correlation)
                {
                    if (usage_query_type == KernelUsage)
                    {
                        int lookup_start = (kernel.timestamp - tree.start_time - kernel.duration) * scale;
                        int lookup_end = (kernel.timestamp - tree.start_time) * scale;
                        fp32active_sum += metrics.lookup(lookup_start, lookup_end) * kernel.duration;
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
            return 0;
        }
    }
    float fp32active_avg = fp32active_sum / duration_sum;
    return fp32active_avg;
}
