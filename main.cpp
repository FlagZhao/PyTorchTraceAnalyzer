#include "util/metrics.h"
#include "util/tree.h"

#include <string>
#include <iostream>

using namespace std::string_literals;

/********************************************

                   _ooOoo_
                  o8888888o
                  88" . "88
                  (| -_- |)
                  O\  =  /O
               ____/`---'\____
             .'  \\|     |//  `.
            /  \\|||  :  |||//  \
           /  _||||| -:- |||||-  \
           |   | \\\  -  /// |   |
           | \_|  ''\---/''  |   |
           \  .-\__  `-`  ___/-. /
         ___`. .'  /--.--\  `. . __
      ."" '<  `.___\_<|>_/___.'  >'"".
     | | :  `- \`.;`\ _ /`;.`/ - ` : | |
     \  \ `-.   \_ __\ /__ _/   .-` /  /
======`-.____`-.___\_____/___.-`____.-'======
                   `=---='
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
            佛祖保佑       永无BUG

********************************************/

int main()
{
    std::string path;

    path = "a100-test-runner_1387429.train.1673235521507.pt.trace.json"s;
    Tree tree;
    tree.readFromFile(path);
    tree.build();
    // tree.print();

    path = "resnet18_all_metrics.train.csv"s;
    Metrics metrics;
    metrics.readFromFile(path, 10);

    std::string func_name;
    printf("Enter function name: ");
    std::getline(std::cin, func_name);

    std::vector<Event *> cuda_ptr_list;
    int found_count = 0;
    for (auto i = tree.event_list.begin(); i < tree.event_list.end(); i++)
    {
        if (tree.string_table[i->name_id] == func_name)
        {
            found_count++;
            const int64_t end_time = i->timestamp + i->duration;
            for (i++; i < tree.event_list.end() && i->timestamp < end_time; i++)
            {
                if (i->cat == Event::cuda_runtime)
                {
                    cuda_ptr_list.push_back(&*i);
                }
            }
            i--; // Go back to the last child function
        }
    }

    if (found_count)
    {
        printf("Function found\n");
        if (cuda_ptr_list.size())
        {
            auto i = cuda_ptr_list.begin();
            for (const Event &kernel : tree.kernel_list)
            {
                if (i < cuda_ptr_list.end() &&
                    (*i)->correlation == kernel.correlation)
                {
                    printf("%s: %d\n",
                           tree.string_table[(*i)->name_id].c_str(),
                           (*i)->correlation);
                    i++;
                }
            }
        }
        else
        {
            printf("This function does not invoke kernel\n");
        }
    }
    else
    {
        printf("Function not found");
    }

    return 0;
}
