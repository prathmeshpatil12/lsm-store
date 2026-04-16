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
    src/bloom/bloom.cpp
)

# bloom filter test
add_executable(bloom_test
    src/bloom/bloom.cpp
    src/bloom/bloom_main.cpp
)

add_executable(db_test
    src/memtable/skiplist.cpp
    src/memtable/memtable.cpp
    src/wal/wal.cpp
    src/sstable/sstable.cpp
    src/bloom/bloom.cpp
    src/compaction/compaction.cpp
    src/db/db.cpp
    src/db/db_main.cpp
)

target_include_directories(db_test PRIVATE
    src/memtable
    src/wal
    src/sstable
    src/bloom
    src/compaction
    src/db
)
