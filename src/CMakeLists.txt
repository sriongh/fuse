add_executable(fuse
  identityTranslator.C
)

set_target_properties(fuse
  PROPERTIES
  COMPILE_FLAGS ${Rose_CXX_FLAGS}
  LINK_FLAGS ${Rose_LDFLAGS}
)

  
