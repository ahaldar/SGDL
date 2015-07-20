/* This software is distributed under the GNU General Public License Version 3 */
/* Copyright (C) Aparajita Haldar */

#include "ebdgraph.h"

int EBDGraph::setlevel(node n, int lval) {
  int oval = nlevel[n];
  nlevel[n] = lval;
  return oval;
}

int EBDGraph::setweight(node n, int val) {
  return CGraph::setval(n, val);
}

void EBDGraph::build(CTree& ct, node n) {
  edge e;
  node n1, n2;
  node nn;
  forall_out_edges(e, n) {
    if (e.target().outdeg() == 0) {
      n1 = new_node(n, e.target(), 0);
      setweight(n1, ct[endnode(n1)] - ct[startnode(n1)]);
    }
    else {
      n1 = new_node(n, ct.bend(e.target()), 0);
      setweight(n1, ct[endnode(n1)] - ct[startnode(n1)]);
      build(ct, e.target());
    }
  }
}

void EBDGraph::markup(CTree& ct) {
  node n;
  edge e;
  int flag;
  do{
    flag = 0;
    forall_nodes(n, (*this)) {
      forall_out_edges(e, n) {
	if (level(e.target()) == level(n)) {
	  setlevel(n, level(n) + 1);
	  flag = 1;
	}
      }
    }
  } while (flag);
}

EBDGraph::EBDGraph(const string& name) : CGraph(name) {}

node EBDGraph::new_node(node s, node t, int l) {
  node n = CGraph::new_node();
  start[n] = s;
  end[n] = t;
  nlevel[n] = l;
  return n;
}

string EBDGraph::dot(const string& s) const {
  ostringstream ost;
  ost << CGraph::dot(s);
  ost << "\t" << "node [" << endl;
  ost << "\t\t" << "shape=record" << endl;
  ost << "\t" << "];" << endl;
  return ost.str();
}

string EBDGraph::dot(const node n) const {
  ostringstream ost;
  ost << "\t" << n.id() << "\t"
      << "["
      << "label="
      << "\"" << n.id() << " ["
      << start[n].id() << "-" << end[n].id() << "](" << weight(n) << ")(" << nlevel[n] << ")\"" << ","
      << "rank=" << nlevel[n]
      << "];" << endl;
  return ost.str();
}

string EBDGraph::dot(const edge e) const {
  ostringstream ost;
  ost << "\t" << e.source().id() << " -> " << e.target().id() << ";" << endl;
  return ost.str();
}

void EBDGraph::dotf(ofstream& s, bool) const {
  node n;
  int maxlevel = 0;
  CGraph::dotf(s, false);
  forall_nodes(n, *this) {
    if (nlevel[n] > maxlevel) maxlevel = nlevel[n];
  }
  for (int i = 0; i <= maxlevel; i++) {
    s << "\t" << "{ rank=same; " << endl;
    forall_nodes (n, *this) {
      if (nlevel[n] == i) s << "\t\t" << n.id() << ";" << endl;
    }
    s << "\t" << "}" << endl;
  }
  s << "}" << endl;
}

void EBDGraph::dotf(const string& fname) const {
  CGraph::dotf(fname);
}

string EBDGraph::print(node n) const {
  ostringstream ost;
  ost << start[n] << "-" << end[n] << "," << nlevel[n];
  return ost.str();
}

string EBDGraph::print(const edge e) const {
  return CGraph::print(e);
}

node EBDGraph::startnode(node n) const { return start[n]; }

node EBDGraph::endnode(node n) const { return end[n]; }

int EBDGraph::level(node n) const { return nlevel[n]; }

int EBDGraph::weight(node n) const {
  return ((CGraph&) (*this))[n];
}

void EBDGraph::build(CTree& ct) {
  //set new level when edge from node max(child node+1, current level)
  node n1, n2;
  edge e;
  build(ct, ct.root());
  forall_nodes(n2, (*this)) {
    if (ct.bend(startnode(n2)) != (ct.bend(endnode(n2)))) {
      forall_nodes(n1, (*this)) {
	if ((ct.bend(startnode(n2)) == ct.bend(endnode(n1))) 
	    && (startnode(n1) != startnode(n2))) {
	  forall_out_edges(e, startnode(n1)) {
	    if (ct.bend(e.target(), startnode(n2))) {
	      new_edge(n1, n2);
	    }
	  }
	}
      }
    }
  }
  markup(ct);
}

// Local variables:
// compile-command: "make -k"
// End:
