#include "../includes/nm.h"

void						handle_fat_arch(char *ptr, t_env *env)
{
	struct fat_header	*header_fat;
	struct mach_header	*mach_header;
	struct fat_arch		*arch;
	cpu_type_t			cputype;
	unsigned long		nfat_arch;
	unsigned long		arch_offset;
	unsigned long		i;

	i = 0;
	header_fat = env->header_fat;
	nfat_arch = header_fat->magic == FAT_MAGIC ? header_fat->nfat_arch :
		swap_bigendian_littleendian(header_fat->nfat_arch , sizeof(header_fat->nfat_arch ));
	while(i < nfat_arch)
	{
		arch = (void *)header_fat + sizeof(struct fat_header) + (i * sizeof(struct fat_arch));
		cputype = header_fat->magic == FAT_MAGIC ? arch->cputype : swap_bigendian_littleendian(arch->cputype, sizeof(arch->cputype));
		arch_offset = header_fat->magic == FAT_MAGIC ? arch->offset : swap_bigendian_littleendian(arch->offset, sizeof(arch->offset));
		mach_header = (struct mach_header *)((void *)ptr + arch_offset);
		env->header_32 = mach_header;
		if(cputype == CPU_TYPE_X86_64)
			otool((void *)ptr + arch_offset, env);
		i++;
	}
}