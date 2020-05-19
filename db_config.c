static int callback(void *data, int argc, char **argv, char **azColName){
  Config *config = (Config *) &data;
  sprintf(config->directory, "%s", argv[0]);
  config->old = argv[1];
  config->scan_interval = argv[2];
  printf("%s", config->directory);
  return 0;
}

int dbConfig(Config *config, char *file) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc = sqlite3_open(file, &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return 0;
  }
  char *stmt = "SELECT `directory`, `old`, `scan_interval` FROM `web_configs` WHERE `id`=1";
  
  rc = sqlite3_exec(db, stmt, callback, config, &zErrMsg);
  if(rc != SQLITE_OK){
    fprintf(stderr, "failed to read database directory: %s \n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  printf("%s", config->directory);

  sqlite3_close(db);
  return 1;
}
