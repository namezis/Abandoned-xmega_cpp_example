/*
 * ledGroup.c
 *  Led group is a group of leds :-)
 *  An example could be and RGB led - which is a group of 3 leds. Or a led bar, consisting of 8 leds.
 *  The idea is that a after initialization each led of the group is addressable with a bitmask or its numbers.
 *  This allows to map real leds to different ports and pins, meanwhile the algorithm (sliding light or progress bar)
 *  remains unchanged and easy.
 *  Created on: 12.06.2011
 *      Author: Yuriy
 */

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

extern "C" {
#include "port_driver.h"
}
#include "Leds.h"

/* Allocates memory for the led group with specified amount of leds */
LedGroup::LedGroup (uint8_t maxAmountOfLeds){
    amountOfLeds = 0;
    ports = (PORT_t **) pvPortMalloc(sizeof(PORT_t *)*maxAmountOfLeds);
    bitmasks = (uint8_t*) pvPortMalloc(sizeof(uint8_t)*maxAmountOfLeds);
}
/*
 * Adds new led to group. Note that there is important to add
 * leds in the order, because they will be addressed by index.
 * Only 8 leds are supported.
 * Special case for RGB - add Red, then Green, then Blue.
 * Special case for RG - add Red, then Green
 * Returns 1 if success.
 */
void LedGroup::add(PORT_t * port, uint8_t bitmask, uint8_t isActiveLow){
    if (amountOfLeds<8) {
        //store pin information
        ports[amountOfLeds]=port;
        bitmasks[amountOfLeds]=bitmask;
        // Configures pin on the port
        PORT_ConfigurePins(port, bitmask, false, isActiveLow, PORT_OPC_PULLUP_gc, PORT_ISC_BOTHEDGES_gc );
        // Configure pin output
        //PORT_SetDirection(port, bitmask);
        PORT_SetPinsAsOutput(port, bitmask);
        //we have added one more led to the group
        amountOfLeds++;
    }
}

/*
 * Sets leds shining according to the bitmask. If you have 8 leds and want
 * leds 1,5 and 8 shining, pass bitmask '10010001'=0x91.
 * It is possible to use Color_enum instead of the bitmask for RGB leds -
 * in this case R G and B lesa should added in this order - R G B
 */
void LedGroup::set(uint8_t bitmask) {
    for (uint8_t i=0; i<amountOfLeds;i++){
        /* bitmask>>i shifts bitmask to the left, effectively placing bit
         * number i to the 0x01 position. Than clear all other bits and
         * see if this bit was 1
         */
        if ((bitmask>>i)&0x01){
            PORT_SetPins(ports[i], bitmasks[i]);
        } else {
            PORT_ClearPins(ports[i], bitmasks[i]);
        }
    }
}
