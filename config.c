typedef struct config {
  long scan_interval; 
  long old;
  char directory[255];
} Config;

int readConf(Config *config) {
  if(!access("/etc/diskQuota.conf", F_OK)){ //conf doesnt exist try to create it
    FILE *f = fopen("/etc/diskQuota.conf","w+");  //config file
    printf("Failed to open config file!\n");
    printf("Using default settings.\n");

    config->scan_interval = 120;
    fputs("scan_interval=120", f);

    config->old = 86400;
    fputs("old=120",f);

    strcpy(config->directory,"/dev/null"); 
    fputs("directory=/dev/null", f);
    fclose(f);
    return 0;
  }
  FILE *f = fopen("config","r");  //config file
  if(f == NULL) {
    printf("Failed to open config file!\n");
    config->scan_interval = 120;
    config->old = 86400;
    strcpy(config->directory ,"/dev/null"); 
    return 0;
  } else { //read config
    char line[1024];
    while( fgets(line, 1024, f) != NULL){
      char *part;
      if(strstr(line, "scan_interval") != NULL){
        part = strstr(line, "=");
        part++;
        config->scan_interval= (long) part;
        printf("%s", part);
      }
      if((part = strstr(line, "old")) != NULL){
        part = strstr(line, "=");
        part++;
        config->old= (long) part;
        printf("%s", part);
      }
      if((part = strstr(line, "directory")) != NULL){
        part = strstr(line, "=");
        part++;
        strcpy(config->directory, part);
        printf("%s", part);
      }
    }
  }
  fclose(f);
  return(1);
}
