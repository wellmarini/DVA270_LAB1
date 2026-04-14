#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <nrfx_uarte.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//definierar vilka pinnar som ska användas för att skicka och ta emot data:
#define PIN_TXD 20
#define PIN_RXD 22
#define LIMIT 10
#define MAX 50

//Skapar en driver instance för UARTE:
nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);

//skapar en buffer att ta emot tecken vi läser över UARTE
char buffer;

void read_string(char input[], int maxLen){
    int i;
    for (i = 0; i < maxLen - 1; i++){
        nrfx_uarte_rx(&instance, &buffer, 1);

        input[i] = buffer;

        if (buffer == '\r' || buffer == '\n'){
            break;
        }
    }
    input[i] = '\0';
}

int read_int(char input[], int maxLen){
   read_string(input, maxLen);
   int readInt = atoi(input);
   return readInt;
}

int main(void)
{
    //Vi kör med default settings och anger våra TX- och RX-pinnar:
    const nrfx_uarte_config_t config = NRFX_UARTE_DEFAULT_CONFIG(PIN_TXD, PIN_RXD);
    //Initierar UARTE:
    nrfx_uarte_init(&instance, &config, NULL);
    
    nrfx_systick_init();

    while(1){
    char startInput[MAX];
    char start[] = "Ange ett heltal: \n\r";
    char error[] = "Det tar för lång tid!\n\r";
    char wait[] = "Vänta!\n\r";
    char done[] = "Klar!\n\r";

    nrfx_uarte_tx(&instance, start, sizeof(start), 0);

    int finalInput = read_int(startInput, MAX);

    if(finalInput > LIMIT)
    {
        nrfx_uarte_tx(&instance, error, sizeof(error), 0);
    }
    else
    {
        nrfx_uarte_tx(&instance, wait, sizeof(wait), 0);
        nrfx_systick_delay_ms(finalInput * 1000);
        nrfx_uarte_tx(&instance, done, sizeof(done), 0);
    }
    }
}