include(FindPackageHandleStandardArgs)

# Find sight and depdendent libraries
macro(find_sight_library var name path)
  find_library(${var} NAMES ${name} PATHS ${path})
endmacro()

# Add library as imported library
macro(add_sight_library name type location)
  add_library(${name} ${type} IMPORTED)
  set_property(TARGET ${name}
    PROPERTY IMPORTED_LOCATION
    ${location}
  )
endmacro()

# Find include paths
macro(find_sight_path var name path)
  find_path(${var} NAMES ${name} PATHS ${path})
endmacro()

set(SIGHT_ROOT ${CMAKE_SOURCE_DIR}/externals/sight)
set(SIGHT_WIDGETS_DIR ${SIGHT_ROOT}/widgets)
set(SIGHT_WIDGETS_PAPI_DIR ${SIGHT_WIDGETS_DIR}/papi)
set(SIGHT_WIDGETS_GSL_DIR ${SIGHT_WIDGETS_DIR}/gsl)
set(SIGHT_TAFFYDB_DIR ${SIGHT_ROOT}/script/taffydb)

find_sight_library(SIGHT_STRUCTURE sight_structure ${SIGHT_ROOT})
find_sight_library(SIGHT_LAYOUT sight_layout ${SIGHT_ROOT})
find_sight_library(SIGHT_COMMON sight_common ${SIGHT_ROOT})
find_sight_library(SIGHT_PAPI papi ${SIGHT_WIDGETS_PAPI_DIR}/lib)
find_sight_library(SIGHT_PFM pfm ${SIGHT_WIDGETS_PAPI_DIR}/lib)
find_sight_library(SIGHT_GSL gsl ${SIGHT_WIDGETS_GSL_DIR}/lib)
find_sight_library(SIGHT_GSL_CBLAS gslcblas ${SIGHT_WIDGETS_GSL_DIR}/lib)

find_path(SIGHT_INCLUDE_DIR sight.h ${SIGHT_ROOT})
find_path(SIGHT_PAPI_INCLUDE_DIR  papi.h ${SIGHT_WIDGETS_PAPI_DIR}/include)

find_package_handle_standard_args(Sight
  REQUIRED_VARS
  SIGHT_INCLUDE_DIR
  SIGHT_LAYOUT
  SIGHT_STRUCTURE
  SIGHT_COMMON
  SIGHT_PAPI
  SIGHT_PAPI_INCLUDE_DIR
  SIGHT_PFM
  SIGHT_GSL
  SIGHT_GSL_CBLAS
  HANDLE_COMPONENTS
)

if(Sight_FOUND)
  mark_as_advanced(SIGHT_INCLUDE_DIR)
  mark_as_advanced(SIGHT_LAYOUT)
  mark_as_advanced(SIGHT_STRUCTURE)
  mark_as_advanced(SIGHT_COMMON)
  mark_as_advanced(SIGHT_PAPI)
  mark_as_advanced(SIGHT_PFM)
  mark_as_advanced(SIGHT_GSL)
  mark_as_advanced(SIGHT_CSL_CBLAS)
endif()

if(Sight_FOUND AND NOT TARGET Sight::Sight)
  add_sight_library(Sight::SightLayout SHARED ${SIGHT_LAYOUT})
  add_sight_library(Sight::SightStructure SHARED ${SIGHT_STRUCTURE})
  add_sight_library(Sight::SightCommon STATIC ${SIGHT_COMMON})
  add_sight_library(Sight::Papi SHARED ${SIGHT_PAPI})
  add_sight_library(Sight::Pfm SHARED  ${SIGHT_PFM})
  add_sight_library(Sight::Gsl SHARED ${SIGHT_GSL})
  add_sight_library(Sight::GslCblas SHARED ${SIGHT_GSL_CBLAS})
  target_link_libraries(Sight::SightStructure INTERFACE Sight::Papi)
  target_link_libraries(Sight::SightStructure INTERFACE Sight::Pfm)
  target_link_libraries(Sight::SightLayout INTERFACE Sight::Gsl)
  target_link_libraries(Sight::SightLayout INTERFACE Sight::GslCblas)
  execute_process(COMMAND chmod -R  +rwx ${SIGHT_TAFFYDB_DIR} RESULT_VARIABLE success)
endif()
