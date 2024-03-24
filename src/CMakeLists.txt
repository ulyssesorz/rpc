aux_source_directory(. SRC_LIST)

add_library(rpc ${SRC_LIST})

target_link_libraries(rpc pthread netlib zookeeper_mt)