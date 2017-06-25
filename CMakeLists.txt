cmake_minimum_required(VERSION 3.6)
project(prelamda)

set(CMAKE_C_STANDARD 11)

include_directories(include)

set(SOURCE_FILES main.c
        src/lib/mem.c
        src/gen.c
        src/lib/parse.c
        include/prelamda.h
        include/lib/mem.h
        include/lib/parse.h
        include/gen.h src/token.c include/token.h include/lex.h src/lex.c)

add_executable(prelamda ${SOURCE_FILES})