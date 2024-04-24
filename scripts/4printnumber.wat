(module
    (memory 1)
    (data (i32.const 0) "hello world\00")
    (import "env" "printNumber" (func $printNumber (param i32) ))
    (func $_start
        (call $printNumber
            (i32.const 42)
        )
        ;; support i64.const f32.const f64.const
        (call $printNumber
            (i64.const 42)
        )
        (call $printNumber
            (f32.const 42.1)
        )
        (call $printNumber
            (f64.const 42.1)
        )
    )
    (start $_start)
)