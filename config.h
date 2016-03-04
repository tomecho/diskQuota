#define CONFIG_FILE "config"


typedef struct config;

typedef enum confType {db,file} confType;

int validConf(Config *conf);

confType checkConfType();

int readConf(Config *config) ;
