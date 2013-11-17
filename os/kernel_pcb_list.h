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
 * @infos: insert a <pcb> in a <list>
 *
 * @param <list>: a list to insert to
 * @param <pcb>: the pcb to insert
 */
#define kernel_pcb_list_pushf(list,pcb) \
    { \
        if (!(list)->mFirst) \
        { \
            (list)->mLast = (pcb); \
        } \
        (pcb)->mNext = (list)->mFirst; \
        (list)->mFirst = (pcb); \
        (pcb)->mParentList = (list); \
    }

#define kernel_pcb_list_pushb(list,pcb) \
    { \
        if ((list)->mFirst) \
        { \
            (list)->mLast->mNext = (pcb); \
        } \
        else \
        { \
            (list)->mFirst = (pcb); \
        } \
        (list)->mLast = (pcb); \
        (pcb)->mNext = nullptr; \
        (pcb)->mParentList = (list); \
    }

/*
 * @infos: insert in a sorted <list>
 *
 * @param <list>: list to insert to
 * @param <pcb>: the PCB to insert
 */
void
kernel_pcb_list_sorted_insert(kernel_pcb_list_t * list, kernel_pcb_t * pcb);

/*
 * @infos: pop front a <list>
 *
 * @param <list>: a PCB list
 * @param <first_pcb>: return the first PCB pointer
 *
 * @asserts:
 *  - <list> must have at least one PCB
 */
#define kernel_pcb_list_popf(list,first_pcb) \
    { \
        (first_pcb) = (list)->mFirst; \
        (list)->mFirst = (first_pcb)->mNext; \
    }

/*
 * @infos: rotate to the left (the first became last)
 *
 * @param <list>: a PCB list
 *
 * @asserts:
 *  - <list> must have one PCB at least
 */
#define kernel_pcb_list_rotatel(list) \
    { \
        (list)->mLast->mNext = (list)->mFirst; \
        (list)->mLast = (list)->mFirst; \
        (list)->mFirst = (list)->mFirst->mNext; \
        (list)->mLast->mNext = nullptr; \
    }

/*
 * @infos: find a PCB in a <list> by a given <pid>
 *
 * @param <list>: list to search
 * @param <pid>: the PID to search in the list
 *
 * @return:
 *  - nullptr: if <pid> not in <list>
 *  - the PCB for the given <pid>
 */
kernel_pcb_t *
kernel_pcb_list_search(kernel_pcb_list_t * list, uint32_t pid);

/*
 * @infos: remove a <pcb> in a <list>
 *
 * @param <list>: a PCB list
 * @param <list>: a PCB to remove from the list
 *
 * @asserts:
 *  - <pcb> contained in <list>
 */
void
kernel_pcb_list_remove(kernel_pcb_list_t * list, kernel_pcb_t * pcb);


#endif
