#ifndef METRICS_H
#define METRICS_H

#include "flops.h"

#include <string>
#include <vector>

class Metrics
{
public:
    std::vector<Flops> flops_list;
    int start_time;
    int end_time;
    int iter_count;
    Metrics();
    ~Metrics();
    bool readFromFile(const std::string &path, const int &iter_count = 1);
    double lookup(const int &lookup_start, const int &lookup_end);
    void print();
};

#endif // METRICS_H
