#!/bin/bash

# 定义要扫描的目录
directory="../assemblyscript/tests/compiler/"

# 查找所有以 .debug.wasm 结尾的文件并对每个文件执行命令
find "$directory" -type f -name "*.debug.wasm" | while read -r file; do
  echo "Processing $file"
  ./build/wasm-interpreter "$file"
done
