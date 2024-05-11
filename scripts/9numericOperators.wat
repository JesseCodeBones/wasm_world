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

        (call $printNumberI32
            (i32.and
                (i32.const 2)
                (i32.const 3)
            )
        )
        (call $printNumberI64
            (i64.and
                (i64.const 2)
                (i64.const 3)
            )
        )

        (call $printNumberI32
            (i32.or
                (i32.const 2)
                (i32.const 3)
            )
        )
        (call $printNumberI64
            (i64.or
                (i64.const 2)
                (i64.const 3)
            )
        )

        (call $printNumberI32
            (i32.xor
                (i32.const 2)
                (i32.const 3)
            )
        )
        (call $printNumberI64
            (i64.xor
                (i64.const 2)
                (i64.const 3)
            )
        )
        (call $printNumberI32
            (i32.shl
                (i32.const 1)
                (i32.const 3)
            )
        )
        (call $printNumberI64
            (i64.shl
                (i64.const 1)
                (i64.const 3)
            )
        )

        (call $printNumberI32
            (i32.shr_s
                (i32.const -8)
                (i32.const 2)
            )
        )
        (call $printNumberI64
            (i64.shr_s
                (i64.const -8)
                (i64.const 2)
            )
        )

        (call $printNumberI32
            (i32.shr_u
                (i32.const -8)
                (i32.const 2)
            )
        )
        (call $printNumberI64
            (i64.shr_u
                (i64.const -8)
                (i64.const 2)
            )
        )
        (call $printNumberI32
            (i32.rotl
                (i32.const 1)
                (i32.const 2)
            )
        )
        (call $printNumberI64
            (i64.rotl
                (i64.const 1)
                (i64.const 2)
            )
        )
        (call $printNumberI32
            (i32.rotr
                (i32.const 1)
                (i32.const 2)
            )
        )
        (call $printNumberI64
            (i64.rotr
                (i64.const 1)
                (i64.const 2)
            )
        )
    )
    (start $_start)
)