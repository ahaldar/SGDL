/* This software is distributed under the GNU General Public License Version 3 */
/* Copyright (C) Aparajita Haldar */

#include "cgraph.h"

void CGraph::debug(const node n1, const node n2, const CGraph& g,
		   const string msg, ostream& s) const {
  if (DEBUG_MODE) {
    s << name();
    if (n1 != node()) s << n1;
    s << " , " << g.name();
    if (n2 != node()) s << n2;
    s << " : " << msg << endl;
  }
}

CGraph::CGraph(const string name) : gname(name) {}

CGraph::CGraph(const CGraph& g) : graph::graph(g) {
  node_map<node> nmap;
  set_name(g.name());

  graph::node_iterator nbs = g.nodes_begin();
  graph::node_iterator nes = g.nodes_end();
  while (nbs != nes){
    node n = new_node(g.scalar[*nbs]);
    nmap[*nbs] = n;
    nbs++;
  }

  graph::edge_iterator ebs = g.edges_begin();
  graph::edge_iterator ees = g.edges_end();
  while (ebs != ees) {
    new_edge(nmap[ebs->source()], nmap[ebs->target()], g.weight[*ebs]);
    ebs++;
  }
}

node CGraph::new_node(int sval) {
  node n = graph::new_node();
  scalar[n] = sval;
  return n;
}

edge CGraph::new_edge(node s, node t, int wval) {
  edge e = graph::new_edge(s, t);
  weight[e] = wval;
  return e;
}

void CGraph::save_graph_info_handler(ostream* s) const {
  *s << name_key << " \"" << name() << "\"" << endl;
}

void CGraph::load_graph_info_handler(GML_pair* list) {
  while (strcmp(list->key, name_key)) list = list->next;
  gname = list->value.str;
}

void CGraph::save_node_info_handler(ostream* s, node n) const {
  *s << ndata_key << " " << scalar[n] << endl;
}

void CGraph::load_node_info_handler (node n, GML_pair* list) {
  while (strcmp(list->key, ndata_key)) list = list->next;
  scalar[n] = list->value.integer;
}

void CGraph::save_edge_info_handler (ostream* s, edge e) const {
  *s << edata_key << " " << weight[e] << endl;
}

void CGraph::load_edge_info_handler (edge e, GML_pair* list) {
  while (strcmp(list->key, edata_key)) list = list->next;
  weight[e] = list->value.integer;
}

void CGraph::save(const string& fname) const {
  graph::save(fname.c_str());
}

void CGraph::load(const string& fname) {
  graph::load(fname.c_str());
}

string CGraph::name() const { return gname; }

string CGraph::set_name(const string& nname) {
  string oname = gname;
  gname = nname;
  return oname;
}

int CGraph::operator[] (const node n) const { return scalar[n]; }
int CGraph::operator[] (const edge e) const { return weight[e]; }

int CGraph::setval(node n, int sval) {
  int oval = scalar[n];
  scalar[n] = sval;
  return oval;
}

int CGraph::setval(edge e, int wval) {
  int oval = weight[e];
  weight[e] = wval;
  return oval;
}

node CGraph::randomize(int nnodes, int nedges) {
  int nmax = nnodes;
  int numnodes = number_of_nodes();
  int numedges = number_of_edges();
  if (numnodes) { // non-empty graph, perturb NNODES node values and NEDGES edge values
    if (numnodes < nnodes) nnodes = numnodes;
    if (nnodes < 0) nnodes = 0;
    while (nnodes--) {
      graph::node_iterator nb = nodes_begin();
      int in = brand(numnodes);
      while (in--) nb++;
      setval(*nb, brand(nmax));
    }
    if (numedges < nedges) nedges = numedges;
    if (nedges < 0) nedges = 0;
    while (nedges--) {
      graph::edge_iterator eb = edges_begin();
      int ie = brand(numedges);
      while (ie--) eb++;
      setval(*eb, brand(nmax));
    }
  } else { // new empty graph, add NNODES random nodes and NEDGES random edges
    if (nnodes <= 0) nnodes = 1;
    while (nnodes--) new_node(brand(nmax));
    if (nedges < 0) nedges = 0;
    while (nedges--) {
      graph::node_iterator nb1 = nodes_begin();
      graph::node_iterator nb2 = nodes_begin();
      int in1 = brand(nmax);
      int in2 = brand(nmax);
      while (in1--) nb1++;
      while (in2--) nb2++;
      new_edge(*nb1, *nb2, brand(nmax));
    }
  }
  return *nodes_begin();
}

