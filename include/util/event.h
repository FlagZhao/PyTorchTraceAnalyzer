#ifndef EVENT_H
#define EVENT_H

class Event
{
public:
    int cat;
    int name;
    int pid;
    int tid;
    unsigned long long timestamp;
    unsigned long long duration;
    int args_id;
    int parent_id;
    int event_id;
    Event(int cat, int name, int pid, int tid, unsigned long long timestamp, unsigned long long duration, int args_id);
    ~Event();
    bool operator<(const Event &event);
};

#endif // EVENT_H
