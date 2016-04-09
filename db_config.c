int dbConfig(Config *config, char *file) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc = sqlite3_open(file, &db);
  if( rc ){
    fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
    return 0;
  }else{
    fprintf(stderr, "Opened database successfully\n");
  }
  char *directory_stmt = "SELECT `directory` FROM `web_configs` WHERE `id`=1";
  char *old_stmt = "SELECT `old` FROM `web_configs` WHERE `id`=1";
  char *scan_interval_stmt = "SELECT `scan_interval` FROM `web_configs` WHERE `id`=1";
  sqlite3_close(db);
  return 1;
}
