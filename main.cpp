#include "util/flops.h"
#include "util/tree.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

using namespace std::string_literals;

int main()
{
    std::string path, line;
    std::ifstream ifile;

    // path = "a100-test-runner_1387429.train.1673235521507.pt.trace.json"s;
    // ifile.open(path, std::ios::in);
    // std::getline(ifile, line, '\0');

    // Tree tree;
    // tree.build(line);
    // tree.print();

    path = "resnet18_all_metrics.train.csv"s;
    ifile.open(path, std::ios::in);
    std::getline(ifile, line); // Ignore table header

    std::vector<Flops> flops_list;
    while (std::getline(ifile, line))
    {
        std::istringstream istring(line);

        std::string timestamp_str, gpu_fp32active_str, duration_str;
        std::getline(istring, timestamp_str, ',');
        std::getline(istring, gpu_fp32active_str, ',');
        std::getline(istring, duration_str, ',');

        uint64_t timestamp = static_cast<int>(std::stof(timestamp_str) * 1000);
        float gpu_fp32active = std::stof(gpu_fp32active_str);
        uint64_t duration = static_cast<int>(std::stof(duration_str) * 1000);

        Flops flops(timestamp, gpu_fp32active, duration);
        flops_list.push_back(flops);
    }

    uint64_t start_time;
    for (auto i = flops_list.begin(); i < flops_list.end(); i++)
    {
        if (i->gpu_fp32active > 0)
        {
            start_time = i->timestamp - i->duration;
            break;
        }
    }

    uint64_t end_time;
    for (auto i = flops_list.end() - 1; i > flops_list.begin(); i--)
    {
        if (i->gpu_fp32active > 0)
        {
            end_time = i->timestamp;
            break;
        }
    }

    if (start_time < end_time)
    {
        printf("Trace starts at %zu and ends at %zu.\n", start_time, end_time);
    }
    else
    {
        printf("Invalid flops trace.\n");
        return 0;
    }

    // for (const Flops &flops : flops_list)
    // {
    //     printf("%6zu, %.2f, %5zu\n", flops.timestamp, flops.gpu_fp32active, flops.duration);
    // }

    uint64_t lookup_start;
    uint64_t lookup_end;
    uint64_t iter_length = (end_time - start_time) / 10;
    printf("Each iteration is %zu us long.\n", iter_length);
    printf("Please input lookup time range: ");
    std::cin >> lookup_start >> lookup_end;

    double fp32active_sum = 0;
    // Lookup time range projected to the first iteration
    uint64_t iter_start = start_time + lookup_start;
    uint64_t iter_end = start_time + lookup_end;
    for (const Flops &flops : flops_list)
    {
        // Time range of this peice of flops trace
        const uint64_t flops_start = flops.timestamp - flops.duration;
        const uint64_t flops_end = flops.timestamp;
        if (flops_end > iter_start && flops_start < iter_end)
        {
            const int time = static_cast<int>(
                std::min(iter_end, flops_end) - std::max(iter_start, flops_start));
            fp32active_sum += flops.gpu_fp32active * time;
            if (flops_end >= iter_end)
            {
                // Move on to the next iteration
                iter_start += iter_length;
                iter_end += iter_length;
            }
        }
        else
        {
            continue;
        }
    }
    double fp32active_avg = fp32active_sum / static_cast<int>(lookup_end - lookup_start) / 10;

    printf("Average fp32active is %f", fp32active_avg);

    return 0;
}
