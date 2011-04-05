#include <stdio.h>
#include <stdlib.h>

int * phys_mem_table = 0;

void init_paging(void);
void print_phys_mem_bitmap(int*);
int * alloc_phys_page(void);
void free_phys_page(int*);
void init_phys_alloc(int*);

// | 3702 bytes for physmem table | 4096 bytes for page directory| :

void main(void) {

	printf("Enabling paging (not really)\n");
	init_paging();
}

void init_paging(void) {

	//TODO make this line into a define
//	phys_mem_table = (int *)1073741824;  //This should be the start of the 2nd gig in ram
	phys_mem_table = (int*) malloc((24576 * sizeof(int*)) + 3);

	if(phys_mem_table == NULL) {
		printf("Failed to malloc phys_mem_table\n");
	}

	int offset = ((int)phys_mem_table) % 4;
	phys_mem_table += offset;
	
	init_phys_alloc(phys_mem_table);
	print_phys_mem_bitmap(phys_mem_table);
	alloc_phys_page();
	print_phys_mem_bitmap(phys_mem_table);
	alloc_phys_page();
	print_phys_mem_bitmap(phys_mem_table);
}

void print_phys_mem_bitmap(int * start) {
	int x;
	printf("Physical mem table:");
	for(x = 0; x < 24576; x++) {
		printf("%x", start[x]);
	}

	printf("\n");
}

int * alloc_phys_page(void) {

printf("gunna getcha a page\n");
	if( phys_mem_table == NULL) {
		//TODO error out because you called this before calling init_phys_alloc
	}


	// find free bit in table
	int x;
	for(x = 0; x < 24576; x++) {
//printf("I am on page %i\r", x);
//fflush(stdout);
		// If this native memory sized block in table is not all taken
		if(phys_mem_table[x] != 0xFFFFFFFF) {
			unsigned int mask;
			int y = 0;
			//From right to left find the first bit that is not clear
			for(mask = 0x00000001; mask != 0x00000000; mask = mask<<1) {
				//if bit is clear
printf("mask is %x, entry is %x\n", mask, phys_mem_table[x]); sleep(1);
				if((mask & phys_mem_table[x]) == 0) {
					phys_mem_table[x] = phys_mem_table[x] | mask;
					// 32 pages per x
					// 1 page per y
					//start of phys_mem_table + 32 pages per x + y pages
					return (int*)( phys_mem_table + ( (1024 * 4 * 32 * x ) + ( 1024 * 4 * y ) ) );  
				}
				y++;
			}
		}
	}

	//TODO if we get this far we have run out of free pages, do something

}



void free_phys_page(int * page) {

	// location - page = offset
	// offset / size of page  should be the index of page in the paging area
	// 32 indexes per native memory size should give us how many 32 bit intervals in our memory to free is in

	int delta = ( ( (int)page - (int)phys_mem_table) / (1024 * 4) ) / 32;
	
	int shift = ( ( (int)page - (int)phys_mem_table) / (1024 * 4) ) % 32;

	// clear the bit in the table
	phys_mem_table[delta] &= ~(1<<shift);

}


void init_phys_alloc(int * start) {

	int page;
	int page_entry; //Page enties are 32 bit

	//It takes 24576 pages to store the physcial memmory allocator
	//Zero out the next 24576 pages
	//pages have 4096 bytes or 1024 32 bit entries

	for(page = 0; page < 24576; page++) {

		start[page] = 0;
	}

	// since the physcial memmory allocater itself takes up 24576 pages,
	// flip the first 24576 bits to allocate the physical memmory for it

	int x;

	for(x = 0; x < (24576 / 32); x++) {
		start[x] = 0xFFFFFFFF;
	}
	
	return;	
}


/*
void enable_paging(void) {
	__asm__("mov	%eax,	POINTER_TO_PAGE_TABLE\n\t"  //CR3 needs to point to the page table
		"mov	%cr3,	%eax\n\t" 
		"mov	%eax,	%cr0\n\t" //Set page enable bit in cr0
		"or	%eax,	0x80000000\n\t"
		"mov 	%cr0,	%eax\n\t"); 
	}

void make_page_directory( 
*/
