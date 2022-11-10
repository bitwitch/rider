#ifndef __IO_H__
#define __IO_H__

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *data;
    size_t len;
    bool is_valid;
} File;

File io_file_read(const char *path);
int io_file_write(void *buffer, size_t size, const char *path);

#endif
