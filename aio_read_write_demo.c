#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <aio.h>
#include <errno.h>

int main()
{
    // 打开文件
    int fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // allocate I/O block and buffer
    struct aiocb aio;
    char buffer[256];
    memset(&aio, 0, sizeof(struct aiocb));
    aio.aio_fildes = fd;
    aio.aio_buf = buffer;
    aio.aio_nbytes = sizeof(buffer);

    if (aio_read(&aio) == -1) {
        perror("aio_read");
        return 1;
    }

    // wait aio read done
    while (aio_error(&aio) == EINPROGRESS);
    
    // get result
    ssize_t bytes_read = aio_return(&aio);
    if (bytes_read == -1) {
        perror("read");
        return 1;
    }
    printf("Read %zd bytes: %s\n", bytes_read, buffer);

    // 关闭文件
    close(fd);

    return 0;
}
