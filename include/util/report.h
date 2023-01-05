#include "event.h"
#include <vector>
#include <string>
#include <algorithm>
class report
{
private:
    /* data */
public:
    std::vector<event> event_list;
    std::vector<std::string> call_stacks;
    std::vector<std::string> string_table;
    report(/* args */);
    ~report();
    void reorder();
};

bool comp(const event& a, const event& b){
    return a.timestamp<b.timestamp;
}
report::report()
{
}

report::~report()
{
}
void report::reorder(){
    std::sort(this->event_list.begin(),this->event_list.end(),comp);
    return;
}