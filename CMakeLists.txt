cmake_minimum_required(VERSION 3.0.0)
project(nsp5-lab VERSION 0.1.0)

# include(CTest)
# enable_testing()

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# client server
add_executable(p1C src/p1/client.c)
add_executable(p1S src/p1/server.c)

# Program 6 - echo client
add_executable(p6C src/p6/client.c)


# Program 6 - echo server concurrent 
add_executable(p6IS src/p6/iterserver.c)

add_executable(p6CS src/p6/concserver.c)

add_executable(p6CU src/p6/uclient.c)

add_executable(p6SU src/p6/userver.c)


add_executable(p5C src/p5/client.c)

add_executable(p5S src/p5/server.c)

# bford
add_executable(p2 src/p2/bford.c)
add_executable(p2b src/p2/bellmanford.c)

# checksum
add_executable(p3a src/p3/checksum.c)

add_executable(p3b src/p3/hamming.c)


add_executable(p4l src/p4/listener.c)
add_executable(p4s src/p4/sender.c)


add_executable(p8dh src/p8/dh.c)
# add_executable(p4s src/p4/sender.c)


