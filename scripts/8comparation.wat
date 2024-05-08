(module
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (import "env" "printNumber" (func $printNumberI64 (param i64) ))
    (func $_start
        (call $printNumberI32
            (i32.eqz
                (i32.const 1)
            )
        )
        (call $printNumberI32
            (i32.eqz
                (i32.const 0)
            )
        )
        (call $printNumberI32
            (i64.eqz
                (i64.const 1)
            )
        )
        (call $printNumberI32
            (i64.eqz
                (i64.const 0)
            )
        )
    )
    (start $_start)
)