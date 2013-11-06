
.globl kernel_arm_mode
kernel_arm_mode:
    mrs r0, cpsr
    bic r0, r0, #0x1F
    bx lr

