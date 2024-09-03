(module
(func $_start (export "_start")
(local $1 i32)
(local $2 i32)
(local $3 i32)
i32.const 1
local.tee $1
i32.const 2
local.tee $2
local.get $1
local.get $2
i32.gt_s
select ;; Defect select the 1 instead of the 2
local.set  $3
local.get  $3
i32.const 2
i32.eq
i32.eqz
if
unreachable
end
)

)