#ifndef _H_KERNEL_FORWARD_DECLARATIONS
#define _H_KERNEL_FORWARD_DECLARATIONS

#include "standart.h"


/*
 * @infos: forward declaration of a PCB struct
 */
typedef struct kernel_pcb_s kernel_pcb_t;

/*
 * @infos: PCB meta list
 */
typedef struct kernel_pcb_list_s
{
    kernel_pcb_t * mFirst;
    kernel_pcb_t * mLast;
} kernel_pcb_list_t;


#endif
