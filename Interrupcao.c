#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "ws2818b.pio.h"
#include "hardware/pio.h"

//Mapeamento
#define red 13
#define green 11
#define blue 12
#define bt_A 5
#define bt_B 6

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7


// Definição de pixel GRB (Matriz de Leds)
struct pixel_t {
  uint8_t G, R, B; // Três valores de 8-bits compõem um pixel.
};
typedef struct pixel_t pixel_t;
typedef pixel_t npLED_t; // Mudança de nome de "struct pixel_t" para "npLED_t" por clareza.

// Declaração do buffer de pixels que formam a matriz.
npLED_t leds[LED_COUNT];

// Variáveis para uso da máquina PIO.
PIO np_pio;
uint sm;

/**
 * Inicializa a máquina PIO para controle da matriz de LEDs.
 */
void npInit(uint pin) {

  // Cria programa PIO.
  uint offset = pio_add_program(pio0, &ws2818b_program);
  np_pio = pio0;

  // Toma posse de uma máquina PIO.
  sm = pio_claim_unused_sm(np_pio, false);
  if (sm < 0) {
    np_pio = pio1;
    sm = pio_claim_unused_sm(np_pio, true); // Se nenhuma máquina estiver livre, panic!
  }

  // Inicia programa na máquina PIO obtida.
  ws2818b_program_init(np_pio, sm, offset, pin, 800000.f);

  // Limpa buffer de pixels.
  for (uint i = 0; i < LED_COUNT; ++i) {
    leds[i].R = 0;
    leds[i].G = 0;
    leds[i].B = 0;
  }
}

/**
 * Atribui uma cor RGB a um LED.
 */
void npSetLED(const uint index, const uint8_t r, const uint8_t g, const uint8_t b) {
  leds[index].R = r;
  leds[index].G = g;
  leds[index].B = b;
}

/**
 * Limpa o buffer de pixels.
 */
void npClear() {
  for (uint i = 0; i < LED_COUNT; ++i)
    npSetLED(i, 0, 0, 0);
}

/**
 * Escreve os dados do buffer nos LEDs.
 */
void npWrite() {
  // Escreve cada dado de 8-bits dos pixels em sequência no buffer da máquina PIO.
  for (uint i = 0; i < LED_COUNT; ++i) {
    pio_sm_put_blocking(np_pio, sm, leds[i].G);
    pio_sm_put_blocking(np_pio, sm, leds[i].R);
    pio_sm_put_blocking(np_pio, sm, leds[i].B);
  }
  sleep_us(100); // Espera 100us, sinal de RESET do datasheet.
}

// Mapeamento da matriz (5x5)
int getIndex(int x, int y) {
    return (y % 2 == 0) ? y * 5 + x : y * 5 + (4 - x);
}




// Prototipação da função de interrupção
static void gpio_irq_handler(uint gpio, uint32_t events);

int main()
{
    stdio_init_all();

    gpio_init(red);
    gpio_set_dir(red,GPIO_OUT);

    gpio_init(green);
    gpio_set_dir(green,GPIO_OUT);

    gpio_init(blue);
    gpio_set_dir(blue,GPIO_OUT);

    gpio_init(bt_A);
    gpio_set_dir(bt_A, GPIO_IN);
    gpio_pull_up(bt_A);          

    gpio_init(bt_B);
    gpio_set_dir(bt_B, GPIO_IN);
    gpio_pull_up(bt_B);  

    while (true)
    {
        for(int i = 0; i < 5; i++)
        {
            gpio_put(red, true);
            sleep_ms(100);

            gpio_put(red, false);
            sleep_ms(100);
        }
    }
    
return 0;
}