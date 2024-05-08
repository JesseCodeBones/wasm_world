(module
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (import "env" "printNumber" (func $printNumberI64 (param i64) ))
    (import "env" "printNumber" (func $printNumberF64 (param f64) ))
    (func $_start
        (call $printNumberI32
            (i32.clz
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.clz
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i32.ctz
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.ctz
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i32.popcnt
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.popcnt
                (i64.const 42)
            )
        )

        (call $printNumberI32
            (i32.add
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.add
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberF32
            (f32.add
                (f32.const 42)
                (f32.const 42)
            )
        )
        (call $printNumberF64
            (f64.add
                (f64.const 42)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (i32.sub
                (i32.const 42)
                (i32.const 43)
            )
        )
        (call $printNumberI64
            (i64.sub
                (i64.const 42)
                (i64.const 43)
            )
        )
        (call $printNumberF32
            (f32.sub
                (f32.const 42)
                (f32.const 43)
            )
        )
        (call $printNumberF64
            (f64.sub
                (f64.const 42)
                (f64.const 43)
            )
        )

        (call $printNumberI32
            (i32.mul
                (i32.const 42)
                (i32.const 43)
            )
        )
        (call $printNumberI64
            (i64.mul
                (i64.const 42)
                (i64.const 43)
            )
        )
        (call $printNumberF32
            (f32.mul
                (f32.const 42)
                (f32.const 43)
            )
        )
        (call $printNumberF64
            (f64.mul
                (f64.const 42)
                (f64.const 43)
            )
        )

        (call $printNumberI32
            (i32.div_s
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.div_s
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberF32
            (f32.div
                (f32.const 42)
                (f32.const 42)
            )
        )
        (call $printNumberF64
            (f64.div
                (f64.const 42)
                (f64.const 42)
            )
        )

        (call $printNumberI32
            (i32.rem_s
                (i32.const 45)
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.rem_s
                (i64.const 45)
                (i64.const 42)
            )
        )

        (call $printNumberI32
            (i32.rem_s
                (i32.const -45)
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.rem_s
                (i64.const -45)
                (i64.const 42)
            )
        )
    )
    (start $_start)
)