ENGINE_NAME = "gameover"
PROJECT_NAME = "gameovereditor"
TOOLS_DIR = "tools"

V_MAJOR = 1
V_MINOR = 0

import sys, platform
PLATFORM = sys.platform
for x in platform.uname():
    if "microsoft" in x.lower():
        PLATFORM = "windows"
        break

def IsWindows():
    return PLATFORM == "windows" or PLATFORM == "win32"

def IsLinux():
    return PLATFORM == "linux"

def ProcessArguments(argv):
    ret = {} # return a key:value dict
    for arg in argv:
        try:
            k = arg[0:arg.index("=")]
            v = arg[arg.index("=")+1:]
        except:
            k = arg
            v = 0
        ret[k] = v
    return ret

def GetArgumentValue(args, name, default):
    return args[name] if name in args else default