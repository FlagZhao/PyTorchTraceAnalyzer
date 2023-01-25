import ctypes

query = ctypes.cdll.LoadLibrary("./build/Release/Convert.dll")

query.init.argtypes = [ctypes.c_char_p, ctypes.c_char_p, ctypes.c_int]
query.init(b"./a100-test-runner_1563552.train.1673890927432.pt.trace.json",
           b"./resnet50_all_metrics.train.csv", 10)

query.query_backward(b"", b"")
