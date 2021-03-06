/*
 *  felicagpio.c
 *
 */

/*
 *    INCLUDE FILES FOR MODULE
 */
#include <linux/gpio.h>

#include "felica_gpio.h"



/* Debug message feature */
/* #define FELICA_DEBUG_MSG */

/*
* Description :
* Input :
* Output :
*/
int felica_gpio_open(int gpionum, int direction, int value)
{
  int rc = 0;
  char int_name[30];

  if(direction == GPIO_DIRECTION_IN)
  {
    rc = gpio_tlmm_config(GPIO_CFG(gpionum, 0, GPIO_CFG_INPUT, GPIO_CFG_PULL_UP, GPIO_CFG_2MA), GPIO_CONFIG_ENABLE);

  if(rc)
  {
    FELICA_DEBUG_MSG("[FELICA] ERROR - gpio_tlmm_config \n");
    return rc;
  }

    if(GPIO_FELICA_INT == gpionum)
  {
      sprintf(int_name, "felica_int_%02d", gpionum);

      gpio_request(gpionum, int_name);
    }

    rc = gpio_direction_input((unsigned)gpionum);

    if(rc)
    {
      FELICA_DEBUG_MSG("[FELICA] ERROR -  gpio_direction_input \n");
      return rc;
    }
  }
  else
  {
    rc = gpio_tlmm_config(GPIO_CFG(gpionum, 0, GPIO_CFG_OUTPUT, GPIO_CFG_NO_PULL, GPIO_CFG_2MA), GPIO_CONFIG_ENABLE);

    if(rc)
    {
      FELICA_DEBUG_MSG("[FELICA] ERROR - gpio_tlmm_config \n");
      return rc;
    }

    rc = gpio_direction_output((unsigned)gpionum, GPIO_HIGH_VALUE);

    if(rc)
    {
      FELICA_DEBUG_MSG("[FELICA] ERROR -  gpio_direction_output \n");
      return rc;
    }
  }

  return rc;
}

/*
* Description :
* Input :
* Output :
*/
void felica_gpio_write(int gpionum, int value)
{
  gpio_set_value(gpionum, value);
}

/*
* Description :
* Input :
* Output :
*/
int felica_gpio_read(int gpionum)
{
  return gpio_get_value(gpionum);
}
