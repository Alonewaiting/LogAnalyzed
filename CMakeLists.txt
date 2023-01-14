cmake_minimum_required(VERSION 3.3)
project(LogAnalyze)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
set(CJSON_PATH ${PROJECT_SOURCE_DIR}/cJSON)
set(IMAGUI_PATH ${PROJECT_SOURCE_DIR}/imgui)
set(SRC_PATH ${PROJECT_SOURCE_DIR}/src)
if(MSVC)
  # Force to always compile with W4
  set(CMAKE_CXX_FLAGS"${CMAKE_CXX_FLAGS} /W4")

elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  # Update if necessary
  set(CMAKE_CXX_FLAGS"${CMAKE_CXX_FLAGS} -Wall -Wno-long-long -pedantic")
endif()

include_directories(${CJSON_PATH})
include_directories(${IMAGUI_PATH})
include_directories(${IMAGUI_PATH}/backends)
set(CJSON_SRC_FILS
	${CJSON_PATH}/cJSON.c
	${CJSON_PATH}/cJSON_Utils.c
	)
set(IMGUI_SRC_FILS)
if(MSVC)
set(IMGUI_SRC_FILS
	${IMAGUI_PATH}/imconfig.h
	${IMAGUI_PATH}/imgui.cpp
	${IMAGUI_PATH}/imgui.h
	${IMAGUI_PATH}/imgui_demo.cpp
	${IMAGUI_PATH}/imgui_draw.cpp
	${IMAGUI_PATH}/imgui_tables.cpp
	${IMAGUI_PATH}/imgui_widgets.cpp
	${IMAGUI_PATH}/imgui_internal.h
	${IMAGUI_PATH}/backends/imgui_impl_dx11.cpp
	${IMAGUI_PATH}/backends/imgui_impl_win32.cpp
	)
else()
set(IMGUI_SRC_FILS
	${IMAGUI_PATH}/imconfig.h
	${IMAGUI_PATH}/imgui.cpp
	${IMAGUI_PATH}/imgui.h
	${IMAGUI_PATH}/imgui_demo.cpp
	${IMAGUI_PATH}/imgui_draw.cpp
	${IMAGUI_PATH}/imgui_tables.cpp
	${IMAGUI_PATH}/imgui_widgets.cpp
	${IMAGUI_PATH}/imgui_internal.h
	)
endif()
file(GLOB_RECURSE SRC_FILE ${SRC_PATH}/*.c ${SRC_PATH}/*.cc ${SRC_PATH}/*.h ${SRC_PATH}/*.cpp ${SRC_PATH}/*.hpp)

function(assign_source_group)
    foreach(_source IN ITEMS ${ARGN})
        if (IS_ABSOLUTE "${_source}")
            file(RELATIVE_PATH _source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${_source}")
        else()
            set(_source_rel "${_source}")
        endif()
        get_filename_component(_source_path "${_source_rel}" PATH)
        string(REPLACE "/" "\\" _source_path_msvc "${_source_path}")
        source_group("${_source_path_msvc}" FILES "${_source}")
    endforeach()
endfunction(assign_source_group)
 
function(my_add_library)
    foreach(_source IN ITEMS ${ARGN})
        assign_source_group(${_source})
    endforeach()
    add_library(${ARGV})
endfunction(my_add_library)

function(my_add_executable)
    foreach(_source IN ITEMS ${ARGN})
        assign_source_group(${_source})
    endforeach()
    add_executable(${ARGV})
endfunction(my_add_executable)

set(PROJECT_LIBS)
set(PROJECT_SRC_FILES)
macro(add_src_file)
    foreach(_source IN ITEMS ${ARGN})
        set(PROJECT_SRC_FILES ${PROJECT_SRC_FILES} ${_source})
    endforeach()
endmacro(mymacro)

macro(add_lib_file)
foreach(_source IN ITEMS ${ARGN})
        message("${_source}")
        set(PROJECT_LIBS ${PROJECT_LIBS} ${_source})
    endforeach()
endmacro()

add_src_file(${IMGUI_SRC_FILS})
add_src_file(${CJSON_SRC_FILS})
add_src_file(${SRC_FILE})
if(MSVC)
add_lib_file(d3d11.lib)
add_lib_file(d3dcompiler.lib)
add_lib_file(dxgi.lib)

else()

endif()
my_add_executable(LogAnalyze ${PROJECT_SRC_FILES})
target_link_libraries(LogAnalyze ${PROJECT_LIBS})