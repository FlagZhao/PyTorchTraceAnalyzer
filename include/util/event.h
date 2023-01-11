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
    uint64_t timestamp;
    uint64_t duration;
    int args_id;
    int parent_id;
    int event_id;
    Event(const int &cat,
          const int &name,
          const int &pid,
          const int &tid,
          const uint64_t &timestamp,
          const uint64_t &duration,
          const int &args_id);
    ~Event();
    bool operator<(const Event &event);
};

#endif // EVENT_H
