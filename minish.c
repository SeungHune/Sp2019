#include <stdio.h>
#include "common.h"

// main function
int main()
{
	printf("==============operating shell==============\n");
	int pid, fd;
	SYMBOL term;

	// print prompt
	print_prompt();

	//loop and take order
	while (TRUE)
	{
		term = parse(&pid, FALSE, NULL);
		if (term != S_AMP && pid != 0)
		{
			waitfor(pid);
		}
		
		if (term == S_NL)
		{
			print_prompt();
		}
		for (fd=3; fd<MAXFD; fd++)
		{
			close(fd);
		}
	}
}
