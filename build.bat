set flags=-Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm -lmsvcrt -lUser32 -lshell32 -std=c++17
set localLinks=-Isrc/core

clang %localLinks% %flags% src/*.cpp src/core/*.cpp -Xlinker /NODEFAULTLIB:libcmt