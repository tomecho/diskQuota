#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

typedef struct config {
  long scan_interval; 
  long old;
  char directory[255];
} Config;

int readConf(Config *config) {
  /*
  if(!access("/etc/diskQuota.conf", F_OK)){ //conf doesnt exist try to create it
    FILE *f = fopen("/etc/diskQuota.conf","w+");  //config file
    printf("Failed to open config file!\n");
    printf("Using default settings.\n");

    config.scan_interval = 120;
    fputs(f, "scan_interval=120");

    config.old = 86400;
    fputs(f, "old=120");

    config.directory = "/dev/null"; 
    fputs(f, "directory=/dev/null");
    return 0;
  }*/
  FILE *f = fopen("config","r");  //config file
  if(f == NULL) {
    printf("Failed to open config file!\n");
    config.scan_interval = 120;
    config.old = 86400;
    config.directory = "/dev/null"; 
    return 0;
  } else { //read config
    char line[1024];
    while( fgets(line, 1024, f) != NULL){
      char *part
      if(strstr(line, "scan_interval") != NULL){
        part = strstr(line, "=");
        part++;
        printf("%s", part)
      }
      if((part = strstr(line, "old")) != NULL){
        
      }
      if((part = strstr(line, "directory")) != NULL){
        
      }
    }
  }
  fclose(conf);
  return(1);
}

int statFile(char *directory) {
  struct stat st;
  struct timespec t = {0, 0};
  if(stat(directory,&st) == 0)
  {
    t.tv_sec = st.st_mtime;
  } else return 666; //failure status
  if(difftime(t.tv_sec,(time(NULL)-config.old)) < 0)
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
  Config config;
  if(!readConf(config)) return 0;
  //while(1) {
  //  findFiles(config.directory);
  //  sleep(config.scan_interval);
  //}
  return(0x0);
}
