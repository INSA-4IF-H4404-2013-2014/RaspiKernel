#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>


/*
 * Types
 */
typedef void (*func_t) (void);


/*
 *  Structures
 */
struct ctx_s
{
	uint32_t* sp; //Stack Pointer
	unsigned int lr; //Link Register
	unsigned int r0;
	unsigned int r1;
	unsigned int r2;
	unsigned int r3;
	unsigned int r4;
	unsigned int r5;
	unsigned int r6;
	unsigned int r7;
	unsigned int r8;
	unsigned int r9;
	unsigned int r10;
	unsigned int r11;
	unsigned int r12;
	unsigned int r13;
};


/*
 * Global variables
 */
struct ctx_s* current_ctx;


/*
 * Methods
 */
void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size);

#endif
