cmake_minimum_required(VERSION 3.17)
set(CMAKE_CXX_STANDARD 17)

project(thallium_communication_test)

#set(CMAKE_FIND_DEBUG_MODE TRUE)

find_package(mercury REQUIRED)
find_package(thallium REQUIRED)
find_package(Threads REQUIRED)

#set(CMAKE_FIND_DEBUG_MODE FALSE)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Compiling communication test in Debug Mode")
#    add_compile_options(-g3)
    add_compile_options(-O0)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")
endif()

add_executable(thallium_server thallium_server.cpp)
target_include_directories(thallium_server PRIVATE ../../ChronoAPI/ChronoLog/include)
target_link_libraries(thallium_server PRIVATE thallium)
target_link_libraries(thallium_server PUBLIC "-pthread")
add_test(NAME CommThalliumServer COMMAND thallium_server)

add_executable(thallium_client thallium_client.cpp)
target_include_directories(thallium_client PRIVATE)
target_link_libraries(thallium_client thallium)
add_test(NAME CommThalliumClient COMMAND thallium_client)

find_package(MPI)

add_executable(thallium_client_mpi thallium_client_mpi.cpp)
include_directories(SYSTEM ${MPI_INCLUDE_PATH})
target_include_directories(thallium_client_mpi PRIVATE ../../ChronoAPI/ChronoLog/include)
target_link_libraries(thallium_client_mpi thallium ${MPI_C_LIBRARIES})
add_test(NAME CommThalliumClientMPI COMMAND thallium_client_mpi)

add_executable(rpc_server rpc_server.cpp
        ../../ChronoAPI/ChronoLog/include/ChronicleMetadataRPCProxy.h
        ../../ChronoAPI/ChronoLog/include/macro.h
        ../../ChronoAPI/ChronoLog/include/rpc.h
        ../../ChronoAPI/ChronoLog/include/RPCFactory.h
        ../../ChronoVisor/src/ChronicleMetaDirectory.cpp
        ../../ChronoVisor/include/Chronicle.h
        ../../ChronoVisor/include/Story.h
        ../../ChronoVisor/include/Event.h
        ../../ChronoVisor/src/city.cpp
        ../../ChronoVisor/include/city.h
        ../../tools/Serde/src/SerDe.cpp)
target_include_directories(rpc_server PRIVATE
        ../../ChronoAPI/ChronoLog/include
        ../../tools/Serde/include
        ../../ChronoVisor/include)
target_link_libraries(rpc_server thallium)
add_test(NAME CommRPCServer COMMAND rpc_server)

add_executable(rpc_client rpc_client.cpp
        ../../ChronoAPI/ChronoLog/include/ChronicleMetadataRPCProxy.h
        ../../ChronoAPI/ChronoLog/include/macro.h
        ../../ChronoAPI/ChronoLog/include/rpc.h
        ../../ChronoAPI/ChronoLog/include/RPCFactory.h
        ../../ChronoVisor/src/ChronicleMetaDirectory.cpp
        ../../ChronoVisor/include/Chronicle.h
        ../../ChronoVisor/include/Story.h
        ../../ChronoVisor/include/Event.h
        ../../ChronoVisor/src/city.cpp
        ../../ChronoVisor/include/city.h
        ../../tools/Serde/src/SerDe.cpp)
target_include_directories(rpc_client PRIVATE
        ../../ChronoAPI/ChronoLog/include
        ../../tools/Serde/include
        ../../ChronoVisor/include)
target_link_libraries(rpc_client thallium)
add_test(NAME CommRPCClient COMMAND rpc_client)
