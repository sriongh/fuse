include(FindPackageHandleStandardArgs)

# Find sight and depdendent libraries
macro(find_rose_library var name path)
  find_library(${var} NAMES ${name} PATHS ${path})
endmacro()

# Add library as imported library
macro(add_rose_library name type location)
  add_library(${name} ${type} IMPORTED)
  set_property(TARGET ${name}
    PROPERTY IMPORTED_LOCATION
    ${location}
  )
endmacro()

find_program(Rose_EXECUTABLE NAMES rose-config)
find_package_handle_standard_args(Rose REQUIRED_VARS Rose_EXECUTABLE)

find_rose_library(Rose_LIB rose ${Rose_ROOT}/lib)

find_package_handle_standard_args(Rose
  REQUIRED_VARS
  Rose_EXECUTABLE
  Rose_LIB
  HANDLE_COMPONENTS
)


if(Rose_FOUND)
  mark_as_advanced(Rose_EXECUTABLE)
  mark_as_advanced(Rose_LIB)
endif()

if(Rose_FOUND AND NOT TARGET Rose::Rose)
  add_executable(Rose IMPORTED)
  set_property(TARGET Rose PROPERTY IMPORTED_LOCATION ${Rose_EXECUTABLE})
  execute_process(COMMAND ${Rose_EXECUTABLE} cppflags    
    OUTPUT_VARIABLE RoseConfig_CXX_FLAGS OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_VARIABLE RoseConfig_CXX_FLAGS_ERROR ERROR_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE success
  )
  execute_process(COMMAND ${Rose_EXECUTABLE} ldflags
    OUTPUT_VARIABLE RoseConfig_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE
    ERROR_VARIABLE RoseConfig_LDFLAGS_ERROR ERROR_STRIP_TRAILING_WHITESPACE
    RESULT_VARIABLE success
  )
  set(Rose_CXX_FLAGS "${RoseConfig_CXX_FLAGS}")
  set(Rose_LDFLAGS "${RoseConfig_LDFLAGS}")

  add_rose_library(Rose::Rose SHARED ${Rose_LIB})
endif()
