cmake_minimum_required(VERSION 3.0.0)
project(nsp5-lab VERSION 0.1.0)

# include(CTest)
# enable_testing()

include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

set(SRC_1C
    src/p1/client.c
)
add_executable(p1C ${SRC_1C})


set(SRC_1S
    src/p1/server.c
)
add_executable(p1S ${SRC_1S})



# Program 6 - echo client
set(SRC_6C
    src/p6/client.c
)
add_executable(p6C ${SRC_6C})


# Program 6 - echo server concurrent 
set(SRC_6IS
    src/p6/iterserver.c
)
add_executable(p6IS ${SRC_6IS})

set(SRC_6CS
    src/p6/concserver.c
)
add_executable(p6CS ${SRC_6CS})

set(SRC_6CU
    src/p6/uclient.c
)
add_executable(p6CU ${SRC_6CU})

set(SRC_6SU
    src/p6/userver.c
)
add_executable(p6SU ${SRC_6SU})


set(SRC_5C
    src/p5/client.c
)
add_executable(p5C ${SRC_5C})

set(SRC_5S
    src/p5/server.c
)
add_executable(p5S ${SRC_5S})

add_executable(p7 src/p7/bford.c)

add_executable(p3 src/p3/checksum.c)
# set(SRC_1S
#     src/p1/server.c
# )
# add_executable(p1S ${SRC_1S})




# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
