cmake_minimum_required(VERSION 3.5)
project(qvmmi)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/")
include(QVmmiHelpers)

find_package(QV REQUIRED)
find_package(MPI REQUIRED)

if(MPI_FOUND AND NOT TARGET MPI::MPI_CXX)
  message(STATUS "Addin custom MPI library ${MPI_CXX_INCLUDE_PATH}")
  add_library(MPI::MPI_C UNKNOWN IMPORTED)
  set_target_properties(MPI::MPI_C PROPERTIES
    IMPORTED_LOCATION             "${MPI_C_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${MPI_C_INCLUDE_DIRS};${MPI_C_INCLUDE_PATH}"
    INTERFACE_COMPILE_DEFINITIONS "${MPI_C_COMPILE_DEFINITIONS}"
    INTERFACE_COMPILE_OPTIONS     "${MPI_C_COMPILE_OPTIONS};${MPI_C_COMPILE_FLAGS}"
    INTERFACE_LINK_OPTIONS        "${MPI_C_LINK_FLAGS}"
  )
  list(REMOVE_ITEM MPI_CXX_LIBRARIES ${MPI_C_LIBRARIES})
  add_library(MPI::MPI_CXX UNKNOWN IMPORTED)
  set_target_properties(MPI::MPI_CXX PROPERTIES
    IMPORTED_LOCATION             "${MPI_CXX_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES "${MPI_CXX_INCLUDE_DIRS};${MPI_CXX_INCLUDE_PATH}"
    INTERFACE_COMPILE_DEFINITIONS "${MPI_CXX_COMPILE_DEFINITIONS}"
    INTERFACE_COMPILE_OPTIONS     "${MPI_CXX_COMPILE_OPTIONS};${MPI_CXX_COMPILE_FLAGS}"
    INTERFACE_LINK_OPTIONS        "${MPI_CXX_LINK_FLAGS}"
    INTERFACE_LINK_LIBRARIES      "${MPI_C_LIBRARIES}"
  )
endif()

set(_source_dir src)
set(_sources
  ${_source_dir}/class_size_slave.cc
  ${_source_dir}/codec.cc
  ${_source_dir}/fast_input_master.cc
  ${_source_dir}/fast_master.cc
  ${_source_dir}/fast_mmi_master.cc
  ${_source_dir}/fast_mmi_slave.cc
  ${_source_dir}/main.cc
  ${_source_dir}/master.cc
  ${_source_dir}/slave.cc
  ${_source_dir}/slow_check_master.cc
  ${_source_dir}/sure_finite_slave.cc
)

qv_executable(TARGET qvmmi
  SOURCES ${_sources}
  PUBLIC_LIBRARIES QV::qv  MPI::MPI_CXX
)
install(TARGETS qvmmi
  RUNTIME DESTINATION bin
)
