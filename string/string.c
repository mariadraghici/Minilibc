// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	char *start = destination;

	if (start == NULL) {
		return NULL;
	}

	for (; *source != '\0'; source++, start++) {
		*start = *source;
	}
	*start = '\0';
	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	char *start = destination;
	size_t i = 1;

	if (start == NULL) {
		return NULL;
	}

	for (; *source != '\0' && i <= len; source++, start++, i++) {
		*start = *source;
	}

	*start = *source;
	i--;

	if (*source == '\0' && i != len) {
		for (; i <= len; i++, start++) {
			*start = '\0';
		}
	}
	return destination;
}

char *strcat(char *destination, const char *source)
{
	char *start = destination;
	char *aux_source = (char *)source;

	for (; *start != '\0'; start++)
		;
	
	for (; *aux_source != '\0'; aux_source++, start++) {
		*start = *aux_source;
	}
	*start = '\0';
	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	char *start = destination;
	char *aux_source = (char *)source;
	size_t i = 1;

	for (; *start != '\0'; start++)
		;
	
	for (; *aux_source != '\0' && i <= len; aux_source++, start++, i++) {
		*start = *aux_source;
	}
	*start = '\0';
	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	if (strlen(str1) > strlen(str2)) {
		return 1;
	} else if (strlen(str1) == strlen(str2)) {
		for (; *str1 != '\0' && *str2 != '\0'; str1++, str2++) {
			unsigned char value1 = *str1;
			unsigned char value2 = *str2;
			if (*str1 != *str2) {
				return value1 - value2;
			}
		}

		if (*str1 == *str2 && *str1 == '\0') {
			return 0;
		}
	}
	return -1;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	size_t i = 1;
	for (; *str1 != '\0' && *str2 != '\0' && i <= len; str1++, str2++, i++) {
		unsigned char value1 = *str1;
		unsigned char value2 = *str2;
		if (*str1 != *str2) {
			return value1 - value2;
		}
	}

	if (i == len + 1) {
		return 0;
	}
	return -1;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	char *start = (char *)str;
	for (; *start != '\0'; start++) {
		if (*start == c) {
			return start;
		}
	}
	return NULL;
}

char *strrchr(const char *str, int c)
{
	char *start = (char *)str;
	char *point;
	int ok = 0;

	for (; *start != '\0'; start++) {
		if (*start == c) {
			point = start;
			ok = 1;
		}
	}
	if (ok == 1) {
		return point;
	}
	return NULL;
}

char *strstr(const char *haystack, const char *needle)
{
	char *aux2 = (char *)needle;
	char *aux1 = (char *)haystack;

	int size = 0;
    int i = 0;

    int len1 = strlen(haystack);
    int len2 = strlen(needle);
    int l1 = 0, l2 = 0;

	while (l1 < len1 && l2 < len2) {
		if (*aux1 != *aux2) {
			i++;
			aux1 = (char *)(haystack + i);
            l1 = i;
            l2 = 0;
			aux2 = (char *)needle;
			size = 0;
        } else {
			aux1++;
			aux2++;
            l1++; l2++;
			size++;
		}
	}

	if (*aux2 == '\0') {
		return (char *)(haystack + i);
	}
	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	char *aux2 = (char *)needle;
	char *aux1 = (char *)haystack;
	int size = 0;
    int i = 0;

    int len1 = strlen(haystack);
    int len2 = strlen(needle);
    int l1 = 0, l2 = 0;
    char *result;
    int ok = 0;

	while (l1 < len1) {
		if (*aux1 != *aux2) {
			i++;
			aux1 = (char *)(haystack + i);
            l1 = i;
            l2 = 0;
			aux2 = (char *)needle;
			size = 0;
        } else {
            if (l2 == len2 - 1) {
                result = (char *)(haystack + i);
                ok = 1;
            }
			aux1++;
			aux2++;
            l1++; l2++;
			size++;
		}
	}

	if (ok == 1) {
		return result;
	}
	return NULL;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	char *start = (char *)destination;
	char *src = (char *)source;

	if (start == NULL) {
		return NULL;
	}

	for (size_t i = 0; i < num; i++) {
		start[i] = src[i];
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	char *dest = (char *)destination;
	char *src = (char *)source;
	char aux[num];

	for (size_t i = 0; i < num; i++) {
		aux[i] = src[i];
	}

	for (size_t i = 0; i < num; i++) {
		dest[i] = aux[i];
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	char *aux1 = (char *)ptr1;
	char *aux2 = (char *)ptr2;

	if (num == 0) {
		return 0;
	}

	for (size_t i = 0; i < num; aux1++, aux2++, i++) {
		unsigned char value1 = *aux1;
		unsigned char value2 = *aux2;
		if (*aux1 != *aux2) {
			return value1 - value2;
		}
	}

	return 0;

	return -1;
}

void *memset(void *source, int value, size_t num)
{
	char *src = (char *)source;
	unsigned char c = (unsigned char)value;

	for (size_t i = 0; i < num; i++) {
		src[i] = c;
	}
	return source;
}
