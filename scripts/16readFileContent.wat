(module
    (memory 2)
    (data (i32.const 0) "./scripts/16readFileContent.wat\00")
    (import "env" "printNumber" (func $printNumberI32 (param i32) ))
    (import "env" "println" (func $println (param i32) ))
    (import "env" "readFileContent" (func $readFileContent (param i32 i32 i32) ))
    (func $_start
        (call $readFileContent
            (i32.const 0) ;; file path
            (i32.const 1024) ;; file size ptr
            (i32.const 1028) ;; file content ptr
        )
        (call $printNumberI32
            (i32.load
                (i32.const 1024)
            )
        )
        (call $println
            (i32.const 1028)
        )
    )
    (start $_start)
)