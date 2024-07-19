(module
    (memory 1)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberI64 (param i64) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (import "env" "printNumber" (func $printNumberF64 (param f64) ))
    (func $_start
        (block
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

        (block
            (i64.store
                (i32.const 0)
                (i64.const 42)
            )
            (call $printNumberI64 
                (i64.load
                    (i32.const 0)
                )
            )
        )

        (block
            (f32.store
                (i32.const 0)
                (f32.const 42.0)
            )
            (call $printNumberF32 
                (f32.load
                    (i32.const 0)
                )
            )
        )

        (block
            (f64.store
                (i32.const 0)
                (f64.const 42.0)
            )
            (call $printNumberF64 
                (f64.load
                    (i32.const 0)
                )
            )
        )

        (block
            (i32.store8
                (i32.const 0)
                (i32.const 0xff)
            )
            (call $printNumberI32 
                (i32.load8_s
                    (i32.const 0)
                )
            )
        )

        (block
            (i32.store8
                (i32.const 0)
                (i32.const 0xff)
            )
            (call $printNumberI32 
                (i32.load8_u
                    (i32.const 0)
                )
            )
        )

        (block
            (i32.store16
                (i32.const 0)
                (i32.const 0xffff)
            )
            (call $printNumberI32 
                (i32.load16_s
                    (i32.const 0)
                )
            )
        )
        
        (block
            (i32.store16
                (i32.const 0)
                (i32.const 0xffff)
            )
            (call $printNumberI32 
                (i32.load16_u
                    (i32.const 0)
                )
            )
        )

        (block
            (i64.store8
                (i32.const 0)
                (i64.const 0xff)
            )
            (call $printNumberI64 
                (i64.load8_s
                    (i32.const 0)
                )
            )
        )

        (block
            (i64.store8
                (i32.const 0)
                (i64.const 0xff)
            )
            (call $printNumberI64 
                (i64.load8_u
                    (i32.const 0)
                )
            )
        )

        (block
            (i64.store16
                (i32.const 0)
                (i64.const 0xffff)
            )
            (call $printNumberI64 
                (i64.load16_s
                    (i32.const 0)
                )
            )
        )
        
        (block
            (i64.store16
                (i32.const 0)
                (i64.const 0xffff)
            )
            (call $printNumberI64 
                (i64.load16_u
                    (i32.const 0)
                )
            )
        )

        (block
            (i64.store32
                (i32.const 0)
                (i64.const 0xffffffff)
            )
            (call $printNumberI64 
                (i64.load32_s
                    (i32.const 0)
                )
            )
        )
        
        (block
            (i64.store32
                (i32.const 0)
                (i64.const 0xffffffff)
            )
            (call $printNumberI64 
                (i64.load32_u
                    (i32.const 0)
                )
            )
        )

        (block
            (i64.store32
                (i32.const 0)
                (i64.const 0xffffffffffffffff)
            )
            (call $printNumberI64 
                (i64.load32_u
                    (i32.const 0)
                )
            )
        )

        (block
            (call $printNumberI32
                (memory.size)
            )
        )

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