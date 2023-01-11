#ifndef TREE_H
#define TREE_H

#include "event.h"
#include <vector>
#include <string>
#include <algorithm>

class Tree
{
public:
    std::vector<Event> event_list;
    std::vector<std::string> string_table;
    unsigned long long start_time;
    Tree();
    ~Tree();
    void build(const std::string &data);
    void print();
};

#endif // TREE_H
