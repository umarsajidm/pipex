#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void test(char *str)
{
    unsigned int i;
    
    i = 0;
    while(str[i])
        i++;
    while(i--)
    {
        write(1, &str[i], 1);
    }
    write(1, "\n", 1);
}
int main(int argc, char *argv[])
{
    if (argc < 2 || argc > 2)
        return (write(1, "\n", 1));
    int i = 0;
    test(argv[1]);
    return 0;
}
