(module
    (memory 1)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (func $test (param $a1 i32) (param $a2 f32)
        (local $b i32)
        (local $c i32)
        (local $d f32)
        (local $e f64)
        (local $f f32)
        (local.set $b (local.get $a1))
        (local.set $f (local.get $a2))
        (call $printNumberI32
            (local.get $b)
        )
        (call $printNumberF32
            (local.get $f)
        )
        (call $printNumberI32
            (local.tee $c (i32.const 24))
        )
        (call $printNumberI32
            (local.get $c)
        )
    )
    (func $_start
        (call $test
            (i32.const 42)
            (f32.const 42.0)
        )
    )
    (start $_start)
)