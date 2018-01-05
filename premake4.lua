#!lua

solution "TileEngine"
  configurations { "Debug", "Release", "WindowsDebug" }

  project "TileEngine"
    kind "ConsoleApp"
    language "C++"

    targetname "TileEngine"

    includedirs { "./include", "./src" }

    files { "**.h", "**.hpp", "**.cpp", "**.cc" }
    excludes { "./test/**, ./deps/**" }

    configuration "WindowsDebug"
      buildoptions { "-std=c++11" }
      links { "freetype_win", "yse", "glfw3", "gdi32", "glew32s", "opengl32", "png", "z", "DevIL", "chaiscript_stdlib-5.8.5" }
      defines { "DEBUG", "GLEW_STATIC" }
      targetextension ".exe"

    configuration "Debug"
      buildoptions { "-std=c++14", "-Wno-unknown-pragmas", "-g", "-O0", '-pthread' }
      links {  "freetype", "yse", "glfw", "png", "z", "OpenGL.framework", "glew", "IL" }
      defines { "DEBUG" }
      flags { "Symbols" }
      targetextension ".out"

    configuration "Release"
      buildoptions { "-std=c++11", "-Wno-unknown-pragmas", "-g", "-O0", '-pthread' }
      links {  "freetype", "yse", "glfw3.3.1", "png", "z", "OpenGL.framework", "glew", "IL", "chaiscript_stdlib-5.8.5" }
      defines { "NDEBUG" }
      flags { "Optimize" }
      targetextension ".out"
