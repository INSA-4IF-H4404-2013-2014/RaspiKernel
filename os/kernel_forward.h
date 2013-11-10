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

/*
 * @infos: Process status
 */
typedef enum
{
    API_STATE_UNKNOWN,
    API_STATE_PAUSE,
    API_STATE_READY,
    API_STATE_RUNNING
} process_state_t;

#endif
