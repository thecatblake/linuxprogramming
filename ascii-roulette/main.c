#include <unistd.h>
#include <fcntl.h>

int main()
{
    char c = 31;
    while(1)
    {
        write(1, "\r", 1);
        c = 31 + ((c + 1 - 31) % (127 - 31));
        write(1, &c, 1);
    }
}