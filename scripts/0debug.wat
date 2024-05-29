(module
    (import "env" "printNumber" (func $printNumberF64 (param f64) ))
    (func $_start
        (call $printNumberF64
            (f64.reinterpret_i64
                (i64.const 0x3FF0000000000000)
            )
        )
    )
    (start $_start)
)