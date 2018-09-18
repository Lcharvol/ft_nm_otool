#include "../includes/nm.h"

uint64_t	swap_bigendian_littleendian(uint64_t number, size_t sizeoff)
{
	uint64_t	nb_swapped;
	int			i;
	int			j;
	int			i_max;

	if (sizeoff == 1)
		return ((number & 0xF0) >> 4 | (number & 0x0F) << 4);
	i = 0;
	j = sizeoff - 1;
	i_max = sizeoff / 2;
	nb_swapped = 0;
	while (i < i_max)
	{
		nb_swapped |= ((((size_t)0xFF << (8 * i)) & number) << (8 * (j - i)));
		nb_swapped |= ((((size_t)0xFF << (8 * j)) & number) >> (8 * (j - i)));
		i++;
		j--;
	}
	return (nb_swapped);
}

int						is_sym_tab(char *ptr)
{
	int	i;

	i = -1;
	while(++i < SARMAG)
		if(ARMAG[i] != ptr[i])
			return (-1);
	return (0);
}