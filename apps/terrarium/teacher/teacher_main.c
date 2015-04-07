/****************************************************************************
 * apps/terrarium/teacher_main.c
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <stdio.h>
#include <arch/board/board.h>

/****************************************************************************
 * Definitions
 ****************************************************************************/

#define ADC_DEVPATH "/dev/adc0"
#define PWM_DEVPATH "/dev/pwm0"

/****************************************************************************
 * Private Data
 ****************************************************************************/


/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * hello_main
 ****************************************************************************/

#ifdef CONFIG_BUILD_KERNEL
int main(int argc, FAR char *argv[])
#else
int teacher_test1_main(int argc, char *argv[])
#endif
{
  int i;

  printf("Hello, World!!\n");

  for ( i=0 ; i < 10 ; i++ )
  {
    sam_setled( BOARD_D9, true);
    sam_setled( BOARD_D10, true);
  
    sleep(1);

    sam_setled( BOARD_D9, false);
    sam_setled( BOARD_D10, false);
  
    sleep(1);
  }


  /* Let configure the SAM4S peripherals we need */

#ifdef CONFIG_APPLICATION_TIBO_TEST1_USE_ADC
#endif

#ifdef CONFIG_APPLICATION_TIBO_TEST1_USE_PWM
#endif

#ifdef CONFIG_APPLICATION_TIBO_TEST1_USE_I2C
#endif

#ifdef CONFIG_APPLICATION_TIBO_TEST1_USE_SPI
#endif

  return 0;
}

