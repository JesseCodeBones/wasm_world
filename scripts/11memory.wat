(module
    (memory 1)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))

    (func $_start
        (i32.store
            (i32.const 0)
            (i32.const 42)
        )
        (call $printNumberI32 
            (i32.load
                (i32.const 0)
            )
        )
    )
    (start $_start)
)