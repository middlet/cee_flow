#
# cmake for src directory of crowded_world
#

find_package( OpenCV REQUIRED )

include_directories(. ${COMMON_INCLUDES})

# include opencv
add_executable(cflow main.cpp)
target_link_libraries(cflow ${OpenCV_LIBS})