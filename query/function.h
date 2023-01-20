#ifndef FUNCTION_H
#define FUNCTION_H

#include "../tree/event.h"

#include <string>
#include <vector>

class Function
{
public:
    std::string name;
    std::vector<Event *> cuda_ptr_list;
    float fp32active_sum;
    float duration_sum;
    Function(const std::string &name,
             const std::vector<Event *> &cuda_ptr_list,
             const float &fp32active_sum,
             const float &duration_sum);
    ~Function();
};

#endif // FUNCTION_H