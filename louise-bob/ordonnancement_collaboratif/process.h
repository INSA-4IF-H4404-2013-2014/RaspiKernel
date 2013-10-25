#ifndef PROCESS_H
#define PROCESS_H

#include <stdint.h>

#include "allocateMemory.h"


/*
 * Types
 */
typedef void (*func_t) (void);

/*
 * Enums
 */
typedef enum {READY, RUNNING, TERMINATED} PCB_STATE;
/*
 *  Structures
 */
struct pcb_s
{
	uint32_t* sp; // Stack Pointer
	unsigned int lr; // Link Register
	
	/*unsigned int r0;
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
	unsigned int r13;*/
	
	void* args;
	
	struct pcb_s* previous; // Pointer to the previous PCB
	struct pcb_s* next; // Pointer to the next PCB
	
	PCB_STATE running;
};

/*
 * Static variables
 */
struct pcb_s* current_process;

/*
 * Methods
 */
void init_pcb(struct pcb_s* pcb, func_t f, void* args, unsigned int stack_size);
void free_pcb(struct pcb_s* pcb);

#endif
