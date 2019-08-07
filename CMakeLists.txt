cmake_minimum_required(VERSION 3.6)
project(sielo-ui)

###################
### some Define ###
###################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

include_directories(${CMAKE_SOURCE_DIR}/src)

###############################
### user config config file ###
###############################

include("${CMAKE_SOURCE_DIR}\\user-config.cmake")

#####################
### include files ###
#####################

file(
    GLOB_RECURSE
    SOURCE_FILES
    src/*.hpp
    src/*.cpp
)

##################
### create exe ###
##################

if (WIN32)
    add_executable(sielo-ui WIN32 ${SOURCE_FILES} ic_sielo.rc)
else()
    add_executable(sielo-ui ${SOURCE_FILES})
endif()

################
### add libs ###
################

find_package(Qt5 5.13.0 REQUIRED COMPONENTS Widgets)
set (SIELO_LIBS ${SIELO_LIBS} Qt5::Widgets)
target_link_libraries(sielo-ui ${SIELO_LIBS})

#######################
### use windeployqt ###
#######################

if (WIN32)
    # deploy
    get_target_property(QT5_QMAKE_EXECUTABLE Qt5::qmake IMPORTED_LOCATION)
    get_filename_component(QT5_WINDEPLOYQT_EXECUTABLE ${QT5_QMAKE_EXECUTABLE} PATH)
    set(QT5_WINDEPLOYQT_EXECUTABLE "${QT5_WINDEPLOYQT_EXECUTABLE}/windeployqt.exe")

    add_custom_command(TARGET sielo-ui POST_BUILD COMMAND ${QT5_WINDEPLOYQT_EXECUTABLE} --qmldir ${CMAKE_SOURCE_DIR} $<TARGET_FILE_DIR:sielo-ui>)
endif()

####################################
### add filter for Visual Studio ###
####################################

foreach(_source IN ITEMS ${SOURCE_FILES})
	get_filename_component(_source_path "${_source}" PATH)
	file(RELATIVE_PATH _source_path_rel "${CMAKE_SOURCE_DIR}/src" "${_source_path}")
	string(REPLACE "/" "\\" _group_path "${_source_path_rel}")
	source_group("${_group_path}" FILES "${_source}")
endforeach()
