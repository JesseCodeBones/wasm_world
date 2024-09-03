(module
(import "env" "printNumber" (func $printNumberI32 (param i32) ))
(import "env" "println" (func $println (param i32) ))
(memory 1)
(global $for/ran (mut i32) (i32.const 0))
(data (i32.const 0) "come into loop\00")
(func $for/testNestedContinue
  (local $i i32)
  (local $j i32)
  (local $k i32)
  i32.const 0
  local.set $i
  i32.const 0
  local.set $j
  i32.const 0
  local.set $k
;;   嵌套循环 有问题，第二个循环体并没有从0开始
  loop $for-loop|0
   local.get $i
   i32.const 10
   i32.lt_s
   if
    block $for-continue|0
     local.get $i
     i32.const 2
     i32.lt_s
     if
      br $for-continue|0
     end
     i32.const 0
     local.set $j
     loop $for-loop|1
      local.get $j
      i32.const 10
      i32.lt_s
      if
       block $for-continue|1
        local.get $i
        local.get $j
        i32.lt_s
        if
         local.get $k
         i32.const 1
         i32.add
         local.set $k
         i32.const 0
         call $println
         local.get $i
         call $printNumberI32
         local.get $j
         call $printNumberI32
         local.get $k
         call $printNumberI32
         br $for-continue|1
        end
       end
       local.get $j
       i32.const 1
       i32.add
       local.set $j
       br $for-loop|1
      end
     end
    end
    local.get $i
    i32.const 1
    i32.add
    local.set $i
    br $for-loop|0
   end
  end
  local.get $i
  i32.const 10
  i32.eq
  i32.eqz
  if
   unreachable
  end
  local.get $j
  i32.const 10
  i32.eq
  i32.eqz
  if
   unreachable
  end
  local.get $k
  i32.const 28
  i32.eq
  i32.eqz
  if
   unreachable
  end
  i32.const 1
  global.set $for/ran
 )

 (start $for/testNestedContinue)
)