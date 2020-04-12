#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

// #define _GNU_SOURCE

__ssize_t read(int __fd, void *__buf, size_t __nbytes) {
	// char buf[32];
	// sprintf(stdout, "Calling read: size %ld\n", __nbytes);
	printf("Calling read: size %ld\n", __nbytes);
	static __ssize_t (*real_read)(int, void*, size_t) = NULL;
	if (real_read == NULL) {
		real_read = dlsym(RTLD_NEXT, "read");
	}
	return real_read(__fd, __buf, __nbytes);
}

__ssize_t write(int __fd, const void *__buf, size_t __n) {
	printf("Calling write: size %ld\n", __n);
	static __ssize_t (*real_write)(int, const void*, size_t) = NULL;
	if (real_write == NULL) {
		real_write = dlsym(RTLD_NEXT, "write");
	}
	return real_write(__fd, __buf, __n);
}