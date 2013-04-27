#
# cmake file for optical flow
#

project(CEE_FLOW)

cmake_minimum_required(VERSION 2.8)

add_definitions(-Wall -pthread -g)

set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/src)

enable_testing()

add_subdirectory(src)