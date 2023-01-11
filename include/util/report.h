#ifndef REPORT_H
#define REPORT_H

#include "event.h"
#include <vector>
#include <string>
#include <algorithm>

class Report
{
public:
    std::vector<Event> event_list;
    std::vector<std::string> call_stacks;
    std::vector<std::string> string_table;
    Report();
    ~Report();
    void reorder();
};

Report::Report()
{
}

Report::~Report()
{
}

void Report::reorder()
{
    std::sort(this->event_list.begin(), this->event_list.end());
    return;
}

#endif // REPORT_H
