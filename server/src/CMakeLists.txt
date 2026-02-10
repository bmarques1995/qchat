set(TARGET_NAME qchat_server)

file(GLOB_RECURSE QCHAT_SERVER_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "server/*.cpp")
file(GLOB_RECURSE QCHAT_SERVER_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "server/*.hpp")

trace_dependency(NAME zlib INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/zlib.cmake.json")
trace_dependency(NAME zstd INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/zstd.cmake.json")
trace_dependency(NAME brotli INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/brotli.cmake.json")
trace_dependency(NAME OpenSSL INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/openssl.custom.json" CUSTOM_SEARCH_DIR "${CMAKE_PREFIX_PATH}/lib64/cmake/OpenSSL")
trace_library(NAME pq INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/libpq.meson.json" CUSTOM_SEARCH_DIR "${CMAKE_PREFIX_PATH}/lib64")
trace_dependency(NAME Sqlpp23 INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/sqlpp.cmake.json")
trace_dependency(NAME Boost INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/boost.cmake.json")
trace_dependency(NAME Crow INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/crow.cmake.json")
trace_dependency(NAME jsoncpp INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/jsoncpp.cmake.json")

include(CMakeFindDependencyMacro)
set(PostgreSQL_LIBRARY ${CMAKE_PREFIX_PATH}/lib64/libpq.so)
find_dependency(PostgreSQL)

add_library(${TARGET_NAME} SHARED ${QCHAT_SERVER_SRCS} ${QCHAT_SERVER_HDRS})
target_link_libraries(${TARGET_NAME} Crow::Crow sqlpp23::sqlpp23 sqlpp23::postgresql jsoncpp_lib)

target_include_directories(${TARGET_NAME} PUBLIC 
                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server>
                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server/entities>
                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server/views>
                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/server/core>)

set_cxx_project_standards(${TARGET_NAME} 23 FALSE)

set(TARGET_2 qchat_server_exec)

file(GLOB_RECURSE QCHAT_SERVER_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "qchat_server/*.cpp")
file(GLOB_RECURSE QCHAT_SERVER_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "qchat_server/*.hpp")

add_executable(${TARGET_2} ${QCHAT_SERVER_SRCS} ${QCHAT_SERVER_SRCS})
target_link_libraries(${TARGET_2} PUBLIC ${TARGET_NAME})

target_include_directories(${TARGET_2} PRIVATE 
                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/qchat_server>)

set_cxx_project_standards(${TARGET_2} 23 FALSE)
append_rpath(EXTRA_PATH "${CMAKE_PREFIX_PATH}/lib/${CMAKE_LIBRARY_ARCHITECTURE}")