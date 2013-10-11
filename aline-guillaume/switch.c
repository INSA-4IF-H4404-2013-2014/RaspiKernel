
#include "process.h"
#include "switch.h"

#define SWITCH_REGISTER(i) \
        __asm ("mov %0, r" #i : "=r"(current_ctx->mR[i])); \
        __asm ("mov r" #i ", %0" : : "r"(ctx->mR[i]))


void switch_to(struct ctx_s* ctx)
{
  __asm ("mov %0, sp" : "=r"(current_ctx->mSP));
  __asm ("mov %0, lr" : "=r"(current_ctx->mPC));

  SWITCH_REGISTER(0);
  SWITCH_REGISTER(1);
  SWITCH_REGISTER(2);
  SWITCH_REGISTER(3);
  SWITCH_REGISTER(4);
  SWITCH_REGISTER(5);
  SWITCH_REGISTER(6);
  SWITCH_REGISTER(7);
  SWITCH_REGISTER(8);
  SWITCH_REGISTER(9);
  SWITCH_REGISTER(10);
  SWITCH_REGISTER(11);
  SWITCH_REGISTER(12);

  current_ctx = ctx;

  __asm ("mov lr, %0" : : "r"(ctx->mPC));
  __asm ("mov sp, %0" : : "r"(ctx->mSP));
}
