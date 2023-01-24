import ctypes
query = ctypes.cdll.LoadLibrary("./build/libConvert.so")
query.init.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
torch_trace = (ctypes.c_char*100)(*
                                  bytes("./a100-test-runner_1563552.train.1673890927432.pt.trace.json", 'utf-8'))
gpu_trace = (ctypes.c_char*100)(*bytes("./resnet50_all_metrics.train.csv", 'utf-8'))
query.init(torch_trace, gpu_trace)
