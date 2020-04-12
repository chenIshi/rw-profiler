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

/*
void *malloc(size_t size) {
    char buf[32];
    static void *(*real_malloc)(size_t) = NULL;
    if (real_malloc == NULL) {
        real_malloc = dlsym(RTLD_NEXT, "malloc");
    }
    sprintf(buf, "malloc called, size = %zu\n", size);
    write(2, buf, strlen(buf));
    return real_malloc(size);
}
*/