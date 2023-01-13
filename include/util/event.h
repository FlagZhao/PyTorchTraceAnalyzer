#ifndef EVENT_H
#define EVENT_H

#include <stdint.h>

class Event
{
public:
    int cat;
    int name;
    int pid;
    int tid;
    int64_t timestamp;
    int duration;
    int args_id;
    int parent_id;
    int event_id;
    Event(const int &cat,
          const int &name,
          const int &pid,
          const int &tid,
          const int64_t &timestamp,
          const int &duration,
          const int &args_id);
    ~Event();
    bool operator<(const Event &event);
};

#endif // EVENT_H
