#include "ivalarith.h"
/* evaluate arithmetic expression f(x)=expr between x=a to x=b,
and return the minimum result to min and the maximum result to max.
*/
void ivalarith_evaluate(char* expr, int a, int b, double* min, double* max) {
  void* f; //matheval tree representation
  mpfi_t x, fx;
  mpfi_var* vars;
  int count;
  mpfr_t left, right;
  char** names;
  int i;
  
  f = evaluator_create (expr);
  assert(f);
  mpfi_init(x);
  mpfi_init(fx);
  mpfr_init(left);
  mpfr_init(right);
  evaluator_get_variables (f, &names, &count);
  vars = (mpfi_var*) malloc (count * sizeof(mpfi_var));
  assert(count < 2); //handle only x
  for (i = 0; i < count; i++) {
	vars[i].sname = names[i];
	switch(i) {
	  case 0:
		vars[i].mvar = &x;
		break;
	  /* case 1: */
	  /* 	vars[i].mvar = &y; */
	  /* 	break; */
	  /* case 2: */
	  /* 	vars[i].mvar = &z; */
	  /* 	break; */
	}
  }

  mpfi_interv_si(x, a, b);
  evaluator_mpfi_evaluate(f, fx, vars);
  mpfi_get_left(left, fx);
  mpfi_get_right(right, fx);
  *min = mpfr_get_d(left, MPFR_RNDZ);
  *max = mpfr_get_d(right, MPFR_RNDZ);
  mpfr_clear(left);
  mpfr_clear(right);
  mpfi_clear(x);
  mpfi_clear(fx);
  evaluator_destroy(f);
}
