import sys, subprocess
import globals

ret = 0
if globals.IsWindows():
    ANDROID_BUILD = "../platform/tools/platform-tools-windows"
    ret = subprocess.call(["cmd.exe", "/c", ])
if globals.IsLinux():
    ANDROID_BUILD = "../platform/tools/platform-tools-linux"
    ret = subprocess.call(["./{}".format(ANDROID_BUILD)])
sys.exit(ret)