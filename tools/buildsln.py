import globals
import os, sys, subprocess

args = globals.ProcessArguments(sys.argv)
CONFIG = globals.GetArgumentValue(args, "config", "debug")

print("Building config: " + CONFIG)
print("\n")
ret = 0

if globals.IsWindows():
    VS_BUILD_PATH = "Program Files\Microsoft Visual Studio\\2022\Community\MSBuild\Current\Bin\MSBuild.exe"
    VS_BUILD_PATH = "C:\\" + VS_BUILD_PATH

    ret = subprocess.call(["cmd.exe", "/c", VS_BUILD_PATH, "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(CONFIG)])


if globals.IsLinux():
    ret = subprocess.call(["make", "config={}".format(CONFIG)])

sys.exit(ret)