#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include "hardware/timer.h"

#define HIGH 1
#define LOW 0

// チャンネル数
#define CHANNEL 2
#define A 0
#define B 0
// GPIO
#define APWM 0
#define A1 1
#define A2 2

#define BPWM 6
#define B1 7
#define B2 8

// SR-04
#define echoPin 15 // Echo Pin
#define trigPin 14 // Trigger Pin

const float V = 34300; // cm/s

//LED
#define LeftLED 11
#define RightLED 10
#define BoardLED 25

const uint8_t PWM_GPIO[CHANNEL] = {APWM, BPWM};
const uint8_t PWM_CH[CHANNEL] = {PWM_CHAN_A, PWM_CHAN_A};

// GPIOを初期化
void init_GPIO()
{
    gpio_init(BoardLED);
    gpio_set_dir(BoardLED, GPIO_OUT);
    gpio_put(BoardLED, 1);

    gpio_init(LeftLED);
    gpio_set_dir(LeftLED, GPIO_OUT);

    gpio_init(RightLED);
    gpio_set_dir(RightLED, GPIO_OUT);


    gpio_init(A1);
    gpio_set_dir(A1, GPIO_OUT);
    gpio_init(A2);
    gpio_set_dir(A2, GPIO_OUT);

    gpio_init(B1);
    gpio_set_dir(B1, GPIO_OUT);
    gpio_init(B2);
    gpio_set_dir(B2, GPIO_OUT);

    gpio_init(trigPin);
    gpio_set_dir(trigPin, GPIO_OUT);

    gpio_init(echoPin);
    gpio_set_dir(echoPin, GPIO_IN);
    gpio_pull_down(echoPin);
    
    // for (int i = 0;i < CHANNEL;i++){
        // // PWM GPIOを初期化
        // gpio_set_function(PWM_GPIO[i], GPIO_FUNC_PWM);
        // uint sliceNum = pwm_gpio_to_slice_num(PWM_GPIO[i]);
        // pwm_set_clkdiv(sliceNum, 125.0);
    // }
    gpio_init(APWM);
    gpio_set_dir(APWM, GPIO_OUT);
    gpio_put(APWM, 0);

    gpio_init(BPWM);
    gpio_set_dir(BPWM, GPIO_OUT);
    gpio_put(BPWM, 0);
}

void drive(double duty, int ch){
    int frq = 1000;
    int divCounter = 1000000/frq;

    if(duty > 0.9){
        duty = 1;
    }

    uint sliceNum = pwm_gpio_to_slice_num(PWM_GPIO[ch]);
    pwm_set_wrap(sliceNum, divCounter -1);
    pwm_set_chan_level(sliceNum, PWM_CH[ch], (int)divCounter*duty);
    pwm_set_enabled(sliceNum, true);
}

int getDepth(){
  float depth = 0;
  gpio_put(trigPin,HIGH);
  sleep_us(10);
  gpio_put(trigPin, LOW);

  while(!gpio_get(echoPin)){ 
  }
  uint32_t t1 = time_us_32();

  while(gpio_get(echoPin)){
  }
  uint32_t t2 = time_us_32() - t1;
  uint32_t t = t2;
  depth = V * t / (2.0 * 1000000.0);
  return (int)depth;
}

int main() {
    init_GPIO();

    stdio_init_all();
    
    int depth = 0;

    while(1){
        depth = getDepth();
        printf("%d cm \n",depth);
        
        if(depth > 20){
            gpio_put(BoardLED, LOW);
            
            gpio_put(A1, HIGH);
            gpio_put(A2, LOW);
            gpio_put(B1, HIGH);
            gpio_put(B2, LOW);

            gpio_put(APWM, HIGH);
            gpio_put(BPWM, HIGH);
        } else {
            gpio_put(BoardLED, HIGH);

            gpio_put(A1, LOW);
            gpio_put(A2, HIGH);
            gpio_put(B1, LOW);
            gpio_put(B2, HIGH);
            
            gpio_put(APWM, HIGH);
            gpio_put(BPWM, HIGH);

        }
        sleep_ms(1000);
    }

    return 0;
}