int (*my_open)(char* path, int param);
int (*my_ioctl)(int fd, int command, void * arg);

int pwmi2c_main(int argc, char *argv[]);