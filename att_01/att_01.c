#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_PIN_RED 13
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 11

int estado = 0; // Controla a cor do semáforo (0 = amarelo, 1 = verde, 2 = vermelho)

// Função de callback do temporizador que alterna os LEDs, executada automaticamente a cada 3 segundos
bool repeating_timer_callback(struct repeating_timer *t) 
{   
    // Apaga todos os LEDs antes de acender o próximo
    gpio_put(LED_PIN_RED, false);
    gpio_put(LED_PIN_YELLOW, false);
    gpio_put(LED_PIN_GREEN, false);

    // Alterna o estado do semáforo
    if (estado == 0) {
        gpio_put(LED_PIN_YELLOW, true);
        printf("Semáforo amarelo! Atenção\n");
    } 
      else if (estado == 1) {
        gpio_put(LED_PIN_GREEN, true);
        printf("Semáforo verde! Passe\n");
    } 
    else {
        gpio_put(LED_PIN_RED, true);
        printf("Semáforo vermelho! Pare.\n");
    }

    // Atualiza o estado para o próximo ciclo (0 → 1 → 2 → 0)
    estado = (estado + 1) % 3;

    return true; // Mantém o temporizador ativo
}

int main() 
{
    stdio_init_all();

    // Inicializa LEDs como saída
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Liga o LED vermelho no início, sendo o estado inical do semáforo
    gpio_put(LED_PIN_RED, true);
    
    // Configura o temporizador para alternar os LEDs a cada 3 segundos
    struct repeating_timer timer;
    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);

    // Loop infinito que exibe uma mensagem a cada segundo
    while (true) {
        printf("Passou 1 segundo\n"); //mensagem para depuração
        sleep_ms(1000);
    }
    return 0; //nunca será alcanlado, pois o loop é infinito, usado como boa prática de programação
}