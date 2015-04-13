#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

struct config {
	time_t scan_interval;
	time_t old;
	char directory;
};

int readConf() { //lets impement this later
	FILE *conf;
	conf = fopen("/etc/diskQuota.conf","r");  //config file
	fclose(conf);
	return(0);
}

int statFile(char *directory) {
	struct stat st;
	struct timespec t = {0, 0};
	if(stat(directory,&st) == 0)
	{
		t.tv_sec = st.st_mtime;
	} else return 666; //failure status
	if(difftime(t.tv_sec,(time(NULL)-old)) < 0)
	{
		return unlink(directory);
	} else {
		return 111; //no need to delete it
	}
}

void findFiles(char *directory)
{
	DIR *d;
	struct dirent *dir;
	d= opendir(directory);
	char *name;
	if(d)
	{
		while( ( dir=readdir(d) ) != NULL) 
		{
			name = dir->d_name;
			if(strcmp(name,".") == 0) continue; //dont check this dir again 
			if(strcmp(name,"..") == 0) continue; //also dont go up that would be dumb as well
			char type = dir->d_type;
			if(type == DT_DIR) //test directory
			{ //is directory
				char *deeperDirectory=(char*)malloc(sizeof(char)*256);
				strcpy(deeperDirectory,directory);
				strcat(deeperDirectory, "/");
				strcat(deeperDirectory, name);
				//printf("search, %s\n",deeperDirectory);
				findFiles(deeperDirectory);
				free(deeperDirectory);
			} else if(type == DT_REG) {  //is file
				char *toStat=(char*)malloc(sizeof(char)*256);
				strcpy(toStat, directory);
				strcat(toStat,"/");
				strcat(toStat,name);
				statFile(toStat);
				//printf("stat, %s\n", toStat);
				free(toStat);
			} else {
				printf("dirent type error");
				continue;
			}
		}
	}
	closedir(d);
	return;
}

int main()
{  //find old files and delete them, first go into directories and read find all video files
	while(1) {
		findFiles("/home/tom/torrents/outgoing");
		sleep(120);
	}
	return(0x0);
}