# cmake最低版本
cmake_minimum_required(VERSION 3.23)

# 項目名
project(iterator_example)

# 啟用IDE目錄功能
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(source_dir ${CMAKE_CURRENT_SOURCE_DIR})
set(platform ${CMAKE_GENERATOR_PLATFORM})

# 輸出目錄
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${source_dir}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${source_dir}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${source_dir}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${source_dir}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE ${source_dir}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG ${source_dir}/lib)

set(CMAKE_DEBUG_POSTFIX "d") # 調試庫加d後綴
set(platform ${CMAKE_GENERATOR_PLATFORM})

# 32位添加32或32d後綴
if(${platform} STREQUAL "Win32")
  set(CMAKE_DEBUG_POSTFIX "32d")
  set(CMAKE_RELEASE_POSTFIX "32")
endif()

# 包含模塊
include(CMakePrintHelpers) # cmake_print_variables

# 設置全局編譯選項
# add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;/std:c17;/experimental:module;>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/W4;/MP;/Zc:__cplusplus;/experimental:module;>")

find_package(doctest REQUIRED)

set(iterator iterator)
add_executable(${iterator})
target_sources(${iterator} PRIVATE
  src/iterator.cpp
  include/LegacyInputIterator.hpp
  include/LegacyIterator.hpp
  include/LegacyOutputIterator.hpp
  include/LegacyForwardIterator.hpp
  include/LegacyBidirectionalIterator.hpp
  include/LegacyRandomAccessIterator.hpp
  include/common.hpp
)
target_include_directories(${iterator} PRIVATE include)
target_link_libraries(${iterator} PUBLIC doctest::doctest)
target_compile_features(${iterator} PRIVATE cxx_std_20)
if(CMAKE_DEBUG_POSTFIX)
  set_target_properties(${iterator} PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
endif()
if(CMAKE_RELEASE_POSTFIX)
  set_target_properties(${iterator} PROPERTIES RELEASE_POSTFIX ${CMAKE_RELEASE_POSTFIX})
endif()
