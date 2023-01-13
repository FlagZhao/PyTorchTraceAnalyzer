#ifndef FLOPS_H
#define FLOPS_H

class Flops
{
public:
    int timestamp;
    float gpu_fp32active;
    int duration;
    Flops(const int &timestamp,
          const float &gpu_fp32active,
          const int &duration);
    ~Flops();
};

#endif // FLOPS_H
