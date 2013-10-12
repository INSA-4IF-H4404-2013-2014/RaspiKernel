
#include "process.h"
#include "allocateMemory.h"

struct ctx_s * current_ctx = 0;

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size)
{
  ctx->mPC = (unsigned int) f;
  ctx->mSP = (unsigned int) AllocateMemory(stack_size);
}

