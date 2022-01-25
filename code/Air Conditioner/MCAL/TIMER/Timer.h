/*
 * Timer.h
 *
 * Created: 9/4/2021 6:10:47 AM
 *  Author: Eslam Emara
 */


#ifndef TIMER_H_
#define TIMER_H_

#include "TIMER_RegMap.h"
#include "TypeDefs.h"
#include "BIT_MATH.h"
#include "Timer_config.h"

#if (TIMER0_CTRL == ENABLED) || (TIMER1_CTRL == ENABLED)
/*available PreScalars for timer0 / timer 1*/
typedef enum{
	PRESCALAR0_1 = 1,
	PRESCALAR0_8 = 8,
	PRESCALAR0_64 = 64,
	PRESCALAR0_256 = 256,
	PRESCALAR0_1024 = 1024,
	}EN_PRESCALAR0_t;

	#endif

#if TIMER2_CTRL == ENABLED
/*available PreScalars for timer2*/
typedef enum{
	PRESCALAR2_1 = 1,
	PRESCALAR2_8 = 8,
	PRESCALAR2_32 = 32,
	PRESCALAR2_64 = 64,
	PRESCALAR2_128=128,
	PRESCALAR2_256 = 256,
	PRESCALAR2_1024 = 1024,
	}EN_PRESCALAR2_t;

#endif
/*available timers*/
typedef enum{
	TIMER0 = 0x53,
	TIMER1 = 0x4F,
	TIMER2 = 0x45,
	}EN_TIMER_t;
/*available frequencies*/
typedef enum{
	FREQ_1_MHZ=1000000,
	FREQ_2_MHZ=2000000,
	FREQ_4_MHZ=4000000,
	FREQ_8_MHZ=8000000,
	}EN_FREQ_t;
/*available modes*/
typedef enum{
	NORMAL_MODE,
	FAST_PWM,
	CTC_MODE,
	}EN_MODE_t;
/*configure structure*/
typedef struct timer
{
	EN_TIMER_t timer;
	EN_FREQ_t freq;
	EN_MODE_t mode;

	}ST_TIMER_config_t;

	/*
	 *Initialization function for timers
	 *PS============ MAKE SURE YOU ENABLE THE DESIRED TIMER IN THE CONFIG FILE ===============
	 *INPUTS ST_TIMER_config_t (see Timers.h for definition)
	 *void return
	 */
void Timer_init(ST_TIMER_config_t);
/*
 *Function to delay for a period of time.
 *Conditions on desired delay ::: 255 < FREQ * desired < 216120 FOR timer 0 and timer 2
 *65536 < FREQ * desired < 67,108,864 for timer1 otherwise try to divide the delay on more than one time
 *==================================Config.mode must be NORMAL_MODE =====================================
 *INPUTS: desired delay in SECONDS , ST_TIMER_config_t timer config
 *Return 0 if the desired delay doesn't match the frequency
 *Return 1 in successful delay
 */

uint8_t Timer_Delay(float desired,ST_TIMER_config_t config);
/*
 *Function to generate PWM with 8bit resolution
 *INPUTS: uint8_t holds the duty cycle percentage, ST_TIMER_config_t timer config
 *CONDITIONs on input:  ============================== dutyCycle percentage must be between 0 and 100 ======================================
 *======================= PS:WORKS ON TIMER 0 AND TIMER 2 ONLY==============================
 *return 0 in input error type and 1 in success.
 */
void Timer_generate_PWM(uint8_t dutyCycle,ST_TIMER_config_t config);
/*
	*Function to do an event every period of time
	*INPUTS: desired delay in SECONDS , ST_TIMER_config_t timer config , Function takes void and return void
	*Conditions on desired delay ::: 255 < FREQ * desired < 216120 FOR timer 0 and timer 2
	*65536 < FREQ * desired < 67,108,864 for timer1 otherwise try to divide the delay on more than one time
	*==================================Config.mode must be CTC_MODE =====================================
	*Return 0 if the desired delay doesn't match the frequency
	*Return 1 in successful delay
 */

uint8_t Timer_Schedule_Fun(float delay,ST_TIMER_config_t config,void (*function)(void));
/*
	*Function to stop any desired timer
	*INPUTS: EN_TIMER_t (see Timer.h for definition)
	*Void return
 */
void Timer_Stop(EN_TIMER_t timer);


#endif /* TIMER_H_ */
