#include <stdio.h>
#include <stdlib.h>
#include "cudd.h"

int main(void) {
  /* Get set. */
  DdManager * mgr = Cudd_Init(4,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
  DdNode *a = Cudd_bddIthVar(mgr, 0);
  DdNode *c = Cudd_bddIthVar(mgr, 1);
  DdNode *b = Cudd_bddIthVar(mgr, 2);
  DdNode *d = Cudd_bddIthVar(mgr, 3);
  char const * const inames[] = {"a", "c", "b", "d"};
  /* Build BDD. */
  DdNode * tmp = Cudd_bddIte(mgr, c, b, Cudd_Not(d));
  Cudd_Ref(tmp);
  DdNode * f = Cudd_bddOr(mgr, a, tmp);
  Cudd_Ref(f);
  Cudd_RecursiveDeref(mgr, tmp);
  /* Inspect it. */
  printf("f");
  Cudd_PrintSummary(mgr, f, 4, 0);
  Cudd_bddPrintCover(mgr, f, f);
  char * fform = Cudd_FactoredFormString(mgr, f, inames);
  printf("%s\n", fform);
  /* Break up camp and go home. */
  free(fform);
  Cudd_RecursiveDeref(mgr, f);
  int err = Cudd_CheckZeroRef(mgr);
  Cudd_Quit(mgr);
  return err;
}
