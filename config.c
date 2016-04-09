int validConf(Config *conf){
  if(!conf->scan_interval) return 0;
  if(!conf->old) return 0;
  if(!conf->directory) return 0;
  return 1;
}

confType checkConfType(){
  FILE *f = fopen(CONFIG_FILE,"r");  //config file
  char line[1024];
  while( fgets(line, 1024, f) != NULL){
    char *part;
    if(strstr(line, "db") != NULL){
      return db;
    }
  }
  fclose(f);
  return file;
}

int readConf(Config *config) {
  if(!access("/etc/diskQuota.conf", F_OK)){ //conf doesnt exist try to create it
    FILE *f = fopen(CONFIG_FILE,"w+");  //config file
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
  } else {
    confType ct = checkConfType();
    if(ct == db){
      dbConfig(config,"development.sqlite3");
      if(validConf(config) == 0){
        printf("failed to read database, falling back to file");
      }
    }
    if(ct == file){
      FILE *f = fopen("config","r");  //config file
      if(f == NULL) {
        printf("Failed to open config file!\n");
        return 0;
      }
      char line[1024];
      while( fgets(line, 1024, f) != NULL){
        char *part;
        if(strstr(line, "scan_interval") != NULL){
          part = strstr(line, "=");
          part++;
          config->scan_interval= atol(part);
        }
        if((part = strstr(line, "old")) != NULL){
          part = strstr(line, "=");
          part++;
          config->old= atol(part);
        }
        if((part = strstr(line, "directory")) != NULL){
          part = strstr(line, "=");
          part++;
          strcpy(config->directory, part);
        }
      }
      fclose(f);
    }
  }
  return(1);
}

