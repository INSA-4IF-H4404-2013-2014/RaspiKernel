#include "dispatcher.h"


void switch_to(struct ctx_s* ctx)
{
	// Saving current context	
	__asm("mov %0, sp" : "=r"(current_ctx->sp));
	__asm("mov %0, lr" : "=r"(current_ctx->lr));
	__asm("mov %0, r0" : "=r"(current_ctx->r0));
	__asm("mov %0, r1" : "=r"(current_ctx->r1));
	__asm("mov %0, r2" : "=r"(current_ctx->r2));
	__asm("mov %0, r3" : "=r"(current_ctx->r3));
	__asm("mov %0, r4" : "=r"(current_ctx->r4));
	__asm("mov %0, r5" : "=r"(current_ctx->r5));
	__asm("mov %0, r6" : "=r"(current_ctx->r6));
	__asm("mov %0, r7" : "=r"(current_ctx->r7));
	__asm("mov %0, r8" : "=r"(current_ctx->r8));
	__asm("mov %0, r9" : "=r"(current_ctx->r9));
	__asm("mov %0, r10" : "=r"(current_ctx->r10));
	__asm("mov %0, r11" : "=r"(current_ctx->r11));
	__asm("mov %0, r12" : "=r"(current_ctx->r12));

	// Changing current context
	current_ctx = ctx;
	
	// Restore new context
	__asm("mov sp, %0" : : "r"(current_ctx->sp));
	__asm("mov lr, %0" : : "r"(current_ctx->lr));
	__asm("mov r0, %0" : : "r"(current_ctx->r0));
	__asm("mov r1, %0" : : "r"(current_ctx->r1));
	__asm("mov r2, %0" : : "r"(current_ctx->r2));
	__asm("mov r3, %0" : : "r"(current_ctx->r3));
	__asm("mov r4, %0" : : "r"(current_ctx->r4));
	__asm("mov r5, %0" : : "r"(current_ctx->r5));
	__asm("mov r6, %0" : : "r"(current_ctx->r6));
	__asm("mov r7, %0" : : "r"(current_ctx->r7));
	__asm("mov r8, %0" : : "r"(current_ctx->r8));
	__asm("mov r9, %0" : : "r"(current_ctx->r9));
	__asm("mov r10, %0" : : "r"(current_ctx->r10));
	__asm("mov r11, %0" : : "r"(current_ctx->r11));
	__asm("mov r12, %0" : : "r"(current_ctx->r12));
}
