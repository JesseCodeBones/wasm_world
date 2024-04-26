(module
    (memory 1)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (func $test (param $a i32)
        (local $b i32)
        (local.set $b (local.get $a))
        (call $printNumberI32
            (local.get $b)
        )
    )
    (func $_start
        (call $test
            (i32.const 42)
        )
    )
    (start $_start)
)