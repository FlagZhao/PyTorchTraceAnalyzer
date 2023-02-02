#include "function.h"
#include "query.h"
#include "flops.h"
#include "event.h"

#include <cstring>
#include <iostream>

Query::Query()
{
}

Query::Query(const char *torch_trace, const char *gpu_trace, const int &gpu_trace_count)
{
    init(torch_trace, gpu_trace, gpu_trace_count);
}

Query::~Query()
{
}

void Query::init(const char *torch_trace, const char *gpu_trace, const int &gpu_trace_count)
{
    if (tree.readFromFile(torch_trace) &&
        tree.build() &&
        metrics.readFromFile(gpu_trace, gpu_trace_count))
    {
        loaded = true;
    }
}

float Query::query(const std::string &query_str,
                   const UsageQueryType &usage_query_type,
                   const TimeQueryType &time_query_type,
                   const NameQueryType &name_query_type)
{
    if (!loaded)
    {
        return -1;
    }

    std::string name_query_array[0xF];
    int name_query_array_size = split_by_char(name_query_array, query_str, '|');

    std::vector<Function> function_list;
    // Scale between gpu trace time and torch trace time
    const float scale = static_cast<float>(metrics.end_time - metrics.start_time) /
                        metrics.iter_count / tree.duration;
    for (auto i = tree.event_list.begin(); i < tree.event_list.end(); i++)
    {
        if (name_match(tree.string_table[i->name_id], name_query_array,
                       name_query_array_size, name_query_type))
        {
            std::string name = tree.string_table[i->name_id];
            float fp32active_sum = 0;
            int duration_sum = 0;
            std::vector<Event *> cuda_ptr_list;
            if (usage_query_type == RangeUsage)
            {
                const float end_time = static_cast<float>(i->timestamp - tree.start_time);
                const float lookup_start = (end_time - i->duration) * scale;
                const float lookup_end = end_time * scale;
                fp32active_sum += metrics.sumup(static_cast<int>(lookup_start),
                                                static_cast<int>(lookup_end));
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
            function_list.emplace_back(name, cuda_ptr_list, fp32active_sum, duration_sum);
        }
    }

    if (function_list.size())
    {
        if (usage_query_type == KernelUsage || time_query_type == KernelTime)
        {
            for (Function &function : function_list)
            {
                auto i = function.cuda_ptr_list.begin();
                auto j = tree.gpu_list.begin();
                while (i < function.cuda_ptr_list.end() && j < tree.gpu_list.end())
                {
                    if ((*i)->correlation > j->correlation)
                    {
                        j++;
                    }
                    else if ((*i)->correlation < j->correlation)
                    {
                        // printf("Cuda %d not found\n", (*i)->correlation);
                        i++;
                    }
                    else if ((*i)->correlation == j->correlation)
                    {
                        if (usage_query_type == KernelUsage)
                        {
                            const float end_time = static_cast<float>(j->timestamp - tree.start_time);
                            const float lookup_start = (end_time - j->duration) * scale;
                            const float lookup_end = end_time * scale;
                            function.fp32active_sum += metrics.sumup(static_cast<int>(lookup_start),
                                                                     static_cast<int>(lookup_end));
                        }
                        if (time_query_type == KernelTime)
                        {
                            function.duration_sum += j->duration;
                        }
                        i++;
                        j++;
                    }
                }
            }
        }
    }
    else
    {
        printf("Function not found\n");
        return 0;
    }
    float fp32active_sum = 0;
    int duration_sum = 0;
    for (const Function &i : function_list)
    {
        i.fp32active_sum
            ? printf("\"%s\": %f\n", i.name.c_str(), i.fp32active_sum / i.duration_sum)
            : printf("\"%s\": No kernel invokes\n", i.name.c_str());
        fp32active_sum += i.fp32active_sum;
        duration_sum += i.duration_sum;
    }
    float fp32active_avg = fp32active_sum / duration_sum;
    return fp32active_avg;
}

int Query::split_by_char(std::string *buffer, std::string_view sv, char delims)
{
    size_t start = 0;
    int i = 0;
    while (start < sv.size())
    {
        const std::size_t end = sv.find_first_of(delims, start);
        if (start != end)
        {
            buffer[i] = sv.substr(start, end - start);
            i++;
        }
        if (end == std::string_view::npos)
        {
            break;
        }
        start = end + 1;
    }
    return i;
}

bool Query::name_match(const std::string &str, const std::string *match_array,
                       const int &match_array_size, const NameQueryType &match_type)
{
    for (int i = 0; i < match_array_size; i++)
    {
        if (match_type == FuzzyName && std::strstr(str.c_str(), match_array[i].c_str()) ||
            match_type == PreciseName && str == match_array[i])
        {
            return true;
        }
    }
    return false;
}
