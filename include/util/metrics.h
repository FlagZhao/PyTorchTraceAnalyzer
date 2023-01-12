#ifndef METRICS_H
#define METRICS_H

#include "flops.h"

#include <stdint.h>
#include <string>
#include <vector>

class Metrics
{
public:
    std::vector<Flops> flops_list;
    uint64_t start_time;
    uint64_t end_time;
    Metrics();
    ~Metrics();
    bool readFromFile(const std::string &path);
    double lookup(const uint64_t lookup_start, const uint64_t lookup_end);
    void print();
};

#endif // METRICS_H
