#include <sys/reboot.h>
#include <stdio.h>

int main()
{
    reboot(RB_AUTOBOOT);
}