string CGraph::dot(const string&) const {
  ostringstream ost;
  ost << (is_directed() ? "digraph" : "graph") << " {" << endl;
  ost << "\t" << "graph [" << endl;
  ost << "\t\t" << "rankdir=\"BT\"," << endl;
  ost << "\t\t" << "ranksep=\"equally\"," << endl;
  ost << "\t\t" << "label=\"" << name() << "\"" << endl;
  ost << "\t" << "];" << endl;
  return ost.str();
}

string CGraph::dot(const node n) const {
  ostringstream ost;
  ost << "\t" << n.id() << "\t"
      << "["
      << "label=" << "\"" << n.id() << " (" << scalar[n] << ")\""
      << "];" << endl;
  return ost.str();
}

string CGraph::dot(const edge e) const {
  ostringstream ost;
  ost << "\t" << e.source().id() << " -> " << e.target().id() << "\t" << "["
      << "label=" << weight[e]
      << "];" << endl;
  return ost.str();
}

void CGraph::dotf(ofstream& s, const bool close) const {
  node n;
  edge e;
  s << dot();
  forall_nodes(n, *this) {
    s << dot(n);
  }
  forall_edges(e, *this) {
    s << dot(e);
  }
  if (close) s << "}" << endl;
}

void CGraph::dotf(const string& fname) const {
  ofstream f(fname.c_str());
  dotf(f);
  f.close();
}

string CGraph::print(const node n) const {
  ostringstream ost;
  ost << ((CGraph&) n.container())[n];
  return ost.str();
}

string CGraph::print(const edge e) const {
  ostringstream ost;
  ost << ((CGraph&) e.source().container())[e];
  return ost.str();
}

bool CGraph::compareData(const CGraph& g) const {
  return name() == g.name();
}

bool CGraph::compareData(const node n1, const node n2) const {
  return (*this)[n1] == ((CGraph&) n2.container())[n2];
}

bool CGraph::compareData(const edge e1, const edge e2) const {
  return (*this)[e1] == ((CGraph&) e2.source().container())[e2];
}

bool CGraph::compare(const node n1, const node n2, const CGraph& g) const {
  if (n1.id() != n2.id() || n1.indeg() != n2.indeg() || n1.outdeg() != n2.outdeg()) {
    debug(n1, n2, g, "(Topology mismatch)", cout);
    return false;
  }
  if (!compareData(n1, n2)) return false;
  node::in_edges_iterator ieb1 = n1.in_edges_begin();
  node::in_edges_iterator iee1 = n1.in_edges_end();
  node::in_edges_iterator ieb2 = n2.in_edges_begin();
  while (ieb1 != iee1) {
    if (!compare(*ieb1, *ieb2, g)) {
      debug(n1, n2, g, "(In edge mismatch)", cout);
      return false;
    }
    ieb1++;
    ieb2++;
  }
  node::out_edges_iterator oeb1 = n1.out_edges_begin();
  node::out_edges_iterator oee1 = n1.out_edges_end();
  node::out_edges_iterator oeb2 = n2.out_edges_begin();
  while (oeb1 != oee1) {
    if (!compare(*oeb1, *oeb2, g)) {
      debug(n1, n2, g, "(Out edge mismatch)", cout);
      return false;
    }
    oeb1++;
    oeb2++;
  }
  return true;
}

bool CGraph::compare(const edge e1, const edge e2, const CGraph& g) const {
  return compareData(e1, e2);
}

bool CGraph::compare(const CGraph& g, const bool comparegdata) const {
  if (comparegdata && !compareData(g)) {
    debug(node(), node(), g, "(Graph data mnismatch)", cout);
    return false;
  }
  if (is_directed() != g.is_directed()
      || number_of_nodes() != g.number_of_nodes()
      || number_of_edges() != g.number_of_edges()) {
    debug(node(), node(), g, "(Graph structure mismatch)", cout);
    return false;
  }
  graph::node_iterator nb1 = nodes_begin();
  graph::node_iterator ne1 = nodes_end();
  graph::node_iterator nb2 = g.nodes_begin();
  while (nb1 != ne1) {
    debug(*nb1, *nb2, g, "Comparing...", cout);
    if (!compare(*nb1, *nb2, g)) {
      debug(*nb1, *nb2, g, "(Node mismatch)", cout);
      return false;
    }
    nb1++;
    nb2++;
  }
  return true;
}

ostream& operator<< (ostream& s, const CGraph& g) {
  node n;
  edge e;
  string edge_start = (g.is_directed() ? "--" : "<--");
  string edge_end = "-->";
  s << g.name() << " [" << endl;
  forall_nodes (n, g) {
    s << "  " << n << "(" << g.print(n) << ")" << ":: ";
    forall_adj_edges (e, n) {
      s << edge_start << g.print(e) << edge_end << n.opposite(e) << " ";
    }
    s << endl;
  }
  s << "]" << endl;
  return s;
}

// Local variables:
// compile-command: "make -k"
// End:
