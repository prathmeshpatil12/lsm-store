cmake_minimum_required(VERSION 3.10)
project(lsm-store)

set(CMAKE_CXX_STANDARD 17)

# include directories for all targets
include_directories(
    src/memtable
    src/wal
    src/sstable
    src/bloom
)

# sstable test
add_executable(sstable_test
    src/memtable/skiplist.cpp
    src/wal/wal.cpp
    src/memtable/memtable.cpp
    src/sstable/sstable.cpp
    src/sstable/sstable_main.cpp
)

# bloom filter test
add_executable(bloom_test
    src/bloom/bloom.cpp
    src/bloom/bloom_main.cpp
)