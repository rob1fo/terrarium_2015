#include "pwm_mock.h"

int mock_ioctl(int fd, int command, void * arg){
	puts("ioctl");
	return 0;
};

int mock_open(char* path, int param){
	puts("open");
	return 0;
}