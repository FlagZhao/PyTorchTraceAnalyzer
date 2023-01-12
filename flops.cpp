#include "util/flops.h"

Flops::Flops(const uint64_t &timestamp,
             const float &gpu_fp32active,
             const uint64_t &duration)
{
    this->timestamp = timestamp;
    this->gpu_fp32active = gpu_fp32active;
    this->duration = duration;
}

Flops::~Flops()
{
}
