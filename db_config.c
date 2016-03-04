int dbConfig(Config *config, char *file) {
  sqlite3 *db;
  char *zErrMsg = 0;
  int rc = sqlite3_open(file, &db);
  sqlite3_close(db);
}
