#ifndef __DISK_QUOTA
#define __DISK_QUOTA
int statFile(char *directory, Config *config);

void findFiles(char *directory, Config *config);

int main();
#endif
