#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(void)
{
    char buf[100];
    int fd = open("/proc/mydev", O_RDONLY);

    if (fd < 0) {
        perror("Cannot open /proc/mydev");
        return -1;
    }

    if (read(fd, buf, sizeof(buf)) > 0) {
        puts(buf);
    } else {
        perror("Failed to read");
    }

    close(fd);

    return 0;
}
