#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>

class Event
{
public:
    enum Cat
    {
        none,
        python_function,
        cpu_op,
        cuda_runtime,
        kernel
    };
    Cat cat;
    int name_id;
    int pid;
    int tid;
    int64_t timestamp;
    int duration;
    int args_id;
    int parent_id;
    int event_id;
    Event(const Cat &cat,
          const int &name_id,
          const int &pid,
          const int &tid,
          const int64_t &timestamp,
          const int &duration,
          const int &args_id);
    ~Event();
    bool operator<(const Event &event);
};

#endif // EVENT_H
