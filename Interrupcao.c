#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"
#include "ws2818b.pio.h"
#include "hardware/pio.h"

//Mapeamento
#define red 13
#define bt_A 5
#define bt_B 6

// Definição do número de LEDs e pino.
#define LED_COUNT 25
#define LED_PIN 7

static volatile uint32_t last_time_A = 0; // Tempo da última interrupção do botão A
static volatile uint32_t last_time_B = 0; // Tempo da última interrupção do botão B
static volatile uint flag = 0;

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

void leds_numeros()
{
    npClear();

    switch (flag)
    {
        case 0: // Número 0
            npSetLED(1, 10, 0, 0);
            npSetLED(2, 10, 0, 0);
            npSetLED(3, 10, 0, 0);
            npSetLED(5, 10, 0, 0);
            npSetLED(9, 10, 0, 0);
            npSetLED(10, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            npSetLED(15, 10, 0, 0);
            npSetLED(19, 10, 0, 0);
            npSetLED(21, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(23, 10, 0, 0);
            break;
        
        case 1: // Número 1
            npSetLED(2, 10, 0, 0);
            npSetLED(7, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(17, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(16, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            break;

        case 2: // Número 2
            npSetLED(24, 10, 0, 0);
            npSetLED(23, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(21, 10, 0, 0);
            npSetLED(20, 10, 0, 0);
            npSetLED(19, 10, 0, 0);
            npSetLED(10, 10, 0, 0);
            npSetLED(11, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(13, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            npSetLED(5, 10, 0, 0);
            npSetLED(4, 10, 0, 0);
            npSetLED(3, 10, 0, 0);
            npSetLED(2, 10, 0, 0);
            npSetLED(1, 10, 0, 0);
            npSetLED(0, 10, 0, 0);
            break;

        case 3: // Número 3
            npSetLED(24, 10, 0, 0);
            npSetLED(23, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(21, 10, 0, 0);
            npSetLED(20, 10, 0, 0);
            npSetLED(19, 10, 0, 0);
            npSetLED(10, 10, 0, 0);
            npSetLED(11, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(13, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            npSetLED(9, 10, 0, 0);
            npSetLED(0, 10, 0, 0);
            npSetLED(1, 10, 0, 0);
            npSetLED(2, 10, 0, 0);
            npSetLED(3, 10, 0, 0);
            npSetLED(4, 10, 0, 0);
            break;

        case 4: // Número 4
            npSetLED(24, 10, 0, 0);
            npSetLED(15, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            npSetLED(13, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(17, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(7, 10, 0, 0);
            npSetLED(2, 10, 0, 0);
            break;

        case 5: // Número 5
            npSetLED(24, 10, 0, 0);
            npSetLED(23, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(21, 10, 0, 0);
            npSetLED(20, 10, 0, 0);
            npSetLED(15, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            npSetLED(13, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(11, 10, 0, 0);
            npSetLED(10, 10, 0, 0);
            npSetLED(9, 10, 0, 0);
            npSetLED(0, 10, 0, 0);
            npSetLED(1, 10, 0, 0);
            npSetLED(2, 10, 0, 0);
            npSetLED(3, 10, 0, 0);
            npSetLED(4, 10, 0, 0);
            
            break;

        case 6: // Número 6
            npSetLED(24, 10, 0, 0);
            npSetLED(23, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(21, 10, 0, 0);
            npSetLED(20, 10, 0, 0);
            npSetLED(15, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            npSetLED(5, 10, 0, 0);
            npSetLED(4, 10, 0, 0);
            npSetLED(3, 10, 0, 0);
            npSetLED(2, 10, 0, 0);
            npSetLED(1, 10, 0, 0);
            npSetLED(0, 10, 0, 0);
            npSetLED(9, 10, 0, 0);
            npSetLED(10, 10, 0, 0);
            npSetLED(11, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(13, 10, 0, 0);
            break;

        case 7: // Número 7
            npSetLED(24, 10, 0, 0);
            npSetLED(23, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(21, 10, 0, 0);
            npSetLED(20, 10, 0, 0);
            npSetLED(18, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(6, 10, 0, 0);
            npSetLED(4, 10, 0, 0);
            break;

        case 8: // Número 8
            npSetLED(24, 10, 0, 0);
            npSetLED(23, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(21, 10, 0, 0);
            npSetLED(20, 10, 0, 0);
            npSetLED(10, 10, 0, 0);
            npSetLED(11, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(13, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            npSetLED(0, 10, 0, 0);
            npSetLED(1, 10, 0, 0);
            npSetLED(2, 10, 0, 0);
            npSetLED(3, 10, 0, 0);
            npSetLED(4, 10, 0, 0);
            npSetLED(15, 10, 0, 0);
            npSetLED(19, 10, 0, 0);
            npSetLED(5, 10, 0, 0);
            npSetLED(9, 10, 0, 0);
            break;

        case 9: // Número 9
            npSetLED(24, 10, 0, 0);
            npSetLED(23, 10, 0, 0);
            npSetLED(22, 10, 0, 0);
            npSetLED(21, 10, 0, 0);
            npSetLED(20, 10, 0, 0);
            npSetLED(10, 10, 0, 0);
            npSetLED(11, 10, 0, 0);
            npSetLED(12, 10, 0, 0);
            npSetLED(13, 10, 0, 0);
            npSetLED(14, 10, 0, 0);
            npSetLED(0, 10, 0, 0);
            npSetLED(15, 10, 0, 0);
            npSetLED(19, 10, 0, 0);
            npSetLED(9, 10, 0, 0);
            break;
    }

    npWrite();
}



// Prototipação da função de interrupção
static void crescer_numero(uint gpio, uint32_t events);
static void diminuir_numero(uint gpio, uint32_t events);

int main()
{
    bool state = true;
    uint32_t temp_led = 0;
    uint32_t current_time;

    stdio_init_all();

    gpio_init(red);
    gpio_set_dir(red,GPIO_OUT);

    // Inicializa matriz de LEDs NeoPixel.
    npInit(LED_PIN);
    npClear();

    gpio_init(bt_A);
    gpio_set_dir(bt_A, GPIO_IN);
    gpio_pull_up(bt_A);          

    gpio_init(bt_B);
    gpio_set_dir(bt_B, GPIO_IN);
    gpio_pull_up(bt_B);  


    // interrupção por borda de descida
    gpio_set_irq_enabled_with_callback(bt_B, GPIO_IRQ_EDGE_FALL, true, &diminuir_numero);
    gpio_set_irq_enabled_with_callback(bt_A, GPIO_IRQ_EDGE_FALL, true, &crescer_numero);

    while (true)
    {
        current_time = to_us_since_boot(get_absolute_time());

    if (current_time - temp_led > 100000) // 100ms
    {
            temp_led = current_time; // Atualiza o tempo do último evento

            state = !state;

            gpio_put(red, state);
            
    }
        leds_numeros();

    }
    
return 0;
}

// Funções de interrupção
void crescer_numero(uint gpio, uint32_t events) {
  uint32_t current_time = to_us_since_boot(get_absolute_time());
  if (current_time - last_time_A > 200000) { // 200 ms de debounce para A
    last_time_A = current_time;
    if (flag == 9) {
      flag = 0;
    } else {
      flag++;
    }
    printf("Botão A pressionado. Flag: %d\n", flag);
  }
}

void diminuir_numero(uint gpio, uint32_t events) {
  uint32_t current_time = to_us_since_boot(get_absolute_time());
  if (current_time - last_time_B > 200000) { // 200 ms de debounce para B
    last_time_B = current_time;
    if (flag == 0) {
      flag = 9;
    } else {
      flag--;
    }
    printf("Botão B pressionado. Flag: %d\n", flag);
  }
}