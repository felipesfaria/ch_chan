# Created by the script cgal_create_cmake_script
# This is the CMake script for compiling a CGAL application.


project( ch_chan_ )

cmake_minimum_required(VERSION 2.6.2)
if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}" VERSION_GREATER 2.6)
  if("${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}.${CMAKE_PATCH_VERSION}" VERSION_GREATER 2.8.3)
    cmake_policy(VERSION 2.8.4)
  else()
    cmake_policy(VERSION 2.6)
  endif()
endif()

find_package(CGAL QUIET COMPONENTS Core )

if ( CGAL_FOUND )
  include( ${CGAL_USE_FILE} )

  include( CGAL_CreateSingleSourceCGALProgram )

    include_directories (BEFORE "include")

  include_directories(PointsGenerator)
  add_subdirectory(PointsGenerator)
  include_directories(PointsGenerator_Tests)
  add_subdirectory(PointsGenerator_Tests)
  include_directories(Utils)
  add_subdirectory(Utils)
  include_directories(Utils_Tests)
  add_subdirectory(Utils_Tests)
  include_directories(ch_chan)
  add_subdirectory(ch_chan)
  include_directories(ch_chan_Tests)
  add_subdirectory(ch_chan_Tests)
  create_single_source_cgal_program("main.cpp")
  create_single_source_cgal_program( "ch_from_cin_to_cout.cpp" )
  create_single_source_cgal_program( "ch_graham_anderson.cpp" )
  create_single_source_cgal_program( "ch_timing.cpp" )
  create_single_source_cgal_program( "convex_hull_yz.cpp" )
  create_single_source_cgal_program( "iostream_convex_hull_2.cpp" )
  create_single_source_cgal_program( "vector_convex_hull_2.cpp" )

  add_executable(runMain main.cpp ch_chan/SDL.cpp ch_chan/SDL.h)
  target_link_libraries(runMain ch_chan)
  target_link_libraries(runMain Utils)
  target_link_libraries(runMain SDL2 SDL2_gfx )

else()
  
    message(STATUS "This program requires the CGAL library, and will not be compiled.")
  
endif()

