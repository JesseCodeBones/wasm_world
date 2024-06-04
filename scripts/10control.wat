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
        (call $printNumberI32
            (call $returnI32)
        )

        (call $printNumberI32
            (call $returnPI32
                (i32.const 42)
            )
        )
    )

    (start $_start)
)