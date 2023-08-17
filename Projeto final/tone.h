#include <stdint.h>
#include <Arduino.h>



#define TONE_PIN      2 // buzzer

static Tc *chTC = TC0;
static uint32_t chNo = 0;


void configureToneTimer() {
  // Configure TONE_PIN pin as timer output
  pmc_enable_periph_clk( ID_PIOB ) ;
  int result = PIO_Configure( PIOB,
            PIO_PERIPH_B,
            PIO_PB25B_TIOA0,
            PIO_DEFAULT);
  Serial.println(result);

  pmc_set_writeprotect(false);
  pmc_enable_periph_clk(ID_TC0);
  TC_Configure(chTC, chNo,
         TC_CMR_TCCLKS_TIMER_CLOCK4 |
         TC_CMR_WAVE |         // Waveform mode
         TC_CMR_WAVSEL_UP_RC | // Counter running up and reset when equals to RC
         TC_CMR_ACPA_SET |     // RA compare sets TIOA
         TC_CMR_ACPC_CLEAR );  // RC compare clears TIOA
  chTC->TC_CHANNEL[chNo].TC_IER=TC_IER_CPCS;  // RC compare interrupt
  chTC->TC_CHANNEL[chNo].TC_IDR=~TC_IER_CPCS;
}

void setFrequencytone(uint32_t frequency)
{
  if(frequency < 0 || frequency > 100001) {
    TC_Stop(chTC, chNo);
    return;
  }
  const uint32_t rc = VARIANT_MCK / 128 / frequency; 
  const uint32_t ra = rc >> 1; // 50% duty cycle 
  //const uint32_t ra = rc >> 2; // 20% duty cycle
  TC_Stop(chTC, chNo);
  TC_SetRA(chTC, chNo, ra);
  TC_SetRC(chTC, chNo, rc);
  TC_Start(chTC, chNo);
}
