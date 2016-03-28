diskQuota: diskQuota.c config.c db_config.c
	gcc -std=c11 diskQuota.c -o bin/diskQuota
v: diskQuota.c config.c db_config.c
	gcc -std=c11 diskQuota.c -o bin/diskQuota -v
clean:
	rm bin/*
