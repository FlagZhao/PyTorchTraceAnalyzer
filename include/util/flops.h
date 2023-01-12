#ifndef FLOPS_H
#define FLOPS_H

#include <stdint.h>

class Flops
{
public:
    uint64_t timestamp;
    float gpu_fp32active;
    uint64_t duration;
    Flops(const uint64_t &timestamp,
          const float &gpu_fp32active,
          const uint64_t &duration);
    ~Flops();
};

#endif // FLOPS_H
