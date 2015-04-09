#include <arch/board/board.h>
#include <nuttx/config.h>
#include <nuttx/pwm.h>
#include <nuttx/i2c.h>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <errno.h>

#define PWM_DEVPATH "/dev/pwm0"

FAR struct pwm_lowerhalf_s *sam_pwminitialize(int channel);

static int pwm_init(struct pwm_lowerhalf_s **dev)
{
	if(pwm_devinit() != 0) return 2;
	*dev = sam_pwminitialize(0);
	if(!*dev) return 1;
	return pwm_register(PWM_DEVPATH, *dev);
}

static void help(char *s)
{
	printf("%s: %s { -f <fréquence> -d <duty cycle> | -l <message lcd> | -s }\n"
		   "-p\tActive le PWM0, avec les 2 parametres obligatoires\n"
		   "-s\tDésactive le PWM\n"
		   "-l\tÉcrit sur l'écran LCD esclave 0x20, la chaine passé en paramètre\n", s);
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
		case 'd':
			dc = atoi(optarg);
			flag |= 2;
		case 's':
			fd = open(PWM_DEVPATH, O_RDONLY);
			if(ioctl(fd, PWMIOC_STOP, 0) != 0)
				printf("ioctl a échoué: %d\n", errno);
			return errno;
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
			/* getopt peut swap des arguments, donc le pointeur peut
			   etre invalidé, d'ou la copie nécessaire */
			return 0;
		default:
			help(argv[0]);
			return 3;
		}
	}

	if(flag & 3) // Les 2 arguments sont requis
	{
		if(pwm_init(&dev) != 0)
		{
			puts("Erreur d'initialisation du pwm");
			return 1;
		}
		int fd = open(PWM_DEVPATH, O_RDONLY);
		struct pwm_info_s info;
		info.frequency = freq;
		info.duty = ((unsigned)dc << 16) / 100;
		if(ioctl(fd, PWMIOC_SETCHARACTERISTICS, (unsigned)&info) != 0)
			printf("ioctl a échoué: %d\n", errno);
		if(ioctl(fd, PWMIOC_START, 0) != 0)
			printf("ioctl a échoué: %d\n", errno);
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
