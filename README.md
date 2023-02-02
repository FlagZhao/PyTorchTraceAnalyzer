# CallingTreeBuilder
## API reference
### `Query` class
```python
convert.Query(
    torch_trace="",
    gpu_trace="",
    gpu_trace_count=1
)
```
The main component of this library.  
You can initialize an empty instance by not providing any argument, but it has to be initialized later by calling `Query.init()`.
#### Parameters
- `torch_trace`: str, path to the PyTorch trace file.
- `gpu_trace`: str, path to the GPU trace file.
- `gpu_trace_count`: int, number of iterations included in the GPU trace file.
#### Return value
An empty instance of the `Query` class.

### `init` method
```python
convert.Query.init(
    torch_trace,
    gpu_trace,
    gpu_trace_count=1
)
```
Loads and analyzes the traces.
#### Parameters
- `torch_trace`: str, path to the PyTorch trace file.
- `gpu_trace`: str, path to the GPU trace file.
- `gpu_trace_count`: int, number of iterations included in the GPU trace file.
#### Return value
An loaded instance of the `Query` class.

### `loaded` variable
```python
convert.Query.loaded
```
Returns if the `Query` class is loaded or not.

### `query` method
```python
convert.Query.query(
    func_name,
    usage_query_type="KernelUsage",
    time_query_type="RangeTime",
    name_query_type="PreciseName"
)
```
Queries the specifies function, with selected usage calculation method and name matching method.
#### Parameters
- `func_name`: str, the function name to query.
- `usage_query_type`: str, method used to calculate the GPU usage sum. Can be `"KernelUsage"` or `"RangeUsage"`.
- `time_query_type`: str, method used to calculate the time sum. Can be `"KernelTime"` or `"RangeTime"`.
- `name_query_type`: str, name matching mathod. Can be `"FuzzyName"` or `"PreciseName"`.
#### Return value
The average GPU usage of matching functions, in float.

### `query_forward` method
```python
convert.Query.query_forward(
    usage_query_type="KernelUsage",
    time_query_type="RangeTime"
)
```
Queries the forward layer, with selected usage calculation method.
#### Parameters
- `usage_query_type`: str, method used to calculate the GPU usage sum. Can be `"KernelUsage"` or `"RangeUsage"`.
- `time_query_type`: str, method used to calculate the time sum. Can be `"KernelTime"` or `"RangeTime"`.
#### Return value
The average GPU usage of forward layer, in float.

### `query_backward` method
```python
convert.Query.query_backward(
    usage_query_type="KernelUsage",
    time_query_type="RangeTime"
)
```
Queries the backward layer, with selected usage calculation method.
#### Parameters
- `usage_query_type`: str, method used to calculate the GPU usage sum. Can be `"KernelUsage"` or `"RangeUsage"`.
- `time_query_type`: str, method used to calculate the time sum. Can be `"KernelTime"` or `"RangeTime"`.
#### Return value
The average GPU usage of backward layer, in float.

### `query_optimizer` method
```python
convert.Query.query_optimizer(
    usage_query_type="KernelUsage",
    time_query_type="RangeTime"
)
```
Queries the optimizer, with selected usage calculation method.
#### Parameters
- `usage_query_type`: str, method used to calculate the GPU usage sum. Can be `"KernelUsage"` or `"RangeUsage"`.
- `time_query_type`: str, method used to calculate the time sum. Can be `"KernelTime"` or `"RangeTime"`.
#### Return value
The average GPU usage of optimizer, in float.

### `query_module` method
```python
convert.Query.query_modules(
    module_name,
    usage_query_type="KernelUsage",
    time_query_type="RangeTime"
)
```
Queries the specified module, with selected usage calculation method.
#### Parameters
- `modules_name`: str, the module name to query.
- `usage_query_type`: str, method used to calculate the GPU usage sum. Can be `"KernelUsage"` or `"RangeUsage"`.
- `time_query_type`: str, method used to calculate the time sum. Can be `"KernelTime"` or `"RangeTime"`.
#### Return value
The average GPU usage of the specified module, in float.

## Build
1. Compile `CMakeLists.txt`  
```bash
mkdir build
cd build
cmake ..
make
cd ..
```
2. Build Python package
```bash
python3 -m build --wheel
```