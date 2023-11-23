#!/Users/daruma/.pyenv/pyenv-win/versions/3.9.5/python.exe
import sys 
import subprocess
import os  
def test(args):
    executable_cmd = ["test-parse ",args]
    os.chdir("../bin")
    subprocess.run(executable_cmd)


def build():
    cmake_cmd = ["cmake","../","-GNinja"]
    ninja_cmd = ["ninja"]
    os.chdir("build")
    subprocess.run(cmake_cmd)
    subprocess.run(ninja_cmd)
build()
test(sys.argv[1:])
