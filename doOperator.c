#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "doOperator.h"
#include "tokenStack.h"
#include "lexical.h"



static int op_quit(struct tokenStack *stack);
static int op_print(struct tokenStack *stack);
static int op_dump(struct tokenStack *stack);
static int op_add(struct tokenStack *stack);
static int op_diff(struct tokenStack *stack);
static int op_product(struct tokenStack *stack);
static int op_quotient(struct tokenStack *stack);
static int op_gt(struct tokenStack *stack);
static int op_ge(struct tokenStack *stack);
static int op_lt(struct tokenStack *stack);
static int op_le(struct tokenStack *stack);
static int op_eq(struct tokenStack *stack);
static int op_mod(struct tokenStack *stack);
static int op_swap(struct tokenStack *stack);
static int op_if(struct tokenStack *stack);
static int op_drop(struct tokenStack *stack);
static int op_modquot(struct tokenStack *stack);
static int op_modquot(struct tokenStack *stack);
static int op_help(struct tokenStack *stack);

static struct operator_struct {
	char *name;
	int (*fn_ptr)(struct tokenStack *);
} ops[] = {
	{"quit", op_quit},
	{"print", op_print},
	{"dump", op_dump},
	{"+", op_add},
	{"-", op_diff},	
	{"*", op_product},
	{"/", op_quotient},	
	{"GT", op_gt},	
	{"GE", op_ge},	
	{"LT", op_lt},
	{"LE", op_le},
	{"EQ", op_eq},
	{"MOD", op_mod},
	{"SWAP", op_swap},
	{"IF", op_if},
	{"DROP",op_drop},
	{"MODQUOT",op_modquot},
	{"HELP",op_help},

	{(char *)NULL, (int(*)(struct tokenStack *)) NULL}
};


/* YOU WRITE THIS */
static int popInt(struct tokenStack *s) {
	struct lexToken *popped = popTokenStack(s);
		
	return atoi(popped->symbol);
}

/* YOU WRITE THIS */
static void pushInt(struct tokenStack *s, int v) {
	struct lexToken *newToken = allocToken();
	newToken->kind = LEX_TOKEN_NUMBER;
	sprintf(newToken->symbol, "%d", v);
	pushTokenStack(s, newToken);
}

int doOperator(struct tokenStack *stack, char *o) {
	struct operator_struct *op = ops;
	for(op=ops;op->name != (char *)NULL; op++) {
	if(!strcmp(op->name, o))
	  return op->fn_ptr(stack);
	}
	return(-1);
}

/*ARGSUSED*/
static int op_quit(struct tokenStack *stack) {
	printf("[quit]\n");
	exit(0);
	/*NOTREACHED*/
}

static int op_print(struct tokenStack *stack) {
	struct lexToken *t = popTokenStack(stack);
	printToken(stdout, t);
	freeToken(t);
	return(0);
}

static int op_dump(struct tokenStack *stack) {
	struct lexToken *t = popTokenStack(stack);
	dumpToken(stdout, t);
	freeToken(t);
	return(0);
}

static int op_add(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v1+v2);
	return 0;
}

static int op_diff(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v2-v1);
	return 0;
}

static int op_product(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v1*v2);
	return 0;
}

static int op_quotient(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	if(v2== 0){
	printf("its 0 to become divider");	
	}else{
	pushInt(stack, v2/v1);}
	return 0;
}

static int op_gt(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v2 > v1);
	return 0;
}

static int op_ge(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v2 >= v1);
	return 0;
}

static int op_lt(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v2 < v1);
	return 0;
}

static int op_le(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v2 <= v1);
	return 0;
}

static int op_eq(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v2 == v1);
	return 0;
}

static int op_mod(struct tokenStack *stack) {
	int v1, v2;
	v1 = popInt(stack);
	
	pushInt(stack, v1);
	pushInt(stack, v1);
	return 0;
}

static int op_swap(struct tokenStack *stack) {
	int v1;
	int v2;
	v1 = popInt(stack);
	v2 = popInt(stack);
	pushInt(stack, v1);
	pushInt(stack, v2);
	return 0;
}

static int op_if(struct tokenStack *stack) {
	int v1, v2, v;
	v = popInt(stack);
	v2 = popInt(stack);
	v1 = popInt(stack);
	if (v != 0) pushInt(stack, v1);
	else pushInt(stack, v2);
	return 0;
}

static int op_drop(struct tokenStack *stack) {
	int v1;
	v1=popInt(stack);
	return 0;
}
static int op_modquot(struct tokenStack *stack){
	int v1,v2;
	v1=popInt(stack);
	v2=popInt(stack);
	pushInt(stack,v2/v1);
	pushInt(stack,v2%v1);
	return 0;
}

static int op_help(struct tokenStack *stack){
        printf("* (n1 n2 — product) - push n1*n2\n");
	printf("*/   (n1 n2  — quotient) - push n1/n2\n" );
	printf("*GT  (n1 n2  —  gt)  -push 1 if n1 > n2 and 0 otherwise\n ");
	printf("LT (n1 n2 — lt) -push 1 if n1 < n2 and 0 otherwis\n");
	printf("GE (n1 n2 — ge) -push 1 if n1 >= n2 and 0 otherwise\n ");
 	printf("LE (n1 n2 — le) -push 1 if n1 <= n2 and 0 otherwis\n");
	printf("EQ (n1 n2 — eq) -push 1 if n1 == n2 and 0 otherwise\n");
 	printf("MOD (n1 - n1 n1) - push two copies of n1 onto the stack\n");	
	printf("IF (n1 n2 v — x) - if v is not zero then push n1 otherwise n2\n");
 	printf("MODQUOT (n1 n2 — rem quotient) - push remainder then quotient\n");
 	printf("SWAP (n1 n2 — n2 n1) - swap the order of the top two elements on the stack\n");
	printf("HELP(—)-print out all commands plus a line of documentation This is made easier due to the help string in the table\n");
	printf("ROT (n1 n2 n3 — n2 n3 n1) - rotate top 3 elements on the stack\n");
	printf("DROP (n1 — ) - drop the top element off of the stack\n");
	printf("S (—) - print all elements on the stack non destructively\n");
	return 0;


        
}

