set(fuse_core
  abstraction/abstract_object.C
  abstraction/abstract_object_map.C
  abstraction/abstract_object_set.C
  abstraction/concrete_values.C
  analysis/analysis.C
  analysis/analysis_tester.C
  analysis/compose.C
  analysis/composed_analysis.C
  analysis/factor_trans_system.C
  analysis/graphIterator.C
  analysis/partitions.C
  analysis/ssa.C
  analysis/ssa_nosight.C
  analysis/stx_analysis.C
  analysis/tight_composer.C
  cfgUtils/CallGraphTraverse.C
  cfgUtils/cfgUtils.C
  cfgUtils/DataflowCFG.C
  cfgUtils/VirtualCFGIterator.C
  lattice/lattice.C
  simpleAnalyses/AnalysisAstAttribute.C
  simpleAnalyses/call_context_sensitivity_analysis.C
  simpleAnalyses/const_prop_analysis.C
  simpleAnalyses/const_prop_count.C
  simpleAnalyses/dead_path_elim_analysis.C
  simpleAnalyses/defsAnalysis.C
  simpleAnalyses/dynamicMonitor.C
  simpleAnalyses/live_dead_analysis.C
  simpleAnalyses/pointsToAnalysis.C
  simpleAnalyses/printAnalysisStates.C
  simpleAnalyses/saveDotAnalysis.C
  simpleAnalyses/taintAnalysis.C
  state/nodeState.C
  fuseCommandParser.C
  compositionalTestAnalysis.C
)

if(SIGHT_DEBUG)
  set(fuse_sight_widget sight/widgets/ats_graph_structure.C)
endif()

add_executable(fuse
  ${fuse_core}
  ${fuse_sight_widget}
)

target_compile_definitions(fuse
  PUBLIC
  -DFUSE_START_FROM_MAIN -DFUSE_SKIP_LIB_GLOBAL_DECLS
)  


target_include_directories(fuse
  PUBLIC
  abstraction/
  analysis/
  cfgUtils/
  lattice/
  simpleAnalyses/
  state/
)

set_target_properties(fuse
  PROPERTIES
  COMPILE_FLAGS ${Rose_CXX_FLAGS}
  LINK_FLAGS ${Rose_LDFLAGS}
)

if(SIGHT_DEBUG)
  target_include_directories(fuse
    PUBLIC
    sight/widgets/
    ${SIGHT_INCLUDE_DIR}
    ${SIGHT_PAPI_INCLUDE_DIR}
    ${SIGHT_WIDGETS_DIR}
  )
else()
  target_include_directories(fuse
    PUBLIC
    sight/
  )
endif()

if(SIGHT_DEBUG)
  target_link_libraries(fuse
    Sight::SightStructure
    Sight::SightCommon
  )

  set(fuse_sight_layout sight/widgets/ats_graph_layout.C)
  add_executable(fuseLayout ${fuse_sight_layout})
  target_include_directories(fuseLayout
    PUBLIC
    sight/widgets/
    ${SIGHT_INCLUDE_DIR}
    ${SIGHT_PAPI_INCLUDE_DIR}
    ${SIGHT_WIDGETS_DIR}
  )
  set_target_properties(fuseLayout
    PROPERTIES
    COMPILE_FLAGS ${Rose_CXX_FLAGS}
    LINK_FLAGS ${Rose_LDFLAGS}
  )
  target_link_libraries(fuseLayout
    Sight::SightLayout
  )
  target_compile_definitions(fuse
    PUBLIC
    FUSE_LAYOUT="${CMAKE_CURRENT_BINARY_DIR}/fuseLayout"
  )
endif()
