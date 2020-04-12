#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <dlfcn.h>

#include <sys/time.h>

int read_count = 0;
int write_count = 0;

__ssize_t read(int __fd, void *__buf, size_t __nbytes) {
	struct timeval start, end;
	read_count ++;
	static __ssize_t (*real_read)(int, void*, size_t) = NULL;
	if (real_read == NULL) {
		real_read = dlsym(RTLD_NEXT, "read");
	}
	gettimeofday(&start, NULL);
	__ssize_t ret = real_read(__fd, __buf, __nbytes);
	gettimeofday(&end, NULL);

	long second = (end.tv_sec - start.tv_sec);
	long micros = ((second * 1000000) + end.tv_usec - start.tv_usec);
	printf("Calling read no.%d: size %ld, consumed time: %ld us\n", read_count, __nbytes, micros);
	return ret;
}

__ssize_t write(int __fd, const void *__buf, size_t __n) {
	struct timeval start, end;
	write_count ++;
	static __ssize_t (*real_write)(int, const void*, size_t) = NULL;
	if (real_write == NULL) {
		real_write = dlsym(RTLD_NEXT, "write");
	}

	gettimeofday(&start, NULL);
	__ssize_t ret = real_write(__fd, __buf, __n);
	gettimeofday(&end, NULL);

	long second = (end.tv_sec - start.tv_sec);
	long micros = ((second * 1000000) + end.tv_usec - start.tv_usec);
	printf("Calling write no.%d: size %ld, consumed time: %ld us\n", read_count, __n, micros);
	return ret;
}