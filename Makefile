diskQuota: diskQuota.c config.c db_config.c
	gcc -g -Ilib -lsqlite3 -D_BSD_SOURCE -std=c11 diskQuota.c -o bin/diskQuota
clean:
	rm bin/*
