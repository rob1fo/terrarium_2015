#include "pwmi2c_main.h"
#include "test/pwm_mock.h"

int (*my_open)(char* path, int param);
int (*my_ioctl)(int fd, int command, void * arg);

int main(int argc, char *argv[])
{
	my_ioctl = &mock_ioctl;
	my_open = &mock_open;
	pwmi2c_main(argc, argv);
}