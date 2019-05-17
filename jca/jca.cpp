#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <map>
#include "cudd.h"
#include "cuddInt.h"

typedef struct {
    int index;
    DdNode *node;
} MapItem;

static int varIndex;
static std::map<std::string, MapItem *> varMap;
static DdManager * mgr;
#define MAX_NAME_COUNT 100
char const *inames[MAX_NAME_COUNT];

DdNode *getVar(char const *name)
{
  if (!varMap[name]) {
    varMap[name] = new MapItem;
    varMap[name]->index = varIndex;
    varMap[name]->node = Cudd_bddIthVar(mgr, varIndex);
    inames[varIndex] = name;
    varIndex++;
  }
  return varMap[name]->node;
}

int main(void) {
  mgr = Cudd_Init(MAX_NAME_COUNT,0,CUDD_UNIQUE_SLOTS,CUDD_CACHE_SLOTS,0);
  DdNode *b = getVar("b");
  DdNode *d = getVar("d");
  DdNode *c = getVar("c");
  DdNode *a = getVar("a");
  /* Build BDD. */
#if 0
  DdNode * tmp = Cudd_bddIte(mgr, b, c, Cudd_Not(d));
  Cudd_Ref(tmp);
  DdNode * f = Cudd_bddOr(mgr, a, tmp);
#else
  DdNode * tmp = Cudd_bddAnd(mgr, a, DD_ONE(mgr));
  Cudd_Ref(tmp);
  tmp = Cudd_bddAnd(mgr, b, tmp);
  Cudd_Ref(tmp);
  tmp = Cudd_bddAnd(mgr, a, tmp);
  Cudd_Ref(tmp);
  tmp = Cudd_bddAnd(mgr, b, tmp);
  Cudd_Ref(tmp);
  tmp = Cudd_bddAnd(mgr, b, DD_ONE(mgr));
  Cudd_Ref(tmp);
  DdNode * f = Cudd_bddAnd(mgr, a, tmp);
#endif
  Cudd_Ref(f);
  Cudd_RecursiveDeref(mgr, tmp);
  char * fform = Cudd_FactoredFormString(mgr, f, inames);
  printf("%s\n", fform);
  free(fform);
  Cudd_RecursiveDeref(mgr, f);
  int err = Cudd_CheckZeroRef(mgr);
  Cudd_Quit(mgr);
  return err;
}
