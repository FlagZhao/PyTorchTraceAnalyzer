#include "util/metrics.h"
#include "util/tree.h"

#include <string>
#include <iostream>

using namespace std::string_literals;

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
    metrics.readFromFile(path);

    std::string func_name;
    printf("Enter function name: ");
    std::getline(std::cin, func_name);

    std::vector<int> cuda_id_list;
    int found_times = 0;
    for (int i = 0; i < tree.event_list.size(); i++)
    {
        Event &event = tree.event_list[i];
        if (tree.string_table[event.name_id] == func_name)
        {
            found_times++;
            const int64_t end_time = event.timestamp + event.duration - tree.start_time;
            for (i++;
                 tree.event_list[i].timestamp - tree.start_time < end_time &&
                 i < tree.event_list.size();
                 i++)
            {
                event = tree.event_list[i];
                if (event.cat == Event::cuda_runtime)
                {
                    cuda_id_list.push_back(i);
                }
            }
            i--; // Go back to the last child function
        }
    }

    if (found_times)
    {
        printf("Function found\n");
        if (cuda_id_list.size())
        {
            int i = 0;
            for (const Event &kernel : tree.kernel_list)
            {
                const Event &cuda = tree.event_list[cuda_id_list[i]];
                if (cuda.correlation == kernel.correlation)
                {
                    printf("%s: %d\n",
                           tree.string_table[cuda.name_id].c_str(),
                           cuda.correlation);
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
