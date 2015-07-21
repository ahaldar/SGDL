/* This software is distributed under the GNU General Public License Version 3 */
/* Copyright (C) Aparajita Haldar */

#ifndef EBDG_CGRAPH_H
#define EBDG_CGRAPH_H

#include "util.h"
#include <GTL/graph.h>

class CGraph : public graph {

  node_map<int> scalar;
  edge_map<int> weight;
  string gname;

  /* New private member functions */

  void debug(const node, const node, const CGraph&, const string = "", ostream& = cout) const;

public:

  CGraph(const string = "Unnamed");

  CGraph(const CGraph&);

  /* Overriden base class member functions */

  virtual node new_node(int = 0);
  virtual edge new_edge(node, node, int = 0);

  // Save to and load from GML format file
  virtual void save_graph_info_handler(ostream*) const;
  virtual void load_graph_info_handler(GML_pair*);

  virtual void save_node_info_handler(ostream*, node) const;
  virtual void load_node_info_handler (node, GML_pair*);

  virtual void save_edge_info_handler (ostream*, edge) const;
  virtual void load_edge_info_handler (edge, GML_pair*);

  virtual void save(const string&) const;
  virtual void load(const string&);

  /* New member functions */

  // Retrieve and set graph data
  string name() const;
  string set_name(const string&);

  int operator[] (const node) const;
  int operator[] (const edge) const;

  virtual int setval(node, int);
  virtual int setval(edge, int);

  // Generate and perturb random graph
  virtual node randomize(int = 1, int = 0);

  // Save to Graphviz format file
  virtual string dot(const string& = "") const;
  virtual string dot(const node) const;
  virtual string dot(const edge) const;

  virtual void dotf(ofstream&, const bool = true) const;
  virtual void dotf(const string&) const;

  // Output format data
  virtual string print(const node) const;
  virtual string print(const edge) const;

  // Compare graphs for match or mismatch
  virtual bool compareData(const CGraph&) const;
  virtual bool compareData(const node, const node) const;
  virtual bool compareData(const edge, const edge) const;

  virtual bool compare(const node, const node, const CGraph&) const;
  virtual bool compare(const edge, const edge, const CGraph&) const;
  virtual bool compare(const CGraph&, bool = false) const;

  // Standard output for graph
  friend ostream& operator<< (ostream&, const CGraph&);

};

#endif // EBDG_CGRAPH_H

// Local variables:
// mode: c++
// End:
