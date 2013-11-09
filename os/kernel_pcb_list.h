#ifndef _H_KERNEL_PCB_LIST
#define _H_KERNEL_PCB_LIST

#include "kernel_pcb.h"

// --------------------------------------------------------------- PCB META LISTS

/*
 * @infos: init a pcb list
 */
#define kernel_pcb_list_init(list) \
    (list)->mFirst = nullptr

/*
 * @infos: get first element
 *
 * @return:
 *  - nullptr if list is empty
 *  - a pointer on the first element
 */
#define kernel_pcb_list_first(list) \
    (list)->mFirst

/*
 * @infos: insert in a meta lists
 */
#define kernel_pcb_list_pushb(list,pcb) \
    { \
        if ((list)->mFirst) \
        { \
            (list)->mLast->mNextMeta = (pcb); \
        } \
        else \
        { \
            (list)->mFirst = (pcb); \
        } \
        (list)->mLast = (pcb); \
        (pcb)->mNextMeta = nullptr; \
    }

/*
 * @infos: pop front a meta list
 */
#define kernel_pcb_list_popf(list,first_pcb) \
    { \
        (first_pcb) = (list)->mFirst; \
        (list)->mFirst = (first_pcb)->mNextMeta; \
    }


#endif
