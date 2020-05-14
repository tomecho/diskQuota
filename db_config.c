static int directory_callback(void *data, int argc, char **argv, char **azColName){
  Config *config = (Config *) data;
  strcpy(config->directory, argv[1]);
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
  char *directory_stmt = "SELECT `directory` FROM `web_configs` WHERE `id`=1";
  char *old_stmt = "SELECT `old` FROM `web_configs` WHERE `id`=1";
  char *scan_interval_stmt = "SELECT `scan_interval` FROM `web_configs` WHERE `id`=1";
  
  //read directory
  rc = sqlite3_exec(db,directory_stmt,directory_callback, &config, &zErrMsg);
  if(rc != SQLITE_OK){
    fprintf(stderr, "failed to read database directory: %s \n", zErrMsg);
    sqlite3_free(zErrMsg);
  }
  printf("%s", config->directory);

  // //read old
  // rc = sqlite3_exec(db,old_stmt,directory_callback,(void*)data,&(zErrMsg));
  // if(rc != SQLITE_OK){
  //   fprintf(stderr, "failed to read database old: %s \n",zErrMsg);
  //   sqlite3_free(zErrMsg);
  // }
  
  // //read scan_interval
  // rc = sqlite3_exec(db,scan_interval_stmt,directory_callback,(void*)data,&(zErrMsg));
  // if(rc != SQLITE_OK){
  //   fprintf(stderr, "failed to read database scan_interval: %s \n", zErrMsg);
  //   sqlite3_free(zErrMsg);
  // }

  sqlite3_close(db);
  return 1;
}
