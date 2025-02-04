#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_RED 11
#define LED_YELLOW 12
#define LED_GREEN 13

volatile int state = 0;

bool repeating_timer_callback(struct repeating_timer *t) {   
    
    state = (state + 1) % 3;
    // Alterna entre os estados do semáforo
    if (state == 0) {
        gpio_put(LED_RED, 1);
        gpio_put(LED_YELLOW, 0);
        gpio_put(LED_GREEN, 0);
    } else if (state == 1) {
        gpio_put(LED_RED, 0);
        gpio_put(LED_YELLOW, 1);
        gpio_put(LED_GREEN, 0);
    } else if (state == 2) {
        gpio_put(LED_RED, 0);
        gpio_put(LED_YELLOW, 0);
        gpio_put(LED_GREEN, 1);
    }

     // Alterna entre os estados
    return true;
}

const char* get_led_color(int state) { //Função para exibir a cor que está acesa
    switch (state) {
        case 0: return "Cor vermelha acesa";
        case 1: return "Cor amarela acesa";
        case 2: return "Cor verde acesa";
        default: return "Estado desconhecido";
    }
}

int main() {
    stdio_init_all();

    // Configuração dos pinos como saída
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_YELLOW);
    gpio_set_dir(LED_YELLOW, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);
    gpio_put(LED_RED, 1);

    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    while (1) {
        printf("%s\n", get_led_color(state));
        sleep_ms(1000);
    }
}
