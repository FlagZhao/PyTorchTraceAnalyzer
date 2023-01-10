#include "event.h"
#include <vector>
#include <string>
#include <algorithm>
class Report
{
private:
    /* data */
public:
    std::vector<Event> event_list;
    std::vector<std::string> call_stacks;
    std::vector<std::string> string_table;
    Report(/* args */);
    ~Report();
    void reorder();
};

Report::Report()
{
}

Report::~Report()
{
}

bool comp(const Event &a, const Event &b)
{
    return a.timestamp < b.timestamp;
}

void Report::reorder()
{
    std::sort(this->event_list.begin(), this->event_list.end(), comp);
    return;
}