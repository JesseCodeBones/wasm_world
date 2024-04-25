(module
    (memory 1)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (func $_start
        (drop
            (i32.const 42)
        )
        (call $printNumberI32
            (select
            ;; should select 42
                (i32.const 42)
                (i32.const 24)
                (i32.const 0)
            )
        )
        (call $printNumberI32
            (select
            ;; should select 24
                (i32.const 42)
                (i32.const 24)
                (i32.const 1)
            )
        )
        (call $printNumberF32
            (select
            ;; should select 24
                (result f32)
                (f32.const 42)
                (f32.const 24)
                (i32.const 1)
            )
        )
    )
    (start $_start)
)