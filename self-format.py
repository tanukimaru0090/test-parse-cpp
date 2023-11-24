#!/usr/bin/env python
import subprocess
import sys


def self_format(source):
    subprocess.run(["python", "-m", "black", source])


self_format(sys.argv[1])
