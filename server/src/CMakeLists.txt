set(TARGET_NAME qchat_server)

file(GLOB_RECURSE QCHAT_SERVER_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
file(GLOB_RECURSE QCHAT_SERVER_HDRS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.hpp")

trace_dependency(NAME zlib INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/zlib.cmake.json")
trace_dependency(NAME zstd INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/zstd.cmake.json" CUSTOM_SEARCH_DIR "${CMAKE_PREFIX_PATH}/lib/${CMAKE_LIBRARY_ARCHITECTURE}/cmake/OpenSSL")
trace_dependency(NAME brotli INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/brotli.cmake.json")
trace_dependency(NAME OpenSSL INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/openssl.custom.json" CUSTOM_SEARCH_DIR "${CMAKE_PREFIX_PATH}/lib64/cmake/OpenSSL")
trace_library(NAME pq INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/libpq.meson.json" CUSTOM_SEARCH_DIR "${CMAKE_PREFIX_PATH}/lib/${CMAKE_LIBRARY_ARCHITECTURE}")
trace_dependency(NAME Sqlpp23 INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/sqlpp.cmake.json")
trace_dependency(NAME Boost INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/boost.cmake.json")
trace_dependency(NAME Crow INSTALL_SCRIPT "${PROJECT_SOURCE_DIR}/installers/crow.cmake.json")

add_executable(${TARGET_NAME} ${QCHAT_SERVER_SRCS} ${QCHAT_SERVER_HDRS})
target_link_libraries(${TARGET_NAME} Crow::Crow)

target_include_directories(${TARGET_NAME} PRIVATE 
                                        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

set_cxx_project_standards(${TARGET_NAME} 20 FALSE)
append_rpath(EXTRA_PATH "${CMAKE_PREFIX_PATH}/lib/${CMAKE_LIBRARY_ARCHITECTURE}")