/* This software is distributed under the GNU General Public License Version 3 */
/* Copyright (C) Aparajita Haldar */

#include "ctree.h"
#include "ebdgraph.h"
#include <ctime>

void usage(char* argv) {
  cout << "Usage: " << argv << " <N> <W>" << endl;
  cout << "<N> : number of nodes, <W> : maximum weight" << endl;
  exit(0);
}

void check_args(int argc, char** argv, int& nnodes, int& maxwt, string& fname) {
  if (argc <= 3) {
    usage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &nnodes) < 1 ||
      sscanf(argv[2], "%d", &maxwt) < 1) {
    usage(argv[0]);
  }
  fname = string(argv[3]);
}

int main(int argc, char** argv) {

  int nnodes, nedges, maxwt;
  string fname;
  // DEBUG_MODE = true;
  check_args(argc, argv, nnodes, maxwt, fname);
  cout << "Using nodes " << nnodes << " maxwt " << maxwt
       << " file " << fname << endl;

  //CGraph G;
  //G.randomize(nnodes, maxwt);
  //cout << G;
  //G.dotf(fname + "-cgraph.dot");
  //string comm = "xdot " + fname + "-cgraph.dot";
  //system(comm.c_str());

  //clock_t c;
  //c = clock();

  CTree t("My Tree");
  t.randomize(nnodes, maxwt);
  t.markup(t.root());
  t.dotf(fname + "-ctree.dot");
  cout << t;

  //cout << "Randomize time: " << (float)(clock() - c)/CLOCKS_PER_SEC << endl;

  //c = clock();

  EBDGraph ebdg("My EBDG");
  ebdg.build(t);

  //cout << "Build time: " << (float)(clock() - c)/CLOCKS_PER_SEC << endl;
  ebdg.dotf(fname + "-ebdg.dot");
  cout << ebdg;

  string comm = "xdot " + fname + "-ctree.dot & xdot " + fname + "-ebdg.dot";
  system(comm.c_str());
  exit(0);
}

// Local variables:
// compile-command: "make -k"
// End:
