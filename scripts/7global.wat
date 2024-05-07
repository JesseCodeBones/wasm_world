(module
    (memory 1)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (global $g1 (mut i32) (i32.const 0))
    (global $g2 f32 (f32.const 42.0))
    (func $_start
        (global.set $g1 (i32.const 42))
        (call $printNumberI32
            (global.get $g1)
        )
        (call $printNumberF32
            (global.get $g2)
        )
    )
    (start $_start)
)