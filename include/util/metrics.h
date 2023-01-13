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
    Metrics();
    ~Metrics();
    bool readFromFile(const std::string &path);
    double lookup(const int &lookup_start, const int &lookup_end);
    void print();
};

#endif // METRICS_H
