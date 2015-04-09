#include "pwm_mock.h"

#define PWM_DEVPATH "/dev/pwm0"

#define O_RDONLY 2
#define PWMIOC_START 0
#define PWMIOC_STOP 1
#define PWMIOC_SETCHARACTERISTICS 2
#define FAR


int pwm_init(struct pwm_lowerhalf_s **dev)
{
	if(pwm_devinit() != 0) return 2;
	*dev = sam_pwminitialize(0);
	if(!*dev) return 1;
	return pwm_register(PWM_DEVPATH, *dev);
}

static void help(char *s)
{
	printf("%s: %s { -f <fréquence> -d <duty cycle> | -l <message lcd> | -s }\n"
		   "-f\tFréquence du PWM\n"
		   "-d\tDuty cycle du PWM\n"
		   "-s\tDésactive le PWM\n"
		   "-l\tÉcrit sur l'écran LCD esclave 0x20, la chaine passé en paramètre\n", s, s);
}

int pwmi2c_main(int argc, char *argv[])
{
	struct pwm_lowerhalf_s *dev;
	if(argc == 1) help(argv[0]);

	int opt, flag = 0;
	int freq = 0, dc = 0;

	while((opt = getopt(argc, argv, "f:d:l:s")) != -1)
	{
		int fd;
		switch(opt)
		{
		case 'f':
			freq = atoi(optarg);
			flag |= 1;
			break;
		case 'd':
			dc = atoi(optarg);
			flag |= 2;
			break;
		case 's':
			fd = open(PWM_DEVPATH, O_RDONLY);
			if(ioctl(fd, PWMIOC_STOP, 0) != 0)
				puts("ioctl a échoué");
			return 0;
		case 'l':
			if(strlen(optarg) > 20)
			{
				puts("Message trop long");
				return 2;
			}

			FAR struct i2c_dev_s *i2c = up_i2cinitialize(0);
			I2C_SETFREQUENCY(i2c, 100000);
			I2C_SETADDRESS(i2c, 0x20, 7);
			I2C_WRITE(i2c, (void*) optarg, strlen(optarg));
			up_i2cuninitialize(i2c);
			return 0;
		default:
			help(argv[0]);
			return 3;
		}
	}

	if(flag & 3) // Les 2 arguments sont requis
	{
		int a;
		if(pwm_init(&dev) != 0)
		{
			puts("Erreur d'initialisation du pwm");
			return 1;
		}
		puts("Initialisation du pwm reussie");
		
		int fd = open(PWM_DEVPATH, O_RDONLY);
		struct pwm_info_s info;
		info.frequency = freq;
		info.duty = ((unsigned)dc << 16) / 100;
		if(ioctl(fd, PWMIOC_SETCHARACTERISTICS, &info) != 0)
		{
			puts("ioctl a échoué");
			return 1;
		}
		if(ioctl(fd, PWMIOC_START, 0) != 0)
		{
			puts("ioctl a échoué");
			return 1;
		}
	}
	return 0;
}


/*
  Je pense que théoriquement, ce programme devrait marcher, ce qui veut
  dire que la carte prendra feu dans la pratique.
*/

/*
  Fonction écrites:
  help
  pwmi2c_main
  pwm_init

  Fonction utilisée:
  pwm_devinit
  sam_pwminitialize
  pwm_register
  getopt
  atoi // qui a l'air d'etre un #define de strtol
  open
  ioctl
  puts
  printf
  strlen
  up_i2cinitialize
  I2C_SETADDRESS
  I2C_SETFREQUENCY
  I2C_WRITE
  up_i2cuninitialize

  A mocker peut etre: 
  ioctl
  pwm_devinit
  sam_pwminitialize
  pwm_register
  
 */
