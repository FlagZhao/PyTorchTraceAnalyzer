#include "metrics/metrics.h"
#include "query/query.h"
#include "tree/tree.h"

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

    // path = "a100-test-runner_1387429.train.1673235521507.pt.trace.json"s;
    path = "a100-test-runner_1561923.eval.1673890226890.pt.trace.json"s;
    Tree tree;
    tree.readFromFile(path);
    tree.build();
    // tree.print();

    // path = "resnet18_all_metrics.train.csv"s;
    path = "speech_transformer_all_metrics.eval.csv"s;
    Metrics metrics;
    metrics.readFromFile(path, 10);

    // std::string func_name = "nn.Module: CrossEntropyLoss_0"s;
    std::string func_name = "aten::zeros"s;

    float fp32active = query(tree, metrics, func_name);
    printf("%f\n", fp32active);

    return 0;
}
