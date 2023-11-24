#!/usr/bin/env python 
import sys 
import subprocess 
import os
def test(args): 
    executable_cmd = ["./test-parse"]+args
    os.chdir("bin") 
    subprocess.run(executable_cmd)

def build(): 
    cmake_cmd = ["cmake","../","-GNinja"] 
    ninja_cmd = ["ninja"] 
    os.chdir("build") 
    subprocess.run(cmake_cmd) 
    subprocess.run(ninja_cmd) 
    os.chdir("../") 
build() 
test(list(sys.argv[1:]))
