cmake_minimum_required(VERSION 3.10)
project(lsm-store)

set(CMAKE_CXX_STANDARD 17)

# all source files
add_executable(lsm-store
    src/memtable/skiplist.cpp
    src/memtable/memtable.cpp
    src/wal/wal.cpp
    src/sstable/sstable.cpp
    src/sstable/sstable_main.cpp
)

# include directories so headers can be found
target_include_directories(lsm-store PRIVATE
    src/memtable
    src/wal
    src/sstable
)