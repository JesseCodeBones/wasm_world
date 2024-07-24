(module
    (memory 1)
    (type $printI64Type (func (param i64)))
    (table $0 4 4 funcref)
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "printNumber" (func $printNumberI64 (param i64) ))
    (import "env" "printNumber" (func $printNumberF32 (param f32) ))
    (import "env" "printNumber" (func $printNumberF64 (param f64) ))

    (func $localPrintI64 (param $0 i64)
        (call $printNumberI64 
            (i64.add
                (local.get $0)
                (i64.const 1)
            )
        )
    )

    (elem $0 (i32.const 0) $printNumberI32 $localPrintI64 $printNumberF32 $printNumberF64)
    (func $_start
        (call_indirect $0 (type $printI64Type)
         (i64.const 42) ;; this is the parameter
         (i32.const 1) ;; this is the function index
        )
    )
    (start $_start)
)