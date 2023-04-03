cmake_minimum_required(VERSION 3.14)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)  

# set project name
project(student_t_distribution)

# get external library FLTK
set(FLTK_BUILD_TEST OFF CACHE BOOL " " FORCE)
if(UNIX AND NOT APPLE) 
    set(OPTION_USE_PANGO ON CACHE BOOL " " FORCE)
endif()
FetchContent_Declare(
  FLTK
  GIT_REPOSITORY https://github.com/fltk/fltk
  GIT_TAG        24c63c0774c2ca8bd0bd5f346df1b8728da2e8cf
)
FetchContent_MakeAvailable(FLTK)
if(WIN32)
    set(GUI_TYPE WIN32)
elseif(APPLE)
    set(GUI_TYPE MACOSX_BUNDLE)
else()
    set(GUI_TYPE)
endif()


# get external library boost math
include(FetchContent)  
FetchContent_Declare(boostmath
    GIT_REPOSITORY "https://github.com/boostorg/math.git"         
    GIT_TAG boost-1.81.0)
FetchContent_MakeAvailable(boostmath) 

# get external library DocTest
FetchContent_Declare(doctest 
    GIT_REPOSITORY "https://github.com/onqtam/doctest"         
    GIT_TAG "b7c21ec5ceeadb4951b00396fc1e4642dd347e5f" )
FetchContent_MakeAvailable(doctest) 

# add library target
add_library(ar STATIC "")
target_sources(ar
    PRIVATE
        src/ar/AR_UCI_Graph_Creation.cpp
    PUBLIC
        src/ar/AR_UCI_Graph_Creation_IB.h
        src/ar/AR_UCI_Graph_Creation_OB.h
        src/ar/AR_UCI_Graph_Creation.h
        src/ar/AR_STAT_Util_I.h
)
target_include_directories(ar PRIVATE src/fd)
target_link_libraries(ar fd)

# add library target
add_library(ia STATIC "")
target_sources(ia
    PRIVATE
        src/ia/IA_Master_Controller_GUI.cpp
        src/ia/IA_Graph_Creation_Presenter_GUI.cpp
        src/ia/IA_Graph_Creation_Controller_GUI.cpp
    PUBLIC
        src/ia/IA_GUI_Manager_I.h    
        src/ia/IA_Master_Controller_GUI.h
        src/ia/IA_Graph_Creation_Presenter_GUI.h
        src/ia/IA_Graph_Creation_Controller_GUI.h
)
target_include_directories(ia PRIVATE src/ar)
target_include_directories(ia PRIVATE src/fd)
target_link_libraries(ia ar)
target_link_libraries(ia fd)

# add library target
add_library(fd STATIC "")
target_sources(fd
    PRIVATE
        src/fd/FD_GUI_View_Window_Graph.cpp
        src/fd/FD_GUI_Manager.cpp
        src/fd/FD_GUI_View_Graph.cpp
        src/fd/FD_STAT_Util.cpp
    PUBLIC
        src/fd/FD_GUI_View_Window_Graph.h
        src/fd/FD_GUI_Manager.h
        src/fd/FD_GUI_View_Graph.h
        src/fd/FD_STAT_Util.h
)
target_include_directories(fd PRIVATE src/ar)
target_include_directories(fd PRIVATE src/ia)
target_include_directories(fd PRIVATE ${fltk_SOURCE_DIR})
target_include_directories(fd PRIVATE ${fltk_BINARY_DIR})
target_include_directories(fd 
                PUBLIC ${boostmath_SOURCE_DIR}/include)
target_link_libraries(fd ar)
target_link_libraries(fd ia)
target_link_libraries(fd fltk)
target_link_libraries(fd Boost::math)
if (APPLE)
  target_link_libraries(fd "-framework cocoa")
endif (APPLE)

# add main executable target
add_executable(${CMAKE_PROJECT_NAME} ${GUI_TYPE} src/main.cpp)
target_include_directories(${CMAKE_PROJECT_NAME} 
                           PRIVATE src/ar 
                           PRIVATE src/ia 
                           PRIVATE src/fd
                           PRIVATE ${fltk_SOURCE_DIR} PRIVATE ${fltk_BINARY_DIR}
                           )
target_link_libraries(${CMAKE_PROJECT_NAME} ar)
target_link_libraries(${CMAKE_PROJECT_NAME} ia)
target_link_libraries(${CMAKE_PROJECT_NAME} fd)
target_link_libraries(${CMAKE_PROJECT_NAME} fltk)
if (APPLE)
  target_link_libraries(${CMAKE_PROJECT_NAME} "-framework cocoa")
endif (APPLE)

# add test executable target
add_executable(${CMAKE_PROJECT_NAME}_test)
target_sources(${CMAKE_PROJECT_NAME}_test
    PRIVATE
    src/test/base_config_main_test.cpp
    src/test/FD_STAT_Util_test.cpp
)
target_include_directories(${CMAKE_PROJECT_NAME}_test PRIVATE
                           PRIVATE src/ar PRIVATE src/ia PRIVATE src/fd 
                           ${doctest_SOURCE_DIR}/doctest)
target_link_libraries(${CMAKE_PROJECT_NAME}_test ar)
target_link_libraries(${CMAKE_PROJECT_NAME}_test ia)
target_link_libraries(${CMAKE_PROJECT_NAME}_test fd)
target_link_libraries(${CMAKE_PROJECT_NAME}_test doctest)
