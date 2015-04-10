#pragma once

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <error.h>

struct i2c_dev_s {};
struct pwm_info_s { int frequency, duty; };
struct pwm_lowerhalf_s{};

void *(*sam_pwminitialize)(int);
long  (*ioctl)(int, int, void*);
long  (*pwm_devinit)(void);
long  (*pwm_register)(const char*, struct pwm_lowerhalf_s *a);
void *(*up_i2cinitialize)(int);
long  (*I2C_SETADDRESS)(struct i2c_dev_s *, int, int);
long  (*I2C_SETFREQUENCY)(struct i2c_dev_s *, int);
long  (*I2C_WRITE)(struct i2c_dev_s *, void*, int);
long  (*up_i2cuninitialize)(struct i2c_dev_s *);

int pwm_init(struct pwm_lowerhalf_s **dev);
int pwmi2c_main(int argc, char *argv[]);
void hello();
int mock_open(char* path, int param);
int mock_ioctl(int fd, int command, void * arg);