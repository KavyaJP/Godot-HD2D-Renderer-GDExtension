#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# tweak this if you want to use different folders, or more folders, to store your source code in.
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")

if env["platform"] == "macos":
    library = env.SharedLibrary(
        "hd-2d-renderer-demo/bin/libhd2d.{}.{}.framework/libhd2d.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "hd-2d-renderer-demo/bin/libhd2d{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)
