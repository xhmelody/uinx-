#include <stdio.h>
#include <sys/types.h>
#include <grp.h> //
#include <pwd.h>  //passwd
#include <unistd.h> //getlogin()
#include <sys/time.h>
#include <sys/resource.h> //getrusage()
#include <stdlib.h>

int main()
{
    char *me, **members;
    struct passwd *my_passwd;
    struct group *my_group;
    me = getlogin();   //获取用户id
    my_passwd = getpwnam(me);
    if (!my_passwd)
        exit(1);
    
    //打印用户信息
    printf("I am %s\n", my_passwd->pw_gecos);
    printf("My login name is %s\n", my_passwd->pw_uid);
    printf("My home directory is %s\n", my_passwd->pw_dir);
    printf("My default shell is %s\n", my_passwd->pw_shell);
    
    //获取默认组ID信息
    my_group = getgrgid(my_passwd->pw_gid);
    if (!my_group)
        exit(1);
    
    //打印组信息
    printf("My default group is %s (%d).\n", my_group->gr_name, (int)(my_passwd->pw_gid));
    members = my_group->gr_mem;
    if (*members)
        printf("The members of this group are:\n");
    else
        printf("no other members in the group\n");
    while (*members)//最后是以null结尾的
    {
        printf("  %s\n", *(members));
        members++;
    }
    return 0;
}
