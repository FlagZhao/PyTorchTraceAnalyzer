import ctypes
import sys


class Query:
    def __init__(self, torch_trace: str = "",
                 gpu_trace: str = "",
                 gpu_trace_count: int = 1) -> None:

        if sys.platform == "win32":
            lib_path = "./lib/Convert.dll"
        else:
            lib_path = "./lib/libConvert.so"

        self.cdll = ctypes.CDLL(lib_path)

        if len(torch_trace) and len(gpu_trace):
            self.cdll.init.argtypes = [ctypes.c_char_p,
                                       ctypes.c_char_p,
                                       ctypes.c_int]
            self.cdll.init(torch_trace.encode("utf-8"),
                           gpu_trace.encode("utf-8"),
                           gpu_trace_count)

    def init(self, torch_trace: str,
             gpu_trace: str,
             gpu_trace_count: int = 1) -> None:

        self.cdll.init.argtypes = [ctypes.c_char_p,
                                   ctypes.c_char_p,
                                   ctypes.c_int]
        self.cdll.init(torch_trace.encode("utf-8"),
                       gpu_trace.encode("utf-8"),
                       gpu_trace_count)

    def query(self, func_name: str,
              usage_query_type: str = "KernelUsage",
              time_query_type: str = "RangeTime",
              name_query_type: str = "PreciseName") -> float:

        self.cdll.query.argtypes = [ctypes.c_char_p,
                                    ctypes.c_char_p,
                                    ctypes.c_char_p,
                                    ctypes.c_char_p]
        self.cdll.query.restype = ctypes.c_float

        return self.cdll.query(func_name.encode("utf-8"),
                               usage_query_type.encode("utf-8"),
                               time_query_type.encode("utf-8"),
                               name_query_type.encode("utf-8"))

    def query_forward(self, usage_query_type: str = "KernelUsage",
                      time_query_type: str = "RangeTime") -> float:

        self.cdll.query_forward.argtypes = [ctypes.c_char_p,
                                            ctypes.c_char_p]
        self.cdll.query_forward.restype = ctypes.c_float

        return self.cdll.query_forward(usage_query_type.encode("utf-8"),
                                       time_query_type.encode("utf-8"))

    def query_backward(self, usage_query_type: str = "KernelUsage",
                       time_query_type: str = "RangeTime") -> float:

        self.cdll.query_backward.argtypes = [ctypes.c_char_p,
                                             ctypes.c_char_p]
        self.cdll.query_backward.restype = ctypes.c_float

        return self.cdll.query_backward(usage_query_type.encode("utf-8"),
                                        time_query_type.encode("utf-8"))

    def query_optimizer(self, usage_query_type: str = "KernelUsage",
                        time_query_type: str = "RangeTime") -> float:

        self.cdll.query_optimizer.argtypes = [ctypes.c_char_p,
                                              ctypes.c_char_p]
        self.cdll.query_optimizer.restype = ctypes.c_float

        return self.cdll.query_optimizer(usage_query_type.encode("utf-8"),
                                         time_query_type.encode("utf-8"))

    def query_module(self, module_name: str,
                     usage_query_type: str = "KernelUsage",
                     time_query_type: str = "RangeTime") -> float:

        self.cdll.query.argtypes = [ctypes.c_char_p,
                                    ctypes.c_char_p,
                                    ctypes.c_char_p]
        self.cdll.query.restype = ctypes.c_float

        return self.cdll.query_module(module_name.encode("utf-8"),
                                      usage_query_type.encode("utf-8"),
                                      time_query_type.encode("utf-8"))
