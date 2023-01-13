#include "util/flops.h"

Flops::Flops(const int &timestamp,
             const float &gpu_fp32active,
             const int &duration)
{
    this->timestamp = timestamp;
    this->gpu_fp32active = gpu_fp32active;
    this->duration = duration;
}

Flops::~Flops()
{
}
