#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<pwd.h>
#include<time.h>
#include<grp.h>

int get_file_type(struct stat* st)
{
	if(S_ISREG(st->st_mode)) printf("-");
    else if(S_ISDIR(st->st_mode)) printf("d");
    else if(S_ISCHR(st->st_mode)) printf("c");
    else if(S_ISBLK(st->st_mode)) printf("b");
    else if(S_ISSOCK(st->st_mode)) printf("s");
    else if(S_ISFIFO(st->st_mode)) printf("p");
    else if(S_ISLNK(st->st_mode)) printf("l");
	else printf("-");
  
    return 0;
}
int get_owner_permission(struct stat* st)
{
	if(st->st_mode & S_IRUSR) printf("r");
	else printf("-");

	if(st->st_mode & S_IWUSR) printf("w");
	else printf("-");

	if(st->st_mode & S_IXUSR) printf("x");
	else printf("-");

	return 1;
}

int get_group_permission(struct stat* st)
{   
    if(st->st_mode & S_IRGRP) printf("r");
    else printf("-");

    if(st->st_mode & S_IWGRP) printf("w");
    else printf("-");

    if(st->st_mode & S_IXGRP) printf("x");
    else printf("-");
	
	return 1;
}

int get_other_permission(struct stat* st)
{   
    if(st->st_mode & S_IROTH) printf("r");
    else printf("-");

    if(st->st_mode & S_IWOTH) printf("w");
    else printf("-");

    if(st->st_mode & S_IXOTH) printf("x");
    else printf("-");

	return 1;
}

int get_username(struct stat* st)
{
	char* fileUser = getpwuid(st->st_uid)->pw_name;
	printf("%s ", fileUser);
	return 1;
}

int get_grpname(struct stat* st)
{
	char* filegrp = getgrgid(st->st_gid)->gr_name;
	printf("%s ", filegrp);
	return 1;
}

int get_time(time_t* t)
{
	char* cur_time = ctime(t);
	for(int i = 0; i < 16; i++)
	{
		putchar(cur_time[i]);
	}
	return 1;
}
int main(int argc, char** argv)
{
	
	int ret = -1;
	struct stat st;

	if(2 != argc)
	{
		printf("usage: ./a.out filename\n");
		return 1;
	}

	ret = stat(argv[1], &st);

	if(-1 == ret)
	{
		perror("stat");
		return 1;
	}

	get_file_type(&st);
	get_owner_permission(&st);
	get_group_permission(&st);
	get_other_permission(&st);
	printf(" %lu ", st.st_nlink);
	get_username(&st);
	get_grpname(&st);
	printf("%lu ", st.st_size);
	get_time(&st.st_mtime);
	printf(" %s\n", argv[1]);
	return 0;
}

