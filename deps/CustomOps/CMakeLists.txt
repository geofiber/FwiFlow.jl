cmake_minimum_required(VERSION 3.5)
project(TF_CUSTOM_OP)
set (CMAKE_CXX_STANDARD 11)

execute_process(COMMAND julia -e "import ADCME; print(ADCME.__STR__)" OUTPUT_VARIABLE JL_OUT)
execute_process(COMMAND which julia OUTPUT_VARIABLE JULIA_BIN)
message("Julia=${JULIA_BIN}")

list(GET JL_OUT 0 BINDIR)
list(GET JL_OUT 1 LIBDIR)
list(GET JL_OUT 2 TF_INC)
list(GET JL_OUT 3 TF_ABI)
list(GET JL_OUT 4 EIGEN_INC)
list(GET JL_OUT 5 CC)
list(GET JL_OUT 6 CXX)
list(GET JL_OUT 7 CMAKE)
list(GET JL_OUT 8 MAKE)
list(GET JL_OUT 9 GIT)
list(GET JL_OUT 10 PYTHON)
list(GET JL_OUT 11 TF_LIB_FILE)
list(GET JL_OUT 12 LIBCUDA)
list(GET JL_OUT 13 CUDA_INC)

message("Python path=${PYTHON}")
message("EIGEN_INC=${EIGEN_INC}")
message("TF_INC=${TF_INC}")
message("TF_ABI=${TF_ABI}")
message("TF_LIB_FILE=${TF_LIB_FILE}")


if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 5.0 OR CMAKE_CXX_COMPILER_VERSION VERSION_EQUAL 5.0)
  set(CMAKE_CXX_FLAGS "-D_GLIBCXX_USE_CXX11_ABI=${TF_ABI} ${CMAKE_CXX_FLAGS}")
endif()

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

include_directories(${TF_INC} ${EIGEN_INC}/eigen3 ${EIGEN_INC} ${CUDA_INC} ${LIBDIR}/../include ${LIBDIR}/../include/boost ../amgcl/)
link_directories(${LIBDIR} ${LIBCUDA})
include_directories(FWI/Src/rapidjson)

# add_definitions(-DVERBOSE)

find_program(_nvidia_smi "nvcc")
if (_nvidia_smi)
 message("################# Compiling GPU-compatible custom operator ################# ")
 add_subdirectory(FWI)
 #-------------------------------------------------------------------------------------
  add_subdirectory(FWI/Src)
endif()


find_package(OpenMP)
if (OPENMP_FOUND)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
endif()

set(LIBDIR_NAME Laplacian Poisson Saturation Saturation2 Upwlap Upwps Eikonal)

# Copy and paste the following lines (no modification is required)
list(LENGTH "LIBDIR_NAME" LIBLENGTH)
message("Total number of libraries to make: ${LIBLENGTH}")
MATH(EXPR LIBLENGTH "${LIBLENGTH}-1")
foreach(IDX RANGE 0 ${LIBLENGTH})
  list(GET LIBDIR_NAME ${IDX} _LIB_NAME)
  message("Compiling ${IDX}th library: ${_LIB_NAME}")
  add_subdirectory(${_LIB_NAME})
endforeach(IDX)



