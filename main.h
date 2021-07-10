#ifndef __MAIN_H
#define __MAIN_H

// Set Seconds for ON cycle and OFF cycle
// (System starts in ON cycle)
/* #define ON_SECS       (10)  // vitamin c (bullet blender) */
/* #define OFF_SECS      (30) */
#define ON_SECS       (60*10)  // Nebulizer
#define OFF_SECS      (60*45)

#define RELAY_PIN     5 // *Note: Current board is ON on HIGH

////////////////////////////////////////////////////////
// Stuff below are not really settings

//#define LONGREST_SECS (20)
#define STATE_ON       0
#define STATE_OFF      1
//#define STATE_LONGREST 2 // unused
#define STATE_MAX      1

//  readable, STATE_MAX+1 count labels
#define STRS_STATE     { "ON", "OFF", "???" }

void relay_reset_timer();
void relay_jump_to_sleep_cycle();

const char *str_state(int i);
const char *str_curstate();

#ifndef __MAIN_INO
	extern unsigned int state;
	extern unsigned long secs;
#endif // /__MAIN_INO


#endif // /__MAIN_H
