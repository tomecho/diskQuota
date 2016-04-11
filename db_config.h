#ifndef __DB_CONFIG
#define __DB_CONFIG
int dbConfig(Config *config, char *file);
static int directory_callback(void *data, int argc, char **argv, char **azColName);
#endif
