#ifndef TREE_H
#define TREE_H

#include "event.h"
#include <vector>
#include <string>

class Tree
{
public:
    std::vector<Event> event_list;
    std::vector<Event> kernel_list;
    std::vector<std::string> string_table;
    int64_t start_time;
    int duration;
    Tree();
    ~Tree();
    void read(const std::string &data);
    void readFromFile(const std::string &path);
    void build();
    void print();
};

#endif // TREE_H
