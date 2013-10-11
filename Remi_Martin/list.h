#ifndef _H_LIST
#define _H_LIST

typedef struct _pcb_s pcb_s;

typedef struct maillon
{
	pcb_s * pcb;
	struct maillon * previous;
	struct maillon * next;
} Tmaillon;


Tmaillon * insert ( Tmaillon * list, pcb_s * pcb );

#endif
