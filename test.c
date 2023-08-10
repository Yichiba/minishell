#include <unistd.h>

int main()
{
    while (1)
    {
        sleep(1);
        system("leaks minishell");
    }
    return (1);
}