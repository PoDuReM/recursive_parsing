cmake_minimum_required(VERSION 3.12)
project(recursive_parsing)

set(CMAKE_CXX_STANDARD 14)

add_executable(recursive_parsing main.cpp LexicalAnalyzer.h Tree.h Parser.h parserTests.h graphUtils.h)
