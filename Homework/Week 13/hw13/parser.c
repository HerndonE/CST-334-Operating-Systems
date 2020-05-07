#include "lexer.h"
#include "error.h"
#include "expr.h"
#include "stmt.h"
#include "prog.h"

//
// a predictive parser for a super-minimal programming language
//
// refer to the BNF  

// types of functions used below
void match();
PROG *parse(), *prog();
STMT *get_stmt();
EXPR *get_expr();

int lookahead;    // most recent token

// check that current token is t, and read next token
void match(int t) { 
    if (lookahead == t)
	lookahead = lexan();
    else error("syntax error");
} 

// parse a program
PROG *parse() {
   PROG *p;
   lookahead = lexan();
   p = prog();
   match(DONE);
   return p;
}

// one or more statements
PROG *prog() {

   // YOUR CODE HERE

   // replace the code directly below, which was added so that
   // everything will compile
    
   //EXPR *expr = expr_create_fcall("printf", expr_create_num(22));
   //STMT *stmt = stmt_create_assign("x", expr);
   //PROG *prog = prog_create(stmt, NULL);

   // you will create additional functions in this file for the
   // other non-terminals in your BNF grammar
   PROG *c_prog;
    
    switch (lookahead) {
        case ID:
            c_prog = prog_create(get_stmt(), prog());
            break;
        default:
            return NULL;
    }
    return c_prog;
}

STMT *get_stmt() {
   
}

EXPR *get_expr() {
    
}
