#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include "common.h"

//check the argument exists
int check_arg(char *av[], const char *opt)
{
	int count = 0;

	//check all argument
	while(*av != '\0')
	{
		if(!strcmp(av[count], opt))
		{
			return TRUE;
		}

		av++;
	}

	return FALSE;
}


// change the directory
void cmd_cd(int ac, char *av[])
{
	char *path;

	// setting path
	if(ac > 1)
	{
		path = av[1];
	}
	// if only cd order, go to HOME
	else if((path = (char*)getenv("HOME")) == NULL)
	{
		path = ".";
	}
	if(chdir(path) == ERROR)
	{
		fprintf(stderr, "%s: bad directory.\n", path);
	}
}

// exit program
void cmd_exit()
{
	printf("================terminating================\n");
	exit(1);
}

//  print list
void cmd_ls(int ac, char *av[])
{
	DIR *dp;
	struct dirent *entry;
	char *path;
	int count;
	int opt_a;
	int opt_l;

	if(ac < 2)
	{
		path = ".";
	}
	
	else
	{
		path = av[1];
	}

	if((dp = opendir(path)) == NULL)
	{
		fprintf(stderr, "Can't open directory: %s", av[1]);
		return;
	}


	opt_a = check_arg(av, "-a");
	opt_l = check_arg(av, "-l");

	count = 0;


	while((entry = readdir(dp)) != NULL)
	{
		if(!opt_a)
		{
			if(entry->d_name[0] == '.')
			{
				continue;
			}
		}
		
		printf("%s\t", entry->d_name);

		if(opt_l)
		{
			printf("\n");
		}
		

		else
		{
			if(count > 3)
			{
				printf("\n");
				count = 0;
			}
			else
			{
				count++;
			}
		}
	}
	closedir(dp);
	printf("\n");
}

// copy file
void cmd_cp(int ac, char *av[])
{
	FILE *src;
	FILE *dst;
	char ch;

	if(ac < 3)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}

	if((src = fopen(av[1], "r")) == NULL)
	{
		fprintf(stderr, "%s: Can't open file.\n", av[1]);
		return;
	}

	if((dst = fopen(av[2], "w")) == NULL)
	{
		fprintf(stderr, "%s: Can't open file.\n", av[2]);
		return;
	}

	while(!feof(src))
	{
		ch = (char) fgetc(src);

		if(ch != EOF)
		{
			fputc((int)ch, dst);
		}
	}

	if(check_arg(av, "-v"))
	{
		printf("cp %s %s\n", av[1], av[2]);
	}

	fclose(src);
	fclose(dst);
}

// file delete function
void cmd_rm(int ac, char *av[])
{
	if(ac < 2)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}

	unlink(av[1]);

	if(check_arg(av, "-v"))
	{
		printf("rm %s\n", av[1]);
	}
}

// file move function
void cmd_mv(int ac, char *av[])
{
	FILE *src;
	FILE *dst;
	char ch;

	if(ac < 3)
	{
		fprintf(stderr, "Not enough arguments.\n");
		return;
	}

	if((src = fopen(av[1], "r")) == NULL)
	{
		fprintf(stderr, "%s: Can't open file.\n", av[1]);
		return;
	}

	if((dst = fopen(av[2], "w")) == NULL)
	{
		fprintf(stderr, "%s: Can't open file.\n", av[2]);
		return;
	}

	while(!feof(src))
	{
		ch = (char) fgetc(src);

		if(ch != EOF)
		{
			fputc((int)ch, dst);
		}
	}

	fclose(src);
	fclose(dst);

	unlink(av[1]);

	if(check_arg(av, "-v"))
	{
		printf("mv %s %s\n", av[1], av[2]);
	}
}

// make directory
void cmd_mkdir(int ac, char *av[])
{
	mkdir(av[1]);
}

// delete directory
void cmd_rmdir(int ac, char *av[])
{
	rmdir(av[1]);
}

//cat
void cmd_cat(int ac, char *av[])
{
	int ch;
	FILE *fp;

	if(ac < 2)
	{
		fprintf(stderr, "Not enough arguments");
		return;
	}

	if((fp = fopen(av[1], "r")) == NULL)
	{
		fprintf(stderr, "No such file on directory.\n");
		return;
	}

	while((ch = getc(fp)) != EOF)
	{
		putchar(ch);
	}

	fclose(fp);
}

//clr
void cmd_clr()
{
	system("clear");
}

//allsyms
void cmd_allsyms()
{
	system("sudo vi /proc/kallsyms");
}

//help
void cmd_help()
{
	printf("1. cd     : change directory.\n");
	printf("2. exit   : kill program.\n");
	printf("3. ls     : show list.\n");
	printf("4. allsyms: show all symblos in system.\n");
	printf("5. cp     : copy file.\n");
	printf("6. rm     : remove file.\n");
	printf("7. mv     : move file.\n");
	printf("8. mkdir  : make directory.\n");
	printf("9. rmdir  : remove directory.\n");
	printf("10. cat   : cat.\n");
	printf("11. clr   : clear.\n");
	printf("12. date  : show date.\n");
	printf("13. help  : print list of function.\n");
	
}
