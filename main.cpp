#include "./include/util/tree.h"

#include <fstream>
#include <sstream>
#include <vector>
#include <iostream>

void loadFromFile(const std::string &path, std::string &data)
{
    std::ifstream ifile;
    ifile.open(path, std::ios::in);
    std::ostringstream ostring;
    ostring << ifile.rdbuf();
    data = ostring.str();
}

int main()
{
    Tree tree;
    std::string path = "a100-test-runner_549810.1668545729102.cu116.pt.trace.json";
    std::string data;
    loadFromFile(path, data);

    tree.build(data);
    tree.print();
    return 0;
}