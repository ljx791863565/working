#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main(int argc, char *argv[])
{
	char *ptr; 
	char **pptr;
	struct hostent *hptr;

	char str[32] = {'\0'};
	ptr = argv[1];

	if ((hptr = gethostbyname(ptr))  == NULL){
		perror("gethostbyname");
		return -1;
	}

	printf("host name :%s\n", hptr->h_name);

	for (pptr = hptr->h_aliases; *pptr != NULL; pptr++){
		printf("alias : %s\n", *pptr);
	}

	if (hptr->h_addrtype == AF_INET || hptr->h_addrtype == AF_INET6){
		pptr = hptr->h_addr_list;
		for (; *pptr != NULL; pptr++){
			printf("address: %s\n", inet_ntop(hptr->h_addrtype, *pptr, str, sizeof(str)));
		}
		printf("first address : %s\n", inet_ntop(hptr->h_addrtype, hptr->h_addr_list[0], str, sizeof(str)));
	}else {
		printf("unknows address\n");
	}
	return 0;

}
