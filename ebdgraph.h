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

  // New private member functions

  virtual int setlevel(node, int);
  virtual int setweight(node, int);

  void build(CTree&, node);
  void markup(CTree&);

public:

  EBDGraph(const string& = "Unnamed");

  // Overriden base class member functions

  virtual node new_node(node, node, int = 0);

  string dot(const string& = "") const;
  string dot(const node) const;
  string dot(const edge) const;

  virtual void dotf(ofstream&, const bool) const;
  virtual void dotf(const string&) const;

  virtual string print(const node) const;
  virtual string print(const edge) const;

  // New member functions

  node startnode(const node) const;
  node endnode(const node) const;

  int level(const node) const;
  int weight(const node) const;

  void build(CTree&);

};

#endif // EBDG_EBDGRAPH_H

// Local variables:
// mode: c++
// End:
