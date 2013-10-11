#ifndef _H_PROCESS
#define _H_PROCESS

#define STACK_SIZE 1024 * 32
#define REGISTER_COUNT 13

typedef void (*func_t)();

typedef struct ctx_s
{
  // PC = program counter
  unsigned int mPC;

  // SP = stack counter
  unsigned int mSP;

  // registers
  unsigned int mR[REGISTER_COUNT];
} _ctx_s;

extern struct ctx_s * current_ctx;

void init_ctx(struct ctx_s* ctx, func_t f, unsigned int stack_size);

#endif

