#include "metrics.h"

#include <fstream>
#include <sstream>
#include <iostream>

Metrics::Metrics()
{
}

Metrics::~Metrics()
{
}

bool Metrics::readFromFile(const std::string &path, const int &iter_count)
{
    this->iter_count = iter_count;

    std::ifstream ifile(path, std::ios::in);
    std::string line;

    // Ignore table header
    std::getline(ifile, line);

    while (std::getline(ifile, line))
    {
        std::istringstream istring(line);

        std::string timestamp_str, gpu_fp32active_str, duration_str;
        std::getline(istring, timestamp_str, ',');
        std::getline(istring, gpu_fp32active_str, ',');
        std::getline(istring, duration_str, ',');

        int timestamp = static_cast<int>(std::stof(timestamp_str) * 1000);
        float gpu_fp32active = std::stof(gpu_fp32active_str);
        int duration = static_cast<int>(std::stof(duration_str) * 1000);

        flops_list.emplace_back(timestamp, gpu_fp32active, duration);
    }

    for (auto i = flops_list.begin(); i < flops_list.end(); i++)
    {
        // Find first none-zero entry
        if (i->gpu_fp32active > 0)
        {
            start_time = i->timestamp - i->duration;
            break;
        }
    }

    for (auto i = flops_list.end() - 1; i > flops_list.begin(); i--)
    {
        // Find last none-zero entry
        if (i->gpu_fp32active > 0)
        {
            end_time = i->timestamp;
            break;
        }
    }

    if (start_time < end_time)
    {
        printf("Trace starts at %d and ends at %d.\n", start_time, end_time);
        return true;
    }
    else
    {
        printf("Invalid flops trace.\n");
        return false;
    }
}

double Metrics::sumup(const int &lookup_start, const int &lookup_end)
{
    double fp32active_sum = 0;
    int iter_length = (end_time - start_time) / iter_count;

    // Lookup time range projected to the first iteration
    int iter_start = start_time + lookup_start;
    int iter_end = start_time + lookup_end;
    for (auto i = flops_list.begin(); i < flops_list.end(); i++)
    {
        // Time range of this entry
        const int flops_start = i->timestamp - i->duration;
        const int flops_end = i->timestamp;
        // If this entry overlapse the lookup time range
        if (flops_end > iter_start && flops_start < iter_end)
        {
            fp32active_sum += i->gpu_fp32active *
                              (std::min(iter_end, flops_end) - std::max(iter_start, flops_start));
            // If this entry goes beyond the lookup range
            if (flops_end >= iter_end)
            {
                // Move on to the next iteration
                iter_start += iter_length;
                iter_end += iter_length;
                // Go back to the last entry inside the range
                i--;
            }
        }
        else
        {
            continue;
        }
    }
    return fp32active_sum / iter_count;
}

void Metrics::print()
{
    for (const Flops &flops : flops_list)
    {
        printf("%6d, %.2f, %5d\n", flops.timestamp, flops.gpu_fp32active, flops.duration);
    }
}
