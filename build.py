#!/usr/bin/env python
import sys
import subprocess
import os
import os.path
import time


def test(args):
    executable_name = "./test-parse"

    executable_cmd = [executable_name] + args
    os.chdir("bin")
    subprocess.run(executable_cmd)


def build():
    cmake_conf_path = "./CMakeLists.txt"
    current_time = time.time()
    modification_time = os.path.getmtime(cmake_conf_path)
    diff_time = current_time - modification_time

    os.chdir("build")
    cmake_command = ["cmake", "../", "-GNinja"]
    ninja_command = ["ninja"]
    # 1分以内に更新があった場合
    if diff_time <= 60:
        print('"', cmake_conf_path, '"', "が", "更新されたのでビルド情報を更新します")
        subprocess.run(cmake_command)
        print("ビルド中...")
        subprocess.run(ninja_command)
    # 更新がない場合
    else:
        print(cmake_conf_path, "の", "更新がないため通常通りビルドをします")
        print("ビルド中...")
        subprocess.run(ninja_command)

    os.chdir("../")


build()
test(list(sys.argv[1:]))
