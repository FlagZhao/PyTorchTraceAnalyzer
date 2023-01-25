#include "export.h"

#include <chrono>

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
    init("./a100-test-runner_1563552.train.1673890927432.pt.trace.json",
         "./resnet50_all_metrics.train.csv", 10);

    auto start_time = std::chrono::high_resolution_clock::now();

    float fp32active = query("aten::zeros|torch", "KernelUsage", "KernelTime", "FuzzyName");
    printf("Average fp32active: %f\n", fp32active);

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float, std::milli> duration = end_time - start_time;
    printf("Query took %.3fms", duration.count());

    return 0;
}
