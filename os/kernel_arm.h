#ifndef _H_KERNEL_ARM
#define _H_KERNEL_ARM


// doc1 : doc_arm_specs.pdf

/*
 * Modes (doc1, chapter A2.2) :
 *  - User (0b10000) Normal program execution mode (can't change mode)
 *  - FIQ  (0b10001) Supports a high-speed data transfer or channel process
 *  - IRQ  (0b10010) Used for general-purpose interrupt handling
 *  - Supervisor (0b10011) A protected mode for the operating system
 *  - Abort      (0b10111) Implements virtual memory and/or memory protection
 *  - Undefined  (0b11011) Supports software emulation of hardware coprocessors
 *  - System     (0b11111) Runs privileged operating system tasks (ARMv4 and above)
 *
 * See (doc1, chapter A2.3)
 */

#define KERNEL_ARM_MODE_USR 0x10
#define KERNEL_ARM_MODE_FIQ 0x11
#define KERNEL_ARM_MODE_IRQ 0x12
#define KERNEL_ARM_MODE_SVC 0x13
#define KERNEL_ARM_MODE_ABT 0x17
#define KERNEL_ARM_MODE_UND 0x1B
#define KERNEL_ARM_MODE_SYS 0x1F


/*
 * @infos: Gets the current mode
 *
 * @return: The current mode
 */
uint32_t
kernel_arm_mode();


/*
 * @infos: Sets the current mode
 *
 * @asserts:
 *  - kernel_arm_mode() != KERNEL_ARM_MODE_USR
 */
#define _kernel_arm_set_mode(mode) \
    __asm("cps #" #mode);

#define kernel_arm_set_mode(mode) \
    _kernel_arm_set_mode(mode)


#endif

