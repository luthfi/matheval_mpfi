#if HAVE_CONFIG_H
#include "config.h"
#endif

#include <math.h>
#include <assert.h>
#include <stdarg.h>
#include "common.h"

#include "node_mpfi.h"
#define EPSILON 0.0001

/************************ mpfi node ************************/
mpfi_t* get_mpfi_var(char* name, mpfi_var* vars) {
  //name must be found, must exist
  int i = 0;
  while (0 != strcmp(name, vars[i].sname)) {
	i++;
  }
  return vars[i].mvar;
}

// f must be initialized before calling this this procedure
void node_mpfi_construct(Node * node, mpfi_t f, mpfi_var* vars)
{
  mpfi_t f1, f2;
  mpfi_t* v;
  char* str;
  /* According to node type, construct subtree rooted at node. */
  switch (node->type) {
  case 'n':
	mpfi_init_set_d(f, node->data.number);
	break;
  case 'c':
	/* Constant values are used from symbol table. */
	mpfi_init_set_d(f, node->data.constant->data.value);
	break;
  case 'v':
	/* Variable values are used from symbol table. */
	v = get_mpfi_var(node->data.variable->name, vars);
	mpfi_set(f, *v);
	break;

  case 'f':
	/* Functions are constructd through symbol table. */
	mpfi_init(f1);
	node_mpfi_construct(node->data.function.child, f1, vars);
	str = node->data.function.record->name;
	if (0 == strcmp(str, "log")) { //base 10
	  mpfi_log10(f, f1);
	} else if (0 == strcmp(str, "ln")) { //base e natural
	  mpfi_log(f, f1);
	}
	mpfi_clear(f1);
    printf("func:%s \n", node->data.function.record->name);
	/* return (*node->data.function.record->data. */
	/* 		function) (node_mpfi_construct(node->data.function. */
	/* 									   child)); */
	
  case 'u':
	/* Unary operation node is constructd according to
	 * operation type. */
	switch (node->data.un_op.operation) {
	case '-':
	  mpfi_init(f1);
	  node_mpfi_construct(node->data.un_op.child, f1, vars);
	  mpfi_neg(f, f1);
	  mpfi_clear(f1);
	  break;
	}
	break;
  case 'b':
	/* Binary operation node is constructd according to
	 * operation type. */
	switch (node->data.un_op.operation) {
	case '+':
	  mpfi_init(f1);
	  mpfi_init(f2);
	  node_mpfi_construct(node->data.bin_op.left, f1, vars);
	  node_mpfi_construct(node->data.bin_op.right, f2, vars);
	  mpfi_add(f, f1, f2);
	  mpfi_clear(f1);
	  mpfi_clear(f2);
	  break;
	case '-':
	  /* return node_mpfi_construct(node->data.bin_op.left) - */
	  /* 	node_mpfi_construct(node->data.bin_op.right); */
	  mpfi_init(f1);
	  mpfi_init(f2);
	  node_mpfi_construct(node->data.bin_op.left, f1, vars);
	  node_mpfi_construct(node->data.bin_op.right, f2, vars);
	  mpfi_sub(f, f1, f2);
	  mpfi_clear(f1);
	  mpfi_clear(f2); 
	  break;
	case '*':
	  /* return node_mpfi_construct(node->data.bin_op.left) * */
	  /* 	node_mpfi_construct(node->data.bin_op.right); */
	  mpfi_init(f1);
	  mpfi_init(f2);
	  node_mpfi_construct(node->data.bin_op.left, f1, vars);
	  node_mpfi_construct(node->data.bin_op.right, f2, vars);
	  mpfi_mul(f, f1, f2);
	  mpfi_clear(f1);
	  mpfi_clear(f2); 
	  break;
	case '/':
	  /* return node_mpfi_construct(node->data.bin_op.left) / */
	  /* 	node_mpfi_construct(node->data.bin_op.right); */
	  mpfi_init(f1);
	  mpfi_init(f2);
	  node_mpfi_construct(node->data.bin_op.left, f1, vars);
	  node_mpfi_construct(node->data.bin_op.right, f2, vars);
	  mpfi_div(f, f1, f2);
	  mpfi_clear(f1);
	  mpfi_clear(f2); 
	  break;
	case '^': //we only handle 2^g(x)
	  /* return pow(node_mpfi_construct(node->data.bin_op.left), */
	  /* 			 node_mpfi_construct(node->data.bin_op.right)); */
	  mpfi_init(f1);
	  mpfi_init(f2);
	  node_mpfi_construct(node->data.bin_op.left, f1, vars);
	  assert (EPSILON > abs(2 - mpfi_get_d(f1))); //f1 ~= 2
	  node_mpfi_construct(node->data.bin_op.right, f2, vars);
	  mpfi_exp2(f, f2);
	  mpfi_clear(f1);
	  mpfi_clear(f2);
	}
	break;
  }
}
