/* This software is distributed under the GNU General Public License Version 3 */
/* Copyright (C) Aparajita Haldar */

#ifndef EBDG_CTREE_H
#define EBDG_CTREE_H

#include "cgraph.h"

class CTree : public CGraph {

  node_map<edge> emain;

public:

  CTree();
  CTree(const string& name);

  CTree(const CTree&);

  /* Overriden base class member functions */

  // Set tree data
  virtual int setval(node, int);
  virtual int setval(edge, int);

  // Generate random tree
  virtual node randomize(int, int = RAND_MAX, int = 1, int = 0);

  // Output format data
  virtual string print(const node) const;
  virtual string print(const edge) const;

  /* New member functions */

  // Return root node of tree
  node root() const;
  // Return outedge from node to local maxima
  edge edge_main(const node) const;

  // Assign edge_main to each tree node
  int markup(node);

  // Return local maxima node from given node
  node bend(const node) const;
  // Check whether given node lies along bend path of another node
  bool bend(const node, const node) const;

  // Output format data
  string printbmain(const node) const;

  // Perturb tree
  virtual node perturb(int, int = RAND_MAX, int = 0);

};

#endif // EBDG_CTREE_H

// Local variables:
// mode: c++
// End:
