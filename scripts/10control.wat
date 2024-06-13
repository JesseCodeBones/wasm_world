(module
    (memory 1)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))

    (func $returnI32 (result i32)
        (return 
            (i32.const 42)
        )
    )

    (func $returnPI32 (param $a i32) (result i32)
        (return 
            (local.get $a)
        )
    ) 

    (func $_start
        (local $i i32)
        (call $printNumberI32
            (call $returnI32)
        )

        (call $printNumberI32
            (call $returnPI32
                (i32.const 42)
            )
        )
        (call $printNumberI32
            (if (result i32)
                (i32.eq
                    (i32.const 42)
                    (i32.const 41)
                )
                (then
                    (i32.const 42)
                )
                (else
                    (i32.const 0)
                )
            )
        )
        (if 
            (i32.eq 
                (i32.const 42)
                (i32.const 42)
            )
            (then 
                (call $printNumberI32
                    (i32.const 42)
                )
            )
        )
        (nop)
        (loop $label
            (local.set $i
                (i32.add
                    (local.get $i)
                    (i32.const 1)
                )
            )
            (call $printNumberI32 
            	(local.get $i)
            )
            (br_if $label
                (i32.lt_s 
                    (local.get $i)
                    (i32.const 10)
                )
            )
        )
    )
    (start $_start)
)