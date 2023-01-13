#include "util/metrics.h"
#include "util/tree.h"

#include <string>
#include <iostream>

using namespace std::string_literals;

int main()
{
    std::string path;

    // path = "a100-test-runner_1387429.train.1673235521507.pt.trace.json"s;
    // Tree tree;
    // tree.buildFromFile(path);
    // tree.print();

    path = "resnet18_all_metrics.train.csv"s;
    Metrics metrics;
    metrics.readFromFile(path);

    int lookup_start;
    int lookup_end;
    int iter_length = (metrics.end_time - metrics.start_time) / 10;
    printf("Each iteration is %d us long.\n", iter_length);
    printf("Please input lookup time range: ");
    std::cin >> lookup_start >> lookup_end;

    double fp32active_avg = metrics.lookup(lookup_start, lookup_end);

    printf("Average fp32active is %f", fp32active_avg);

    return 0;
}
