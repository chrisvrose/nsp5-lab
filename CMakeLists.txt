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



# set(CPACK_PROJECT_NAME ${PROJECT_NAME})
# set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
# include(CPack)
