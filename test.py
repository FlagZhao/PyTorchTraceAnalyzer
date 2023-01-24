import ctypes
query = ctypes.cdll.LoadLibrary("./build/Release/Convert.dll")
query.init.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
torch_trace = (ctypes.c_char*100)(*bytes("./build/a100-test-runner_1387429.train.1673235521507.pt.trace.json", 'utf-8'))
gpu_trace = (ctypes.c_char*100)(*bytes("./build/resnet18_all_metrics.train.csv", 'utf-8'))
query.init(torch_trace, gpu_trace)
