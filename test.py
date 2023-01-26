from lib import *

query = Query("./a100-test-runner_1563552.train.1673890927432.pt.trace.json",
              "./resnet50_all_metrics.train.csv", 10)
avg = query.query("aten::zeros|torch", name_query_type="FuzzyName")
print(avg)
