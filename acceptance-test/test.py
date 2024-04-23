import os
import subprocess, sys

# 获取 script 文件夹下所有 .wasm 文件
current_directory = os.getcwd()
folder_path = os.path.join(current_directory, "../scripts/")
executable_path = os.path.join(current_directory, "../build/wasm-interpreter")
wasm_files = [f for f in os.listdir(folder_path) if f.endswith('.wasm')]
runnable = os.path.abspath(executable_path)
if sys.platform.startswith('win'):
    runnable += ".exe"
for index, wasm_file in enumerate(wasm_files):
    # 获取对应的 .log 文件名
    log_file = wasm_file.replace('.wasm', '.log')
    log_file = os.path.join(current_directory, '../scripts/', log_file)
    if os.path.exists(log_file):
        # 执行 wasm 文件，获取其标准输出
        print(f"executing test {str(index)} / {len(wasm_files)} - {wasm_file} ... ")
        result = subprocess.run([runnable, os.path.join(folder_path, wasm_file)], capture_output=True, text=True)
        output = result.stdout
        print(f"script output: {output}")

        # 读取 log 文件的内容
        with open(os.path.join(folder_path, log_file), 'r') as f:
            log_content = f.read()

        # 比较标准输出和 log 文件内容
        if output != log_content:
            print(f"Error: Output of {wasm_file} does not match {log_file}")
            os._exit(1)
        else:
            print(f" √ success test {str(index)} / {len(wasm_files)} - {wasm_file}")
