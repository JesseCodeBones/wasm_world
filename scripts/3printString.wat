(module
    (memory 1)
    (data (i32.const 0) "hello world\00")
    (import "env" "println" (func $println (param i32) ))
    (func $_start
        (call $println
            (i32.const 0)
        )
    )
    (start $_start)
)