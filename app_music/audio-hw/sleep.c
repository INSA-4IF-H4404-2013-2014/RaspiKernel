#include "sleep.h"

void usleep(int time)
{
	int i;
	int j = 0;
	
	for(i = 0 ; time * 1000 ; i++)
	{
		j += 2 + i;
	}
}
