set(fuse_sources
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

add_executable(fuse
  ${fuse_sources}
)

target_include_directories(fuse
  PUBLIC
  abstraction/
  analysis/
  cfgUtils/
  lattice/
  sight/
  simpleAnalyses/
  state/
)

set_target_properties(fuse
  PROPERTIES
  COMPILE_FLAGS ${Rose_CXX_FLAGS}
  LINK_FLAGS ${Rose_LDFLAGS}
)
