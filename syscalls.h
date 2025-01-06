int read(int fd, const char *buf, int n);
int write(int fd, const char *buf, int n);
int open(const char *name, int flags, ...);
void close(int fd);
void unlink(const char *name);