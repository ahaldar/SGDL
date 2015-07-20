/* This software is distributed under the GNU General Public License Version 3 */
/* Copyright (C) Aparajita Haldar */

#include "ctree.h"

CTree::CTree() : CGraph() { }

CTree::CTree(const string& name) : CGraph(name) { make_directed(); }
  
CTree::CTree(const CTree& ct) : CGraph(ct) { }

int CTree::setval(node n, int val) {
  int oval = (*this)[n];
  edge e;
  CGraph::setval(n, val);
  forall_out_edges(e, n) {
    setval(e.target(), val + (*this)[e]);
  }
  return oval;
}

int CTree::setval(edge e, int val) {
  int oval = (*this)[e];
  CGraph::setval(e, val);
  setval(e.target(), (*this)[e.source()] + val);
  return oval;
}

string CTree::print(const node n) const {
  return CGraph::print(n);
}

string CTree::print(const edge e) const {
  ostringstream ost;
  node n = e.source();
  CTree& t = (CTree&) n.container();
  if (t.emain[n] == e) ost << "--";
  ost << t[e];
  if (t.emain[n] == e) ost << "--";
  return ost.str();
}

node CTree::randomize(int nnodes, int ewmax, int ewmin, int nscalar) {
  node root, n;
  int ew, lnnodes;
  if (!nscalar) {		// at root
    if (nnodes & 1) {		// if nnodes odd, make even
      return randomize(nnodes + 1, ewmax, ewmin, nscalar);
    } else {			// nnodes even, generate tree
      ew = brand(ewmax, ewmin);
      root = new_node(nscalar);
      n = new_node(nscalar + ew);
      new_edge(root, n, ew);
      if (nnodes -= 2) {
	lnnodes = brand(nnodes);
	if (!(lnnodes & 1)) lnnodes++; // make sure subtrees have odd nnodes >= 1
	ew = brand(ewmax, ewmin);
	new_edge(n, randomize(lnnodes, ewmax, ewmin, (*this)[n] + ew), ew);
	ew = brand(ewmax, ewmin);
	new_edge(n, randomize(nnodes - lnnodes, ewmax, ewmin, (*this)[n] + ew), ew);
      }
    }
  } else { 			// not at root, guaranteed odd nnodes
    root = new_node(nscalar);
    if (nnodes -= 1) {
      lnnodes = brand(nnodes);
      if (!(lnnodes & 1)) lnnodes++; // make sure subtrees have odd nnodes >= 1
      ew = brand(ewmax, ewmin);
      new_edge(root, randomize(lnnodes, ewmax, ewmin, (*this)[root] + ew), ew);
      ew = brand(ewmax, ewmin);
      new_edge(root, randomize(nnodes - lnnodes, ewmax, ewmin, (*this)[root] + ew), ew);
    }
  }
  return root;
}

node CTree::root() const {
  return *nodes_begin();
}

edge CTree::edge_main(const node n) const { return emain[n]; }

int CTree::markup(node n) {
  edge e;
  int m = 0;
  forall_out_edges(e, n) {
    int mc = markup(e.target());
    if (mc > m) {
      emain[n] = e;
      m = mc;
    }
  }
  if (m == 0) {
    emain[n] = edge();
    return ((CGraph&) n.container())[n];
  } else {
    return m;
  }
}

node CTree::bend(const node n) const {
  if (edge_main(n) == edge()) return n;
  return bend(edge_main(n).target());
}

bool CTree::bend(const node n, const node nn) const {
  if (n == nn) return true;
  if (edge_main(n) == edge()) return false;
  return bend(edge_main(n).target(), nn);
}

string CTree::printbmain(const node n) const {
  ostringstream ost;
  if (emain[n] == edge()) {
    ost << n << endl;
  } else {
    ost << n << " --> " << printbmain(emain[n].target());
  }
  return ost.str();
}

node CTree::perturb(int nedges, int ewmax, int ewmin) {
  node root = CTree::root();
  if (nedges) {
    int numedges = number_of_edges();
    if (nedges > numedges) nedges = numedges;
    if (nedges < 0) nedges = 0;
    while (nedges--) {
      graph::edge_iterator eb = edges_begin();
      int ie = brand(numedges);
      while (ie--) eb++;
      setval(*eb, (*this)[*eb] + brand(ewmax, ewmin));
    }
  }
  return root;
}

// Local variables:
// compile-command: "make -k"
// End:
