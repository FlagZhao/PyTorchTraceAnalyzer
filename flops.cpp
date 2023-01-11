#include "util/flops.h"

Flops::Flops(uint64_t timestamp, float gpu_fp32active, uint64_t duration)
{
    this->timestamp = timestamp;
    this->gpu_fp32active = gpu_fp32active;
    this->duration = duration;
}

Flops::~Flops()
{
}
