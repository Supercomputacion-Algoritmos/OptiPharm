cmake_minimum_required (VERSION 2.8.9)

# Options. Turn on with 'cmake -Dmyvarname=ON'.
option(test "Build all tests." ON) # Makes boolean 'test' available.

project (OPTIPHARM)

set(EXECUTABLE_OUTPUT_PATH "bin/")

set(CMAKE_BUILD_TYPE Debug)

if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
  #Set up static link general libraries
  SET(CMAKE_FIND_LIBRARY_SUFFIXES ".a")
  SET(BUILD_SHARED_LIBRARIES OFF)
  SET(CMAKE_EXE_LINKER_FLAGS "-static")
endif()

if (MSVC)
  Set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /O2 ${SSE_FLAGS}")
else (MSVC)
  set(CMAKE_CXX_FLAGS "-O3 ${CMAKE_CXX_FLAGS} ${SSE_FLAGS}")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -O0 -g ${SSE_FLAGS}")
  set(CMAKE_CXX_FLAGS_RELEASE " ${CMAKE_CXX_FLAGS} -O3 ${SSE_FLAGS}")
endif (MSVC)



#Include headers for a 1 objetive
#target_include_directories(OP_MI PUBLIC includeh/functions includeh/model includeh/read_write includeh/test includeh/uego)

#Bring the headers
include_directories(includeh/uego includeh/functions includeh/model includeh/read_write includeh/test libs/eigen335)



# at the place where we define compiler flags (could be CMakeLists.txt)
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
   	set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11 -O2")
    #set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -Wall -g -ggdb -O0")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O2")
elseif(CMAKE_CXX_COMPILER_ID MATCHES Clang)
	SET (CMAKE_C_COMPILER             "/usr/bin/clang")
    SET (CMAKE_C_FLAGS                "-Wall -std=c99")
    SET (CMAKE_C_FLAGS_DEBUG          "-g")
    SET (CMAKE_C_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

    SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
    #SET (CMAKE_CXX_FLAGS                "-Wall -std=c++11 -O2")
    SET (CMAKE_CXX_FLAGS                "-Wall -std=c++11 -O0 -g -ggdb")
    SET (CMAKE_CXX_FLAGS_DEBUG          "-g")
    SET (CMAKE_CXX_FLAGS_MINSIZEREL     "-Os -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELEASE        "-O4 -DNDEBUG")
    SET (CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

    SET (CMAKE_AR      "/usr/bin/llvm-ar")
    SET (CMAKE_LINKER  "/usr/bin/llvm-ld")
    SET (CMAKE_NM      "/usr/bin/llvm-nm")
    SET (CMAKE_OBJDUMP "/usr/bin/llvm-objdump")
    SET (CMAKE_RANLIB  "/usr/bin/llvm-ranlib")
    add_definitions(-D_GLIBCXX_USE_CXX11_ABI=0)
endif()
set(default_target "OPShapeSimilarity")

#SOURCES
set(MENSAJES "src/uego/usrintf/msgintf.cc")
file(GLOB FUNCTIONS "src/functions/*")
file(GLOB MODELS "src/model/*")
file(GLOB READWRITE "src/read_write/*")
file(GLOB UEGOSHAPESIMILARITY "src/uego/usrintf/configur.cc" "src/uego/*.cc" "src/uego/project/molvalSS.cc" "src/uego/project/nrealopt.cc" ${MENSAJES} )

#Executables
add_executable(OPShapeSimilarity  ${UEGOSHAPESIMILARITY} "src/uego/usrintf/main.cc" ${FUNCTIONS} ${MODELS} ${READWRITE}  )


add_executable(OP_SS  ${MENSAJES} ${FUNCTIONS} ${MODELS} ${READWRITE}  "src/test/calculateShapeSimilarity.cpp")
add_executable(OP_MRMS  ${MENSAJES} ${FUNCTIONS} ${MODELS} ${READWRITE} "src/test/MoveRotateMolSave.cpp")
add_executable(OP_WRMOL2  ${MENSAJES} ${FUNCTIONS} ${MODELS} ${READWRITE} "src/test/ReadWriteMol2.cpp")
add_executable(OP_MI  ${MENSAJES} ${FUNCTIONS} ${MODELS} ${READWRITE} "src/test/MoleculeInfo.cpp")
add_executable(OP_ALIGN  ${MENSAJES} ${FUNCTIONS} ${MODELS} ${READWRITE} "src/test/AlignMolecule.cpp")





