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

  // Overriden base class member functions

  virtual int setval(node, int);
  virtual int setval(edge, int);

  virtual node randomize(int, int = RAND_MAX, int = 1, int = 0);

  virtual string print(const node) const;
  virtual string print(const edge) const;

  // New member functions

  node root() const;
  edge edge_main(const node) const;

  int markup(node);

  node bend(const node) const;
  bool bend(const node, const node) const;

  string printbmain(const node) const;

  virtual node perturb(int, int = RAND_MAX, int = 0);

};

#endif // EBDG_CTREE_H

// Local variables:
// mode: c++
// End:
