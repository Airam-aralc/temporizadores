#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/time.h"

const uint LED_PIN_RED = 13;
const uint LED_PIN_YELLOW = 12;
const uint LED_PIN_GREEN = 11;
const uint BUTTON_PIN = 5;

// Variáveis de controle
int estado = 0;
bool led_active = false; // Indica se o semáforo está ativo (para evitar múltiplos acionamentos do botão)

// Função callback para alternar os LEDs a cada 3 segundos
int64_t turn_off_callback(alarm_id_t id, void *user_data)
{
    // Desliga todos os LEDs antes de mudar o estado
    gpio_put(LED_PIN_RED, false);
    gpio_put(LED_PIN_YELLOW, false);
    gpio_put(LED_PIN_GREEN, false);

    // Alterna os estados dos LEDs
    if (estado == 0)
    {
        gpio_put(LED_PIN_YELLOW, true);
        printf("Semáforo amarelo! Atenção\n");
    }
    else if (estado == 1)
    {
        gpio_put(LED_PIN_GREEN, true);
        printf("Semáforo verde! Passe\n");
    }
    else if (estado == 2)
    {
        printf("Ciclo concluído. Aguarde novo acionamento do botão.\n");
        led_active = false; // Permite que o botão seja pressionado novamente
        return 0;           // Finaliza o ciclo
    }

    estado++; // Avança para o próximo estado

    // Configura o temporizador para chamar esta função novamente em 3 segundos
    return 3000000; // 3 segundos em microssegundos (3.000.000 µs)
}

int main()
{
    stdio_init_all();

    // Inicializa os LEDs como saída
    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Inicializa o botão como entrada
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN); // Ativa o pull-up interno

    while (true)
    {
        // Verifica se o botão foi pressionado e se os LEDs estão inativos
        if (gpio_get(BUTTON_PIN) == 0 && !led_active)
        {
            sleep_ms(50); // Debounce do botão

            if (gpio_get(BUTTON_PIN) == 0) // Confirma que o botão ainda está pressionado
            {
                // Inicia o ciclo com o LED vermelho aceso
                gpio_put(LED_PIN_RED, true);
                printf("Semáforo vermelho! Pare\n");

                // Marca que o ciclo começou
                led_active = true;
                estado = 0; // Reinicia a contagem de estados

                // Inicia a sequência de alternância dos LEDs
                add_alarm_in_ms(3000, turn_off_callback, NULL, false);
            }
        }

        sleep_ms(10); // Pequena pausa para otimizar o uso da CPU
    }
    return 0;
}