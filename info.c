#include <stdio.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

int main()
{
	pid_t my_pid, my_ppid;
	pid_t my_uid, my_euid;
	pid_t my_gid, my_egid;
	struct passwd* info;
	my_pid = getpid();
	my_ppid = getppid();
	my_uid = getuid();
	my_euid = geteuid();
	my_gid = getgid();
	my_egid = getegid();

	printf("pid = %ld\n", my_gid);
	printf("ppid = %ld\n", my_ppid);
	printf("uid = %ld\n", my_uid);
	printf("euid = %ld\n", my_euid);
	printf("gid = %ld\n", my_gid);
	printf("egid = %ld\n", my_egid);


	info = getpwuid(my_uid);
	if (info){
		printf("my login name : %s\n", info->pw_name);
		printf("my login passwd : %s\n", info->pw_passwd);
		printf("my user id : %ld\n", info->pw_uid);
		printf("my group id : %ld\n", info->pw_gid);
		printf("my real name : %s\n", info->pw_gecos);
		printf("my home dir : %s\n", info->pw_dir);
		printf("my work shell : %s\n", info->pw_shell);
	}

	return 0;
}
