import sys, subprocess
import globals

ret = 0

if globals.IsWindows():
    ret = subprocess.call(["cmd.exe", "/c", "premake5\\premake5", "vs2022"])

if globals.IsLinux():
    ret = subprocess.call(["premake5/premake5.linux", "gmake2"])

sys.exit(ret)