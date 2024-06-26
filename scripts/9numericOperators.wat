(module
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (import "env" "printNumber" (func $printNumberI64 (param i64) ))
    (import "env" "printNumber" (func $printNumberF64 (param f64) ))
    (func $_start
        (call $printNumberI32
            (i32.clz
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.clz
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i32.ctz
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.ctz
                (i64.const 42)
            )
        )
        (call $printNumberI32
            (i32.popcnt
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.popcnt
                (i64.const 42)
            )
        )

        (call $printNumberI32
            (i32.add
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.add
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberF32
            (f32.add
                (f32.const 42)
                (f32.const 42)
            )
        )
        (call $printNumberF64
            (f64.add
                (f64.const 42)
                (f64.const 42)
            )
        )
        (call $printNumberI32
            (i32.sub
                (i32.const 42)
                (i32.const 43)
            )
        )
        (call $printNumberI64
            (i64.sub
                (i64.const 42)
                (i64.const 43)
            )
        )
        (call $printNumberF32
            (f32.sub
                (f32.const 42)
                (f32.const 43)
            )
        )
        (call $printNumberF64
            (f64.sub
                (f64.const 42)
                (f64.const 43)
            )
        )

        (call $printNumberI32
            (i32.mul
                (i32.const 42)
                (i32.const 43)
            )
        )
        (call $printNumberI64
            (i64.mul
                (i64.const 42)
                (i64.const 43)
            )
        )
        (call $printNumberF32
            (f32.mul
                (f32.const 42)
                (f32.const 43)
            )
        )
        (call $printNumberF64
            (f64.mul
                (f64.const 42)
                (f64.const 43)
            )
        )

        (call $printNumberI32
            (i32.div_s
                (i32.const 42)
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.div_s
                (i64.const 42)
                (i64.const 42)
            )
        )
        (call $printNumberF32
            (f32.div
                (f32.const 42)
                (f32.const 42)
            )
        )
        (call $printNumberF64
            (f64.div
                (f64.const 42)
                (f64.const 42)
            )
        )

        (call $printNumberI32
            (i32.rem_s
                (i32.const 45)
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.rem_s
                (i64.const 45)
                (i64.const 42)
            )
        )

        (call $printNumberI32
            (i32.rem_s
                (i32.const -45)
                (i32.const 42)
            )
        )
        (call $printNumberI64
            (i64.rem_s
                (i64.const -45)
                (i64.const 42)
            )
        )

        (call $printNumberI32
            (i32.and
                (i32.const 2)
                (i32.const 3)
            )
        )
        (call $printNumberI64
            (i64.and
                (i64.const 2)
                (i64.const 3)
            )
        )

        (call $printNumberI32
            (i32.or
                (i32.const 2)
                (i32.const 3)
            )
        )
        (call $printNumberI64
            (i64.or
                (i64.const 2)
                (i64.const 3)
            )
        )

        (call $printNumberI32
            (i32.xor
                (i32.const 2)
                (i32.const 3)
            )
        )
        (call $printNumberI64
            (i64.xor
                (i64.const 2)
                (i64.const 3)
            )
        )
        (call $printNumberI32
            (i32.shl
                (i32.const 1)
                (i32.const 3)
            )
        )
        (call $printNumberI64
            (i64.shl
                (i64.const 1)
                (i64.const 3)
            )
        )

        (call $printNumberI32
            (i32.shr_s
                (i32.const -8)
                (i32.const 2)
            )
        )
        (call $printNumberI64
            (i64.shr_s
                (i64.const -8)
                (i64.const 2)
            )
        )

        (call $printNumberI32
            (i32.shr_u
                (i32.const -8)
                (i32.const 2)
            )
        )
        (call $printNumberI64
            (i64.shr_u
                (i64.const -8)
                (i64.const 2)
            )
        )
        (call $printNumberI32
            (i32.rotl
                (i32.const 1)
                (i32.const 2)
            )
        )
        (call $printNumberI64
            (i64.rotl
                (i64.const 1)
                (i64.const 2)
            )
        )
        (call $printNumberI32
            (i32.rotr
                (i32.const 1)
                (i32.const 2)
            )
        )
        (call $printNumberI64
            (i64.rotr
                (i64.const 1)
                (i64.const 2)
            )
        )

        (call $printNumberF32
            (f32.abs
                (f32.const -42)
            )
        )
        (call $printNumberF64
            (f64.abs
                (f64.const -42)
            )
        )
        (call $printNumberF32
            (f32.neg
                (f32.const 42)
            )
        )
        (call $printNumberF64
            (f64.neg
                (f64.const 42)
            )
        )
        (call $printNumberF32
            (f32.ceil
                (f32.const 42.1)
            )
        )
        (call $printNumberF64
            (f64.ceil
                (f64.const 42.1)
            )
        )

        (call $printNumberF32
            (f32.floor
                (f32.const 42.1)
            )
        )
        (call $printNumberF64
            (f64.floor
                (f64.const 42.1)
            )
        )

        (call $printNumberF32
            (f32.trunc
                (f32.const 42.99999)
            )
        )
        (call $printNumberF64
            (f64.trunc
                (f64.const 42.99999)
            )
        )

        (call $printNumberF32
            (f32.nearest
                (f32.const 42.99999)
            )
        )
        (call $printNumberF64
            (f64.nearest
                (f64.const 42.99999)
            )
        )

        (call $printNumberF32
            (f32.sqrt
                (f32.const 42.1)
            )
        )
        (call $printNumberF64
            (f64.sqrt
                (f64.const 42.1)
            )
        )

        (call $printNumberF32
            (f32.min
                (f32.const 42.1)
                (f32.const -1)
            )
        )
        (call $printNumberF64
            (f64.min
                (f64.const 42.1)
                (f64.const -1)
            )
        )

        (call $printNumberF32
            (f32.max
                (f32.const 42.1)
                (f32.const -1)
            )
        )
        (call $printNumberF64
            (f64.max
                (f64.const 42.1)
                (f64.const -1)
            )
        )

        (call $printNumberF32
            (f32.copysign
                (f32.const 42.1)
                (f32.const -1)
            )
        )
        
        (call $printNumberF64
            (f64.copysign
                (f64.const 42.1)
                (f64.const -1)
            )
        )

        (call $printNumberI32
            (i32.wrap_i64
                (i64.const 0xffffffffffffffff)
            )
        )

        (call $printNumberI32
            (i32.trunc_f32_s
                (f32.const 42.9)
            )
        )

        (call $printNumberI32
            (i32.trunc_f32_u
                (f32.const 42.1)
            )
        )

        (call $printNumberI32
            (i32.trunc_f64_s
                (f64.const 42.9)
            )
        )

        (call $printNumberI32
            (i32.trunc_f64_u
                (f64.const 42.1)
            )
        )

        (call $printNumberI64
            (i64.trunc_f32_s
                (f32.const 42.9)
            )
        )

        (call $printNumberI64
            (i64.trunc_f32_u
                (f32.const 42.1)
            )
        )

        (call $printNumberI64
            (i64.trunc_f64_s
                (f64.const 42.9)
            )
        )

        (call $printNumberI64
            (i64.trunc_f64_u
                (f64.const 42.1)
            )
        )

        (call $printNumberI64
            (i64.extend_i32_s
                (i32.const -1)
            )
        )
        (call $printNumberI64
            (i64.extend_i32_u
                (i32.const -1)
            )
        )

        (call $printNumberF32
            (f32.demote_f64
                (f64.const 42.1)
            )
        )

        (call $printNumberF64
            (f64.promote_f32
                (f32.const 42.1)
            )
        )

        (call $printNumberF32
            (f32.convert_i32_s
                (i32.const -1)
            )
        )
        (call $printNumberF32
            (f32.convert_i32_u
                (i32.const -1)
            )
        )
        (call $printNumberF32
            (f32.convert_i64_s
                (i64.const -1)
            )
        )
        (call $printNumberF32
            (f32.convert_i64_u
                (i64.const -1)
            )
        )
        (call $printNumberF64
            (f64.convert_i32_s
                (i32.const -1)
            )
        )
        (call $printNumberF64
            (f64.convert_i32_u
                (i32.const -1)
            )
        )
        (call $printNumberF64
            (f64.convert_i64_s
                (i64.const -1)
            )
        )
        (call $printNumberF64
            (f64.convert_i64_u
                (i64.const -1)
            )
        )
        (call $printNumberI32
            (i32.reinterpret_f32
                (f32.const -0)
            )
        )
        (call $printNumberI64
            (i64.reinterpret_f64
                (f64.const -0)
            )
        )
        (call $printNumberF32
            (f32.reinterpret_i32
                (i32.const 0x3F800000)
            )
        )
        (call $printNumberF64
            (f64.reinterpret_i64
                (i64.const 0x3FF0000000000000)
            )
        )

        (call $printNumberI32
            (i32.extend8_s
                (i32.const 0xff)
            )
        )
        (call $printNumberI32
            (i32.extend16_s
                (i32.const 0xffff)
            )
        )

        (call $printNumberI64
            (i64.extend8_s
                (i64.const 0xff)
            )
        )
        (call $printNumberI64
            (i64.extend16_s
                (i64.const 0xffff)
            )
        )
        (call $printNumberI64
            (i64.extend32_s
                (i64.const 0xffffffff)
            )
        )
    )
    (start $_start)
)