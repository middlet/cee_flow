#
# cmake for src directory of crowded_world
#


find_package( OpenCV REQUIRED )
#set( BOOST_LIBRARYDIR "/usr/lib" )
#set(Boost_USE_STATIC_LIBS OFF)
#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
find_package( Boost REQUIRED COMPONENTS filesystem system)

include_directories(. ${COMMON_INCLUDES})

# include opencv
add_executable(cflow main.cpp)
target_link_libraries(cflow ${OpenCV_LIBS} ${Boost_LIBRARIES})