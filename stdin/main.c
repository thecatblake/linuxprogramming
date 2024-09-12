#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    char buf[1000];
    int i = read(0, buf, 1000);
    int fd = open("/dev/tty", O_WRONLY);
    write(fd, buf, 1000);
}