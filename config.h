#ifndef __CONFIG
#define __CONFIG
#define CONFIG_FILE "config"

//typedef struct config Config;
typedef struct config {
  long scan_interval; 
  long old;
  char directory[255];
} Config;

//typedef enum confType confType;
typedef enum confType {db,file} confType;

confType checkConfType();

int readConf(Config *config);
#endif
