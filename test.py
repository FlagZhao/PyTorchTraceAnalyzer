import ctypes
query = ctypes.cdll.LoadLibrary("./build/libConvert.so")
query.init.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
query.init(b"./a100-test-runner_1563552.train.1673890927432.pt.trace.json",
           b"./resnet50_all_metrics.train.csv")

query.query_backward()
