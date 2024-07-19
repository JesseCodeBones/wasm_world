(module
    (memory 2)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (func $_start
        (block
            (call $printNumberI32
                (memory.grow (i32.const 5))
            )
        )
        (block
            (call $printNumberI32
                (memory.size)
            )
        )
    )
    (start $_start)
)