(module
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (import "env" "printNumber" (func $printNumberI64 (param i64) ))
    (import "env" "printNumber" (func $printNumberF64 (param f64) ))
    (func $_start
        (call $printNumberI32
            (i32.eqz
                (i32.const 0)
            )
        )
        (call $printNumberI32
            (i32.eqz
                (i32.const 1)
            )
        )
        (call $printNumberI32
            (i64.eqz
                (i64.const 0)
            )
        )
        (call $printNumberI32
            (i64.eqz
                (i64.const 1)
            )
        )
        (call $printNumberI32
            (i32.eq
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.eq
                (i32.const 42)
                (i32.const 41)
            )
        )
        (call $printNumberI32
            (i64.eq
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.eq
                (i64.const 42)
                (i64.const 41)
            )
        )
        (call $printNumberI32
            (f32.eq
                (f32.const 42.0)
                (f32.const 42.0)
            )
        )
        (call $printNumberI32
            (f32.eq
                (f32.const 42.0)
                (f32.const 42.1)
            )
        )
        (call $printNumberI32
            (f64.eq
                (f64.const 42.0)
                (f64.const 42.0)
            )
        )
        (call $printNumberI32
            (f64.eq
                (f64.const 42.0)
                (f64.const 42.1)
            )
        )
        (call $printNumberI32
            (i32.ne
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.ne
                (i32.const 42)
                (i32.const 41)
            )
        )
        (call $printNumberI32
            (i64.ne
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.ne
                (i64.const 42)
                (i64.const 41)
            )
        )
        (call $printNumberI32
            (f32.ne
                (f32.const 42.0)
                (f32.const 42.0)
            )
        )
        (call $printNumberI32
            (f32.ne
                (f32.const 42.0)
                (f32.const 42.1)
            )
        )
        (call $printNumberI32
            (f64.ne
                (f64.const 42.0)
                (f64.const 42.0)
            )
        )
        (call $printNumberI32
            (f64.ne
                (f64.const 42.0)
                (f64.const 42.1)
            )
        )
        (call $printNumberI32
            (i32.lt_s
                (i32.const 41)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.lt_s
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.lt_s
                (i32.const 43)
                (i32.const 42)
            )
        )

        (call $printNumberI32
            (i64.lt_s
                (i64.const 41)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.lt_s
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.lt_s
                (i64.const 43)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i32.lt_u
                (i32.const 41)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.lt_u
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.lt_u
                (i32.const 43)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i64.lt_u
                (i64.const 41)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.lt_u
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.lt_u
                (i64.const 43)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (f32.lt
                (f32.const 41)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f32.lt
                (f32.const 42)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f32.lt
                (f32.const 43)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f64.lt
                (f64.const 41)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (f64.lt
                (f64.const 42)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (f64.lt
                (f64.const 43)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (i32.gt_s
                (i32.const 41)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.gt_s
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.gt_s
                (i32.const 43)
                (i32.const 42)
            )
        )

        (call $printNumberI32
            (i64.gt_s
                (i64.const 41)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.gt_s
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.gt_s
                (i64.const 43)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i32.gt_u
                (i32.const 41)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.gt_u
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.gt_u
                (i32.const 43)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i64.gt_u
                (i64.const 41)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.gt_u
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.gt_u
                (i64.const 43)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (f32.gt
                (f32.const 41)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f32.gt
                (f32.const 42)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f32.gt
                (f32.const 43)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f64.gt
                (f64.const 41)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (f64.gt
                (f64.const 42)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (f64.gt
                (f64.const 43)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (i32.le_s
                (i32.const 41)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.le_s
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.le_s
                (i32.const 43)
                (i32.const 42)
            )
        )

        (call $printNumberI32
            (i64.le_s
                (i64.const 41)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.le_s
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.le_s
                (i64.const 43)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i32.le_u
                (i32.const 41)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.le_u
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.le_u
                (i32.const 43)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i64.le_u
                (i64.const 41)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.le_u
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.le_u
                (i64.const 43)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (f32.le
                (f32.const 41)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f32.le
                (f32.const 42)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f32.le
                (f32.const 43)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f64.le
                (f64.const 41)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (f64.le
                (f64.const 42)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (f64.le
                (f64.const 43)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (i32.ge_s
                (i32.const 41)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.ge_s
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.ge_s
                (i32.const 43)
                (i32.const 42)
            )
        )

        (call $printNumberI32
            (i64.ge_s
                (i64.const 41)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.ge_s
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.ge_s
                (i64.const 43)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i32.ge_u
                (i32.const 41)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.ge_u
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i32.ge_u
                (i32.const 43)
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (i64.ge_u
                (i64.const 41)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.ge_u
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i64.ge_u
                (i64.const 43)
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (f32.ge
                (f32.const 41)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f32.ge
                (f32.const 42)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f32.ge
                (f32.const 43)
                (f32.const 42)
            )
        )
        (call $printNumberI32
            (f64.ge
                (f64.const 41)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (f64.ge
                (f64.const 42)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (f64.ge
                (f64.const 43)
                (f64.const 42)
            )
        )
    )
    (start $_start)
)