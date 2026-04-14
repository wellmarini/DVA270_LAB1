#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_systick.h>
#include <nrfx_uarte.h>

void toggle_led(int ledPin)
{
    if(nrf_gpio_pin_out_read(ledPin) == 0)
    {
        nrf_gpio_pin_write(ledPin, LED_OFF);
    } else {
        nrf_gpio_pin_write(ledPin, LED_ON);
    }
}

int main(void)
{
    nrf_gpio_cfg_output(LED1);
    nrf_gpio_cfg_output(LED2);
    nrf_gpio_cfg_output(LED3);
    nrf_gpio_cfg_output(LED4);

    nrf_gpio_pin_write(LED1, LED_OFF);
    nrf_gpio_pin_write(LED2, LED_OFF);
    nrf_gpio_pin_write(LED3, LED_OFF);
    nrf_gpio_pin_write(LED4, LED_OFF);

    nrf_gpio_cfg_input(BUTTON1, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON2, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON3, NRF_GPIO_PIN_PULLUP);
    nrf_gpio_cfg_input(BUTTON4, NRF_GPIO_PIN_PULLUP);

    while(1)
    {
        if(nrf_gpio_pin_read(BUTTON1) == 0)
        {
            toggle_led(LED1);
            while(nrf_gpio_pin_read(BUTTON1) == 0);
        } 

        if(nrf_gpio_pin_read(BUTTON2) == 0)
        {
            toggle_led(LED2);
            while(nrf_gpio_pin_read(BUTTON2) == 0);
        }

        if(nrf_gpio_pin_read(BUTTON3) == 0)
        {
            toggle_led(LED3);
            while(nrf_gpio_pin_read(BUTTON3) == 0);
        }

        if(nrf_gpio_pin_read(BUTTON4) == 0)
        {
            toggle_led(LED4);
            while(nrf_gpio_pin_read(BUTTON4) == 0);
        }
    }

}