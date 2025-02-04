#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define LED_VERDE 11
#define LED_VERMELHO 13
#define LED_AZUL 12
#define BOTAO 5

volatile bool podePressionar = true; // Controle do estado do botão

// Callback para desligar o LED azul
int64_t desligar_azul(alarm_id_t id, void *user_data) {
    gpio_put(LED_AZUL, 0);
    podePressionar = true; // Libera o botão para um novo acionamento
    return 0;
}

// Callback para desligar o LED vermelho e agendar desligamento do azul
int64_t desligar_vermelho(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERMELHO, 0);
    add_alarm_in_ms(3000, desligar_azul, NULL, false);
    return 0;
}

// Callback para desligar o LED verde e agendar desligamento do vermelho
int64_t desligar_verde(alarm_id_t id, void *user_data) {
    gpio_put(LED_VERDE, 0);
    add_alarm_in_ms(3000, desligar_vermelho, NULL, false);
    return 0;
}

// Callback de interrupção do botão
void botao_callback(uint gpio, uint32_t events) {
    if (podePressionar) {
        podePressionar = false;
        gpio_put(LED_VERDE, 1);
        gpio_put(LED_VERMELHO, 1);
        gpio_put(LED_AZUL, 1);
        add_alarm_in_ms(3000, desligar_verde, NULL, false);
    }
}

int main() {
    stdio_init_all();
    
    gpio_init(LED_VERDE);
    gpio_set_dir(LED_VERDE, GPIO_OUT);
    gpio_put(LED_VERDE, 0);

    gpio_init(LED_VERMELHO);
    gpio_set_dir(LED_VERMELHO, GPIO_OUT);
    gpio_put(LED_VERMELHO, 0);

    gpio_init(LED_AZUL);
    gpio_set_dir(LED_AZUL, GPIO_OUT);
    gpio_put(LED_AZUL, 0);

    gpio_init(BOTAO);
    gpio_set_dir(BOTAO, GPIO_IN);
    gpio_pull_up(BOTAO);
    gpio_set_irq_enabled_with_callback(BOTAO, GPIO_IRQ_EDGE_RISE, true, &botao_callback);
    gpio_set_irq_callback(botao_callback);
    irq_set_enabled(IO_IRQ_BANK0, true);

    while (1) {
        sleep_ms(1000);
        printf("Sistema aguardando acionamento do botão...\n");
    }
}
