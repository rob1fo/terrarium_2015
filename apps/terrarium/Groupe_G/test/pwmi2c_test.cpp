#include "CppUTest/TestHarness.h"
#include <cassert>
int flags = 0;

extern "C"
{
#include "pwm_mock.h"
}

long mocker(...)
{
	int tmp = flags & 1;
	flags >>= 1;
	return tmp;
}

void* pmocker(...)
{
	return (void*)(long)mocker();
}

TEST_GROUP(pwmi2c)
{
	void setup()
	{
		sam_pwminitialize	= (void *(*) (int))pmocker;
		ioctl				= (long(*)(int, int, void*))mocker;
		pwm_devinit			= (long(*)(void))mocker;
		pwm_register		= (long(*)(const char *, struct pwm_lowerhalf_s *))mocker;
		up_i2cinitialize	= (void *(*)(int))pmocker;
		I2C_SETADDRESS		= (long(*)(struct i2c_dev_s *, int, int))mocker;
		I2C_SETFREQUENCY	= (long(*)(struct i2c_dev_s *, int))mocker;
		I2C_WRITE			= (long(*)(struct i2c_dev_s *, void*, int))mocker;
		up_i2cuninitialize	= (long(*)(struct i2c_dev_s *))mocker;

	}

	void teardown() 
	{
	}
};

// Teste toute les possibilité pour pwm_init
TEST(pwmi2c, allInit)
{
	// 3 appels mocké, 8 possibilité
	
	struct pwm_lowerhalf_s *dev;
	for(int i = 0; i < 8; ++i)
	{
		int expect;
		flags = i;
		if(flags & 0x1) expect = 2;
		else if(~flags & 0x2) expect = 1;
		else expect = !!(flags & 0x4);
		CHECK_EQUAL(expect, pwm_init(&dev));
	}
}

// Teste toute les possibilité pour pwmi2c_main
TEST(pwmi2c, testPwmStart)
{
	// 5 appels mocké, 32 possibilité
	char *argv[] =
		{
			"lel", "-f", "100000", "-d", "500", NULL
		};
	int argc = 5;

	struct pwm_lowerhalf_s *dev;
	for(int i = 0; i < 32; ++i)
	{
		int expect = 42;
		flags = i;

		if(flags & 0x10) expect = 1;
		else if(flags & 0x8 && flags & 0x2) expect = 1;
		else if((flags & 0x7) == 0x02) expect = 0;
		else expect = 1;

		CHECK_EQUAL(expect, pwmi2c_main(argc, argv));
		optind = 1;
	}
}


TEST(pwmi2c, testPwmStop)
{
	// 5 appels mocké, 32 possibilité
	char *argv[] =
		{
			"lel", "-s", NULL
		};
	int argc = 2;

	CHECK_EQUAL(0, pwmi2c_main(argc, argv));
	optind = 1;
}

TEST(pwmi2c, testi2cPrint)
{
	// 5 appels mocké, 32 possibilité
	char *argv[] =
		{
			"lel", "-l", "lel", NULL
		};
	int argc = 3;

	CHECK_EQUAL(0, pwmi2c_main(argc, argv));
	optind = 1;

}

TEST(pwmi2c, testi2cPrintLarge)
{
	// 5 appels mocké, 32 possibilité
	char *argv[] =
		{
			"lel", "-l", "ledsfsdfsdfsdffsdsfdsdfsfsdsfdl", NULL
		};
	int argc = 3;

	CHECK_EQUAL(2, pwmi2c_main(argc, argv));
	optind = 1;

}


