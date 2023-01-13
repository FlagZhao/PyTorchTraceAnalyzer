#include "util/event.h"

Event::Event(const Cat &cat,
             const int &name_id,
             const int &pid,
             const int &tid,
             const int64_t &timestamp,
             const int &duration,
             const int &args_id,
             const int &correlation)
{
    this->cat = cat;
    this->name_id = name_id;
    this->pid = pid;
    this->tid = tid;
    this->timestamp = timestamp;
    this->duration = duration;
    this->args_id = args_id;
    this->correlation = correlation;
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
