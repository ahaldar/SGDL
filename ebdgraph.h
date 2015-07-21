/* This software is distributed under the GNU General Public License Version 3 */
/* Copyright (C) Aparajita Haldar */

#ifndef EBDG_EBDGRAPH_H
#define EBDG_EBDGRAPH_H

#include "cgraph.h"
#include "ctree.h"

class EBDGraph : public CGraph {

  node_map<node> start;
  node_map<node> end;
  node_map<int> nlevel;

  /* New private member functions */

  // Set EBDG data
  virtual int setlevel(node, int);
  virtual int setweight(node, int);

  // Build EBDG nodes
  void build(CTree&, node);
  // Assign level data to EBDG nodes
  void markup(CTree&);

public:

  EBDGraph(const string& = "Unnamed");

  /* Overriden base class member functions */

  virtual node new_node(node, node, int = 0);

  // Save to Graphviz format file
  string dot(const string& = "") const;
  string dot(const node) const;
  string dot(const edge) const;

  virtual void dotf(ofstream&, const bool) const;
  virtual void dotf(const string&) const;

  // Outputformat data
  virtual string print(const node) const;
  virtual string print(const edge) const;

  /* New member functions */

  // Retrieve and set EBDG data
  node startnode(const node) const;
  node endnode(const node) const;

  int level(const node) const;
  int weight(const node) const;

  // Build EBDG from contour tree
  void build(CTree&);

};

#endif // EBDG_EBDGRAPH_H

// Local variables:
// mode: c++
// End:
