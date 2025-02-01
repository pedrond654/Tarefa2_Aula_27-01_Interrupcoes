#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

//Mapeamento
#define red 13
#define green 11
#define blue 12
#define bt_A 5
#define bt_B 6

// Prototipação da função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    gpio_init(red);
    gpio_set_dir(red,GPIO_OUT);

    gpio_init(green);
    gpio_set_dir(greeb,GPIO_OUT);

    gpio_init(blue);
    gpio_set_dir(blue,GPIO_OUT);

    gpio_init(bt_A);
    gpio_set_dir(bt_A, GPIO_IN);
    gpio_pull_up(bt_A);          

    gpio_init(bt_B);
    gpio_set_dir(bt_B, GPIO_IN);
    gpio_pull_up(bt_B);  

return 0;
}