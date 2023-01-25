#ifndef FUNCTION_H
#define FUNCTION_H

#include "event.h"

#include <string>
#include <vector>

class Function
{
public:
    std::string name;
    std::vector<Event *> cuda_ptr_list;
    float fp32active_sum;
    int duration_sum;
    Function(const std::string &name,
             const std::vector<Event *> &cuda_ptr_list,
             const float &fp32active_sum,
             const int &duration_sum);
    ~Function();
};

#endif // FUNCTION_H
