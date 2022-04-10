cmake_minimum_required(VERSION 3.15)
project(cs-system-principle)

set(CMAKE_CXX_STANDARD 14)

add_executable(cs-system-principle main.cpp relation.cpp
        data_representation.cpp data_representation.c csSysPrinciple.h arrayList.cpp
        myAlloc.cpp strUtil.cpp StringInfo.h
        StringInfo.cpp bigEndOrSmallEnd.cpp asmStrToExplain.cpp myAlloc.h asmStrToExplain.h )