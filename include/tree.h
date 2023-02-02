#ifndef TREE_H
#define TREE_H

#include "event.h"
#include <vector>
#include <string>

class Tree
{
public:
    std::vector<Event> event_list;
    std::vector<Event> gpu_list;
    std::vector<std::string> string_table;
    int64_t start_time;
    int duration;
    Tree();
    ~Tree();
    bool read(const std::string &data);
    bool readFromFile(const std::string &path);
    bool build();
    void print();
};

#endif // TREE_H
