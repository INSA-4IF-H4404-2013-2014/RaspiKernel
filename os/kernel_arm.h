#ifndef _H_KERNEL_ARM
#define _H_KERNEL_ARM

#include "standart.h"

// doc1 : doc_arm_specs.pdf

//------------------------------------------------------------------------------ REGISTERS

/* Register (doc1, chapter A2.3)
 *
 *  - r0 - r7: unbanked general registers
 *  - r8 - r12: banked registers (not fiq, fiq)
 *  - r13 = sp: stack pointer
 *  - r14 = lr: parent caller address
 *  - r15 = pc: program counter
 *  - cpsr: status register
 *  - spsr: copy of cpsr before interuption
 *      this register is hidden, bancked and only available in interuption
 *      modes (SVC, ABT, UND, IRQ and FIQ).
 *
 * r13 and r14 are also banked for modes:
 *  - USR and SYS
 *  - SVC
 *  - ABT
 *  - UND
 *  - IRQ
 *  - FIQ
 */

/* Multiple push/pop
 *  http://infocenter.arm.com/help/index.jsp?topic=/com.arm.doc.dui0204j/Babefbce.html
 *
 *  "Registers are stored on the stack in numerical order, with the lowest
 *  numbered register at the lowest address."
 */


//------------------------------------------------------------------------------ MODES
/*
 * Modes (doc1, chapter A2.2):
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


//------------------------------------------------------------------------------ STATUS REGISTER (CPSR)

#define KERNEL_ARM_CPSR_MASK_IRQ 0x80

#define kernel_arm_enable_irq() \
  __asm("\tpush {r0}\n\t" \
      "mrs r0,cpsr\n\t" \
      "bic r0,r0,#" macro_value_str(KERNEL_ARM_CPSR_MASK_IRQ) "\n\t" \
      "msr cpsr_c,r0\n\t" \
      "pop {r0}" \
      : \
      : \
      : "r0");

#define kernel_arm_disable_irq() \
  __asm("\tpush {r0}\n\t"	\
      "mrs r0,cpsr\n\t"	\
      "orr r0,r0,#" macro_value_str(KERNEL_ARM_CPSR_MASK_IRQ) "\n\t" \
      "msr cpsr_c,r0\n\t" \
      "pop {r0}" \
      : \
      : \
      : "r0");


/*
 * @infos: get the status register CPSR's value
 *
 * @return:
 *  - the CPSR value
 */
uint32_t
kernel_arm_get_cpsr();


#endif

