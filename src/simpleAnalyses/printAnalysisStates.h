#ifndef PRINT_ANALYSIS_STATES_H
#define PRINT_ANALYSIS_STATES_H

#include "CallGraphTraverse.h"
#include "VirtualCFGIterator.h"
#include "analysis.h"
#include "cfgUtils.h"
#include "lattice.h"
#include "latticeFull.h"
#include "partitions.h"

#include <string>
#include <vector>

/* GB - 2013-05-10 - Temporarily removing printAnalysisStates until we develop a
good procedure for iterating the Abstraction graph in an easy-to-read order
namespace fuse {
class ComposedAnalysis;

class printAnalysisStates : public UnstructuredPassAnalysis
{
  public:
  std::vector<int> latticeNames;
  std::vector<int> factNames;
  typedef enum {above=0, below=1} ab;
  ab latSide; // Records whether we should print lattices above or below each
node.

  printAnalysisStates(ComposedAnalysis* creator, std::vector<int>& factNames,
std::vector<int>& latticeNames, ab latSide);

  void visit(const Function& func, PartPtr p, NodeState& state);
}
}; // namespace fuse
*/
#endif
