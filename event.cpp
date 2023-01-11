#include "util/event.h"

Event::Event(int cat, int name, int pid, int tid, unsigned long long timestamp, unsigned long long duration, int args_id)
{
    this->cat = cat;
    this->name = name;
    this->pid = pid;
    this->tid = tid;
    this->timestamp = timestamp;
    this->duration = duration;
    this->args_id = args_id;
    this->parent_id = -1;
    this->event_id = 0;
}

Event::~Event()
{
}

bool Event::operator<(const Event &event)
{
    if (this->timestamp == event.timestamp)
    {
        // long duration first
        return this->duration > event.duration;
    }
    else
    {
        // early start first
        return this->timestamp < event.timestamp;
    }
}
