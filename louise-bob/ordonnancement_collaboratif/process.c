#include "process.h"
#include "allocateMemory.h"


void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size)
{
	ctx->sp = AllocateMemory(stack_size);
	ctx->sp -= (stack_size - 1) * 4;
	ctx->lr = f;
}
