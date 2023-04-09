include(FindPackageHandleStandardArgs)

find_program(Rose_EXECUTABLE NAMES rose-config)
find_package_handle_standard_args(Rose REQUIRED_VARS Rose_EXECUTABLE)

if(Rose_FOUND)
  mark_as_advanced(Rose_EXECUTABLE)
endif()

if(Rose_FOUND)
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
endif()
