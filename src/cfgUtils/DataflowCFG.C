#include "sage3basic.h"
#include "DataflowCFG.h"
#include "cfgUtils.h"
#include <cassert>
using namespace std;
#include "sight.h"

#define SgNULL_FILE Sg_File_Info::generateDefaultFileInfoForTransformationNode()

namespace fuse {
// the default interesting filter
bool defaultFilter(CFGNode cfgn) {
  //    scope s(txt()<<"defaultFilter("<<CFGNode2Str(cfgn)<<")");
  SgNode *node = cfgn.getNode();
  assert(node != NULL);
  // Keep the last index for initialized names. This way the definition of the
  // variable doesn't propagate to its assign initializer.
  //  if (isSgInitializedName(node))
  //  {
  //    return (cfgn == node->cfgForEnd());
  //  }
  //  else
  //    return (cfgn.isInteresting());
  switch (node->variantT()) {
  // Keep the last index for initialized names. This way the definition of the
  // variable doesn't propagate to its assign initializer.
  case V_SgInitializedName:
    //        dbg << "(cfgn == node->cfgForEnd()) = "<<((cfgn ==
    //        node->cfgForEnd()))<<endl;
    return (cfgn == node->cfgForEnd());

  // filter out this node type
  // abstract memory object cannot be created for these nodes
  case V_SgExprListExp:
    //      case V_SgNullStatement:
  case V_SgExprStatement:
  case V_SgFunctionRefExp:
    //        dbg << "false"<<endl;
    return false;

  case V_SgFunctionCallExp:
    //        dbg << "cfgn.getIndex()="<<cfgn.getIndex()<<endl;
    return cfgn.getIndex() == 2 || cfgn.getIndex() == 3;

  case V_SgFunctionParameterList:
    //        dbg << "false"<<endl;
    // return true;
    return cfgn.getIndex() ==
           isSgFunctionParameterList(node)->get_args().size();
    // return cfgn.getIndex()==1;*/

  case V_SgFunctionDefinition:
    //        dbg << "cfgn.getIndex()="<<cfgn.getIndex()<<endl;
    return cfgn.getIndex() == 3;

  case V_SgReturnStmt:
    //        dbg << "cfgn.getIndex()="<<cfgn.getIndex()<<endl;
    return cfgn.getIndex() == 1;

    // Filter out intermediate dot expressions. We only care about the complete
    // ones.
    /*      case V_SgDotExp:
            //dbg <<
       "isSgDotExp(node->get_parent())="<<isSgDotExp(node->get_parent())<<endl;
            //cout << "defaultFilter() node="<<cfgUtils::SgNode2Str(node)<<"
       node->get_parent()="<<cfgUtils::SgNode2Str(node->get_parent())<<"
       interesting="<<(!isSgDotExp(node->get_parent()))<<endl; return
       !isSgDotExp(node->get_parent());*/
  /*case V_SgCastExp:
      return false;*/

  // Do not filter out SgVariableDeclarations. We need index=0 (beginning) and
  // index=1 (end) to mark the portion of the CFG devoted to
  // SgVariableDeclarations of globals
  case V_SgVariableDeclaration:
    return true;

  default:
    //        dbg << "cfgn.isInteresting()="<<cfgn.isInteresting()<<endl;
    return cfgn.isInteresting();
  }
}

/*std::string DataflowNode::str(std::string indent) const
{
  ostringstream outs;
  outs << "<" << getNode() << " | " << getNode()->class_name() << " | " <<
getNode()->unparseToString() << " | " << getIndex() << ">"; return outs.str();
}

// XXX: This code is duplicated from frontend/SageIII/virtualCFG/virtualCFG.C
// Make a set of raw CFG edges closure. Raw edges may have src and dest CFG
nodes which are to be filtered out.
// The method used is to connect them into CFG paths so src and dest nodes of
each path are interesting, skipping intermediate filtered nodes)
vector<DataflowEdge> makeClosureDF(const vector<CFGEdge>& orig, // raw in or out
edges to be processed vector<CFGEdge> (CFGNode::*closure)() const, // find
successor edges from a node, CFGNode::outEdges() for example CFGNode
(CFGPath::*otherSide)() const, // node from the other side of the path:
CFGPath::target() CFGPath (*merge)(const CFGPath&, const CFGPath&),  // merge
two paths into one bool (*filter) (CFGNode))   // filter function
{
  // a filter function here
  // A set of CFG paths, each of them is made from a raw CFG edge initially
  vector<CFGPath> currentPaths(orig.begin(), orig.end());
  // cerr << "makeClosure starting with " << orig.size() << endl;
  while (true) {
top:
    for (size_t i = 0; i < currentPaths.size(); ++i) { // check each of the
current paths
      // if a path has a node from the other side which is not interesting, do
the path merge if (!filter((currentPaths[i].*otherSide)())) { unsigned int
oldSize = currentPaths.size(); // the number of unique paths before merge
        //get all other successor edges from the non-interesting dest node
        vector<CFGEdge> currentPaths2 =
((currentPaths[i].*otherSide)().*closure)();

        // merge the successor edges one by one
        for (unsigned int j = 0; j < currentPaths2.size(); ++j) {
          dbg << "makeClosureDF: i="<<i<<" =&gt; j="<<j<<":
"<<CFGEdge2Str(currentPaths2[j])<<endl; dbg <<
"isSgAndOp(currentPaths2[j].source().getNode())="<<isSgAndOp(currentPaths2[j].source().getNode())<<",
"<<
                 "isSgAndOp(currentPaths2[j].target().getNode())="<<isSgAndOp(currentPaths2[j].target().getNode())<<",
"<<
                 "isSgOrOp(currentPaths2[j].source().getNode())="<<isSgOrOp(currentPaths2[j].source().getNode())<<",
"<<
                 "isSgOrOp(currentPaths2[j].target().getNode())="<<isSgOrOp(currentPaths2[j].target().getNode())<<",
"<<
                 "currentPaths2[j].source().getIndex()="<<currentPaths2[j].source().getIndex()<<",
"<<
                 "currentPaths2[j].target().getIndex()="<<currentPaths2[j].target().getIndex()<<endl;
          // Skip edges from the start of a short-circuit operation (|| and &&)
to its end if(((isSgAndOp(currentPaths2[j].source().getNode()) &&
isSgAndOp(currentPaths2[j].target().getNode())) ||
              (isSgOrOp(currentPaths2[j].source().getNode())  &&
isSgOrOp(currentPaths2[j].target().getNode()))) &&
             currentPaths2[j].source().getIndex()==1 &&
currentPaths2[j].target().getIndex()==2) { continue; }

          CFGPath merged = (*merge)(currentPaths[i], currentPaths2[j]);
          if (std::find(currentPaths.begin(), currentPaths.end(), merged) ==
currentPaths.end()) { // find a new path? push it to the working set of initial
edges currentPaths.push_back(merged); // a new path will be inserted. Old path
ending with non-interesting node still exists
          }
        }
        if (currentPaths.size() != oldSize)
          goto top; // TODO go through all paths again? not very efficient!!
      }
    }
    break; // If the iteration got all of the way through: all dest nodes of all
paths are interesting or no new merges are made.
  }
  // cerr << "makeClosure loop done: " << currentPaths.size() << endl;

  // Now convert the set of CFG paths with interesting src and dest nodes into a
set of DataflowEdge vector<DataflowEdge> edges; for
(vector<CFGPath>::const_iterator i = currentPaths.begin(); i !=
currentPaths.end(); ++i) {
    // Only if the end node of the path is interesting
    //if (((*i).*otherSide)().isInteresting())
    if (filter(((*i).*otherSide)()))
      edges.push_back(DataflowEdge(*i, filter));
  }
  //cout << "makeClosure done: #edges=" << edges.size() << endl;
  //for(vector<DataflowEdge>::iterator e=edges.begin(); e!=edges.end(); e++)
  //    printf("Current Node %p<%s | %s>\n", e.target().getNode(),
e.target().getNode()->unparseToString().c_str(),
e.target().getNode()->class_name().c_str()); for
(vector<DataflowEdge>::const_iterator i = edges.begin(); i != edges.end(); ++i)
{ CFGNode end1 = (*i).source().n; CFGNode end2 = (*i).target().n; assert (filter
(end1)  || filter (end2)); // at least one node is interesting
  }
  return edges;
}

vector<DataflowEdge> DataflowNode::outEdges() const {
  return makeClosureDF(n.outEdges(), &CFGNode::outEdges, &CFGPath::target,
&mergePaths, filter);
}

vector<DataflowEdge> DataflowNode::inEdges() const {
  return makeClosureDF(n.inEdges(), &CFGNode::inEdges, &CFGPath::source,
&mergePathsReversed, filter);
}

bool DataflowNode::isInteresting() const {
  //  return (n.getNode())->cfgIsIndexInteresting(n.getIndex());
  //return isDataflowInteresting(n);
  return filter(n);
}

bool isDataflowInteresting(CFGNode cn) {
  assert (cn.getNode());
  return (cn.getNode()->cfgIsIndexInteresting(cn.getIndex()) &&
         //!isSgFunctionRefExp(cn.getNode()) &&
         !isSgExprListExp(cn.getNode()) &&
         !isSgForInitStatement(cn.getNode()) &&
         //!isSgVarRefExp(cn.getNode()) &&
         //!isSgValueExp(cn.getNode()) &&
         //!isSgExprStatement(cn.getNode()) &&
         !(isSgInitializedName(cn.getNode()) && cn.getIndex()==0))
         ||
         (isSgIfStmt(cn.getNode()) &&
          (cn.getIndex()==1 || cn.getIndex()==2));
}*/

} // namespace fuse
