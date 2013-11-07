
.globl kernel_arm_mode
kernel_arm_mode:
    mrs r0, cpsr
    and r0, r0, #0x1F
    bx lr

