#include "util/flops.h"
#include "util/tree.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

void loadFromFile(const std::string &path, std::string &data)
{
    std::ifstream ifile;
    ifile.open(path, std::ios::in);
    std::ostringstream ostring;
    ostring << ifile.rdbuf();
    data = ostring.str();
}

int main()
{
    Tree tree;
    std::string json_path = "a100-test-runner_1387429.train.1673235521507.pt.trace.json";
    std::string data;
    loadFromFile(json_path, data);

    // tree.build(data);
    // tree.print();

    std::string csv_path = "resnet18_all_metrics.train.csv";
    std::ifstream ifile;
    ifile.open(csv_path, std::ios::in);
    std::string line;
    std::getline(ifile, line);

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

    for (Flops flops : flops_list)
    {
        printf("%6zu, %.2f, %5zu\n", flops.timestamp, flops.gpu_fp32active, flops.duration);
    }

    return 0;
}
