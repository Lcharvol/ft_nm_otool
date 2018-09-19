#include "../includes/nm.h"

static void          print_text_section_content_64(uint64_t	offset, char *ptr, uint64_t index, uint64_t size)
{
	unsigned char	*str;
	uint64_t				i;
	uint64_t				length;

	i = 0;
	length = (index + 16) <= size ? 16 : (size - index);
	str = (void *)ptr + offset + index;
	while(i < length)
	{
		if((i == (length - 1)) && ((index + 16) >= size))
			ft_printf("%2.2x \n", str[i]);
		else
			ft_printf("%2.2x ", str[i]);
		i++;
	}
}

static void         print_text_section_content_32(uint32_t	offset, char *ptr, uint32_t index, uint32_t size)
{
	unsigned char	*str;
	uint32_t				i;
	uint32_t				length;

	i = 0;
	length = (index + 16) <= size ? 16 : (size - index);
	str = (void *)ptr + offset + index;
	while(i < length)
	{
		if((i == (length - 1)) && ((index + 16) >= size))
			ft_printf("%2.2x \n", str[i]);
		else
			ft_printf("%2.2x ", str[i]);
		i++;
	}
}

void	print_text_section_64(struct section_64	*sects, char *ptr, t_env *env)
{
	uint64_t i;

	i = 0;
	if (ft_strlen(env->ar_name) > 0)
		ft_printf("%s(%s):\n", env->file_name, env->ar_name);
	else
		ft_printf("%s:\n", env->file_name);
	ft_printf("Contents of (__TEXT,__text) section\n");
	ft_printf("%016lx	", sects->addr);
	print_text_section_content_64(sects->offset, ptr, i, sects->size);
	while(i < sects->size)
	{

		
		if (i % 16 == 0 && i != 0)
		{
			ft_printf("\n%016lx	", sects->addr + i);
			print_text_section_content_64(sects->offset, ptr, i, sects->size);
		}
		i++;
	}
}

void	print_text_section_32(struct section	*sects, char *ptr, t_env *env)
{
	uint32_t i;

	i = 0;
	if (ft_strlen(env->ar_name) > 0)
		ft_printf("%s(%s):\n", env->file_name, env->ar_name);
	else
		ft_printf("%s:\n", env->file_name);
	ft_printf("Contents of (__TEXT,__text) section\n");
	ft_printf("%08lx	", sects->addr);
	print_text_section_content_32(sects->offset, ptr, i, sects->size);
	while(i < sects->size)
	{
		if (i % 16 == 0 && i != 0)
		{
			ft_printf("\n%08lx	", sects->addr + i);
			print_text_section_content_32(sects->offset, ptr, i, sects->size);
		}
		i++;
	}
}