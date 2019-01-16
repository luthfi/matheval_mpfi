#ifndef NODE_MPFI_H
#define NODE_MPFI_H 1

#if HAVE_CONFIG_H
#include "config.h"
#endif

#include "symbol_table.h"
#include "node.h"

#include "mpfi.h"
#include "mpfi_io.h"


typedef struct {
  char* sname;
  mpfi_t* mvar;
} mpfi_var;

void node_mpfi_construct(Node * node, mpfi_t f, mpfi_var* vars);

#endif
