 (module
       (import "wasi_snapshot_preview1" "args_get" (func $args_get (param $argc i32) (param $argv i32)))
       (import "env" "println" (func $println (param i32) ))
       (memory 1)
       (func $main (export "main")
           (call $args_get 
            (i32.const 0) 
            (i32.const 1024)
           )
            (call $println
                (i32.const 1024)
            )
       )
       (start $main)
   )