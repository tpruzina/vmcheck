#include <stdio.h>
#include <inttypes.h>

typedef struct
{
	unsigned long	limit : 16;
	unsigned long	base  : 64;
} __attribute__((packed)) dt;

inline int
idtCheck()
{
	dt idt = {0, 0};
	asm volatile( "sidt %0" : "=m"(idt) );

	printf("IDT: limit=%04d, base=%016lx\n", idt.limit, idt.base);

	return idt.base;
}

int
gdtCheck()
{
	dt gdt = {0, 0};
	asm volatile( "sgdt %0" : "=m"(gdt) );
	
	printf("GDT: limit=%04d, base=%016lx\n", gdt.limit, gdt.base);

	return gdt.base;
}

int
ldtCheck()
{
	unsigned char m[6];

	asm("sldt %0\n" : : "m"(m));
	
	return (m[0] != 0x00 && m[1] != 0x00) ? 1 : 0;
}


int
main()
{
	idtCheck();
	gdtCheck();
	if(ldtCheck())
		return 0;
	else
		return -1;
}
