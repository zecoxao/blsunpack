// Copyright 2010       Sven Peter <svenpeter@gmail.com>
// Copyright 2011       glevand <geoffrey.levand@mail.ru>
// Licensed under the terms of the GNU GPL, version 2
// http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt
// Modified to accept BLS entries

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include "tools.h"

#ifdef WIN32
#define MKDIR(x,y) mkdir(x);
#else
#define MKDIR(x,y) mkdir(x,y)
#endif

static u8 *bls = NULL;

static void new_dir(const char *n)
{
	MKDIR(n, 0777);
	if (chdir(n) < 0)
		fail("chdir");
}

unsigned int block_size = 0x200;


static void do_toc(u8 *ptr)
{
	u32 n_entries;
	u32 i;
	u32 pos = 0;
	u32 pos2 = 0;
	u8 *p;
	u8 *tmp;
	u32 size;
	char name[0x20];

	n_entries = *(u32*)(ptr + 0x0C);
	printf("n_entries:%x\n", n_entries);
	p = ptr + 0x20;

	for(i = 0; i < n_entries; i++) {
		memcpy(name, p + 16, 0x20);

		pos = *(u32*)(p);
		printf("pos:%x\n",pos);
		pos2 = pos * block_size;
		tmp = ptr + pos2;
		size = *(u32*)(p + 0x04);
		printf("size:%x\n",size);

		memcpy_to_file(name, tmp, size);

		p += 0x30;
	}
}

int main(int argc, char *argv[])
{
	if (argc != 3)
		fail("usage: blsunpack dump.b directory");

	bls = mmap_file(argv[1]);

	new_dir(argv[2]);

	do_toc(bls);

	return 0;
}