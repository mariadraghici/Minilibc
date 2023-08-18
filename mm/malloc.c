// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
void *malloc(size_t size)
{
	if (size != 0) {
		void *p = mmap(NULL, size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
		if (p == MAP_FAILED) {
			return NULL;
		}
		mem_list_add(p, size);
		return mem_list_head.prev->start;
	}
	return NULL;
}

void *calloc(size_t nmemb, size_t size)
{
	if (size != 0) {
		mem_list_add(mmap(NULL, nmemb * size, PROT_READ | PROT_WRITE,
		MAP_PRIVATE | MAP_ANONYMOUS, -1, 0), nmemb * size);
		for (size_t i = 0; i < nmemb * size; i++) {
			((char *)(mem_list_head.prev->start))[i] = 0;
		}
		return mem_list_head.prev->start;
	}
	return NULL;
}

void free(void *ptr)
{
	struct mem_list *item;
	
	item = mem_list_find(ptr);
	int l = item->len;
	mem_list_del(ptr);
	munmap(ptr, l);
}

void *realloc(void *ptr, size_t size)
{
	if (ptr == NULL && size != 0) {
		return malloc(size);
	} else if (size == 0 && ptr != NULL) {
		free(ptr);
	} else if (size != 0 && ptr != NULL) {
		struct mem_list *item;
		item = mem_list_find(ptr);

		void *new = malloc(item->len + size);
		char *n = (char *)new;
		char *s = (char *)(item->start);
		for (size_t i = 0; i < item->len; i++) {
			*n = *s;
			n++; s++;
			i++;
		}

		return new;
	}
	return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	void *new = realloc(ptr, nmemb * size);
	if (new != NULL) {
		return new;
	}
	errno = ENOMEM;
	return NULL;
}
