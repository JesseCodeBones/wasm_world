(module
    (memory 1)
    (data (i32.const 0) "hello world\00")
    (func $_start (export "_start")
        (drop
            (i32.const 1)
        )
    )
)