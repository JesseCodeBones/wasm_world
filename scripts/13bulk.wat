(module
    (memory 1)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberI64 (param i64) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (import "env" "printNumber" (func $printNumberF64 (param f64) ))

    (func $_start
        (memory.fill 
            (i32.const 200) ;; pointer
            (i32.const 255) ;; value
            (i32.const 4) ;; length
        )
        (call $printNumberI32 (i32.load (i32.const 200)))
        (memory.copy 
            (i32.const 500) ;; destination pointer
            (i32.const 200) ;; source pointer
            (i32.const 4) ;; length
        )
        (call $printNumberI32 (i32.load (i32.const 500)))
    )
    (start $_start)
)