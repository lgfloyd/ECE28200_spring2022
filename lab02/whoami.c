#include <unistd.h>
#include <pwd.h>
#include <stdio.h>

int main()
{
uid_t idNum = geteuid();

struct passwd *pwd = getpwuid(idNum);

puts(pwd -> pw_name);
}
