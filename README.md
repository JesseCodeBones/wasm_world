# wasm world

## Motivation
wasm world aimed to be the light weight wasm interpreter compiler.  
we focus on wasm 1.0 now.  
we focus on JIT compiler, that means the compiler will not take too much loader time.
we also focus the scalable runtime API. the API will be coded during compilation,  
that will make runtime API is much more easier than dynamic link to the interpreter.  

## How to use
### compile
`cmake -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build`
### run
`./build/wasm_interpreter  [your wasm]`

## runtime DIY
wasm_world runtime is very easy to integrate.  
compiler provide a typical runtime in `src/runtime/SampleRuntime.hpp`.
Compiler provides module pointer, so you can get all the information under the module like stack:
```C++
uint32_t stackI32Value = module->runtime.getStack()->top().value.i32;
```

you can also easily get the memory instance:

```C++
uint8_t *ptr = (uint8_t *)module->runtime.memoryBasePtr();
```
