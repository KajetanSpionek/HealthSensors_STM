#include "util.h"


/* Shutdown modes:
 * 0 - default, blocking shutdown - happens immediately
 * 1 - after short delay - in non blocking behaviour
 * Time:
 * Value in ms, only available when (mode == 1)
 */
void UTIL_powerShutdown(uint8_t mode, uint8_t time) {

	switch(mode) {
		case 0:
			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_5, GPIO_PIN_SET);
			break;
		case 1:
			// TODO:
			break;
		default:
			break;
	}
}
