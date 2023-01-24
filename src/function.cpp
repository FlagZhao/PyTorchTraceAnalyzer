#include "function.h"

Function::Function(const std::string &name,
                   const std::vector<Event *> &cuda_ptr_list,
                   const float &fp32active_sum,
                   const float &duration_sum)
{
    this->name = name;
    this->cuda_ptr_list = cuda_ptr_list;
    this->fp32active_sum = fp32active_sum;
    this->duration_sum = duration_sum;
}
Function::~Function()
{
}