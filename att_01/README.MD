## Atividade 1: Temporizador Periódico (Semáforo)

Nesta atividade, um semáforo é simulado utilizando a função add_repeating_timer_ms(), que permite a alternância das cores a cada 3 segundos. O sistema inicia no vermelho, passa para o amarelo e depois para o verde, repetindo o ciclo indefinidamente.

Componentes Utilizados:

* Raspberry Pi Pico W

* 3 LEDs (vermelho, amarelo e verde)

* 3 resistores de 330 Ω

Requisitos:

* O semáforo deve iniciar no vermelho, depois amarelo e, por fim, verde.

* O temporizador deve ser configurado com um atraso de 3 segundos.

* A mudança de estado dos LEDs deve ser feita dentro da função de callback do temporizador.

* No loop principal (while), uma mensagem deve ser impressa a cada segundo.

* A simulação deve ser realizada no BitDogLab, utilizando um LED RGB conectado aos GPIOs 11, 12 e 13.
