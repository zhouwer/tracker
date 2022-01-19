include_directories("/usr/include/eigen3")
cmake_minimum_required(VERSION 2.6)

project(yolosort)
list(APPEND CUDA_NVCC_FLAGS "-std=c++11")
set(CMAKE_CXX_FLAGS "-std=c++0x")
find_package(OpenCV REQUIRED)
add_definitions(-std=c++11)
add_definitions(-DAPI_EXPORTS)
option(CUDA_USE_STATIC_CUDA_RUNTIME OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_BUILD_TYPE Release)
#find_package(Threads) #引入Threads外部依赖包

#set( CMAKE_CXX_FLAGS “${CMAKE_CXX_FLAGS} -std=c++11 -march=native -O3 -pthread” )

find_package(CUDA REQUIRED)
set(CUDA_NVCC_PLAGS ${CUDA_NVCC_PLAGS};-std=c++11;-g;-G;-gencode;arch=compute_53;code=sm_53)

if(WIN32)
enable_language(CUDA)
endif(WIN32)

include_directories(${PROJECT_SOURCE_DIR}/deepsort/include)
# include and link dirs of cuda and tensorrt, you need adapt them if yours are different
# cuda
include_directories(/usr/local/cuda/include)
link_directories(/usr/local/cuda/lib64)
# tensorrt
#include_directories(/usr/include/gcc/x86_64-linux-gnu/)
#link_directories(/usr/lib/gcc/x86_64-linux-gnu/)
include_directories(/home/w/tensorRT/ten70011/include/)
link_directories(/home/w/tensorRT/ten70011/lib/)

include_directories(
    ${CUDA_INCLUDE_DIRS}
    ${OpenCV_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/deepsort/include
)
aux_source_directory(${PROJECT_SOURCE_DIR}/deepsort/src SRC_DIR)

# ===== deepsort =====
add_library(deepsort SHARED ${SRC_DIR})
target_link_libraries(deepsort 
    ${CUDA_LIBS} ${OpenCV_LIBS} 
    cudart nvinfer nvonnxparser
)

# ===== yolo =====
include_directories(${PROJECT_SOURCE_DIR}/yolo/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/yolo/src YOLO_SRC_DIR)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Ofast -Wfatal-errors -D_MWAITXINTRIN_H_INCLUDED")

cuda_add_library(yolov5_trt SHARED ${PROJECT_SOURCE_DIR}/yolo/include/yololayer.cu ${PROJECT_SOURCE_DIR}/yolo/src/yolov5_lib.cpp)
target_link_libraries(yolov5_trt nvinfer cudart deepsort) 


# ===== main =====
aux_source_directory(${PROJECT_SOURCE_DIR}/src M_SRC_DIR)
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(yolosort ${M_SRC_DIR})

target_link_libraries(yolosort nvinfer cudart yolov5_trt)

if(UNIX)
add_definitions(-O2 -pthread)
endif(UNIX)
set(CMAKE_CXX_FLAGS "-std=c++0x")




cmake_minimum_required(VERSION 3.10.0)
 
#project(Build_Qt_Demo)
 
#开启MOC、RCC和UIC，则会在预处理之前先进行MOC、RCC和UIC操作
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
 
#设置UIC的查找路径，UIC默认会在引用ui头文件的源代码路径下查找ui文件，而我们的ui文件存放在/ui文件夹下
#set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR}/ui)
set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_SOURCE_DIR})
 
#设置可执行文件的输出路径，默认在哪个路径编译则会放在哪个路径，而我们是在/build下编译，要存放在/bin路径
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
 
#查找需要的Qt包
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
 
#将各个文件夹下的所有文件打包
#FILE(GLOB ${PROJECT_NAME}_SOURCES "./src/*.cpp")
FILE(GLOB ${PROJECT_NAME}_UI "*.ui")
#FILE(GLOB ${PROJECT_NAME}_QRC "./qrc/*.qrc")
#FILE(GLOB ${PROJECT_NAME}_HEADER "./include/*")
 
#将/include路径包含到查找头文件路径
include_directories(${PROJECT_SOURCE_DIR}/include)
 
#直接将上述的所有文件进行编译和内部链接，ui和qrc以及包含Qt扩展语法的文件由于开启了开启MOC、RCC和UIC，因此会被自行处理
#add_executable(${PROJECT_NAME}
 #         ${${PROJECT_NAME}_UI}
 #         ${${PROJECT_NAME}_SOURCES}
 #         ${${PROJECT_NAME}_QRC}
 #         ${${PROJECT_NAME}_HEADER}
  #        )       
 
#和Qt的库进行链接
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Gui Qt5::Widgets)
target_link_libraries (${PROJECT_NAME} pthread) #依赖线程
find_package (Threads)
#add_executable (yolosort main.cpp mainwindow.cpp)
#target_link_libraries (yolosort ${CMAKE_THREAD_LIBS_INIT})
