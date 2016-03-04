#define CONFIG_FILE "config"

typedef struct config Config;

typedef enum confType confType;

int validConf(Config *conf);

confType checkConfType();

int readConf(Config *config) ;
