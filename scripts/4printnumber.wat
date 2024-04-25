(module
    (memory 1)
    (data (i32.const 0) "hello world\00")
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberI64 (param i64) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (import "env" "printNumber" (func $printNumberF64 (param f64) ))
    (func $_start
        (call $printNumberI32
            (i32.const 42)
        )
        (call $printNumberI64
            (i64.const 42)
        )
        (call $printNumberF32
            (f32.const 42.1)
        )
        (call $printNumberF64
            (f64.const 42.1)
        )
    )
    (start $_start)
)