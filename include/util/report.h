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

void Report::reorder()
{
    std::sort(this->event_list.begin(), this->event_list.end());
    return;
}