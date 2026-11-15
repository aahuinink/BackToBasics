#include <stddef.h>
void *memcpy(void *dest, const void *src, size_t n) {
	for (size_t i = 0; i < n; i++) {
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
	}
	return dest;
}

void *memset(void *s, int c, size_t n) {
	for (size_t i = 0; i < n; i++) {
		((unsigned char *)s)[i] = c;
	}
	return s;
}

