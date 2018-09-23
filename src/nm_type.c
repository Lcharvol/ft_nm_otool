#include "../includes/nm.h"

static unsigned char				get_sect_type(int n_sect, char *ptr)
{
	
}			

unsigned char				get_type(char *ptr, unsigned char type, int n_sect)
{
	if (n_sect == NO_SECT)
	{
		if ((type & N_TYPE) == N_UNDF)
			return ('U');
		else if ((type & N_TYPE) == N_ABS)
			return ((type & N_EXT) ? 'A' : 'a');
		else if ((type & N_TYPE) == N_PBUD)
			return ((type & N_EXT) ? 'U' : 'u');
	}
	if((type & N_TYPE) == N_SECT)
		return get_sect_type(n_sect, ptr);
	return '?';
};
