# This file is in root dir to project
# NOTE: DO NOT use ${PROJECT_BINARY_DIR}
#       DO NOT compile symtable.cc alone!
PROJECT(RC_RUNTIME)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${PROJECT_SOURCE_DIR}/src
        ${PROJECT_SOURCE_DIR}/src/rcinterpolator
        ${PROJECT_SOURCE_DIR}/src/plcInterface
        ${PROJECT_SOURCE_DIR}/src/rcinterpolator/estun
        ${PROJECT_SOURCE_DIR}/src/teachbox
        ${PROJECT_SOURCE_DIR}/src/RSI
        ${PROJECT_SOURCE_DIR}/src/Antlr4
        ${PROJECT_SOURCE_DIR}/src/RSI/TinyXml
        ${PROJECT_SOURCE_DIR}/src/codeparser
        ${PROJECT_SOURCE_DIR}/src/dataparser
        ${PROJECT_SOURCE_DIR}/src/rcinterpreter
        ${PROJECT_SOURCE_DIR}/src/utility
        ${PROJECT_SOURCE_DIR}/src/robotmodel
        ${PROJECT_SOURCE_DIR}/src/Interpolation
        /usr/xenomai/include)
ADD_SUBDIRECTORY(src)
