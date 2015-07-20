/* This software is distributed under the GNU General Public License Version 3 */
/* Copyright (C) Aparajita Haldar */

#include "util.h"

const char* ndata_key = "scalar";
const char* edata_key = "weight";
const char* name_key = "name";

bool DEBUG_MODE = false;

int brand(int nmax, int nmin) {
  static bool init = false;
  if (!init) {
    srand(time(NULL));
    init = true;
  }
  return nmin + ((double (rand()) / RAND_MAX) * (nmax - nmin));
}

// Local variables:
// compile-command: "make -k"
// End:
