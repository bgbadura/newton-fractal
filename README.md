CLion configuration that worked for me:

Settings -> Build, Execution, Deployment -> Toolchains:
  - Name: WSL
  - Toolset: Ubuntu
  - CMake: WSL CMake
  - Build tool: /usr/bin/ninja
  - C Compiler: /usr/bin/cc
  - C++ Compiler: /usr/bin/c++
  - Debugger: /usr/bin/gdb

Settings -> Build, Execution, Deployment -> CMake:
  - Name: Debug-WSL
  - Build Type: Debug
  - Toolchain: WSL
  - Generator: Ninja
  - CMake options: -DCMAKE_ISPC_COMPILER=/usr/bin/ispc
