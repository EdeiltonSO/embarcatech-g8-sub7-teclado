#include <stdio.h>
#include "pico/stdlib.h"

#define led_pin_verde 11
#define led_pin_azul 12
#define led_pin_vermelho 13

// Configuração do buzzer
#define BUZZER_PIN 21 // Pino conectado ao buzzer

const uint PIN_COLUMNS[] = {5,4,3,2};
const uint PINS_ROWS[] = {9,8,7,6};

const char CONJUNTO_DE_CARACTERES[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

// Protótipos das funções
void initleds();
void led_verde(); 
void led_azul();
void led_vermelho();
void all_leds_off();
void buzzer_init();
void buzzer_beep_one_second();

void inicializarTeclado();
char verificarPinosAtivos();
void mapearTeclado(char *caractere);

int main() {
    stdio_init_all();
    inicializarTeclado();
    initleds();
    buzzer_init();

    while (true) {
        char c = '\0';
        c = verificarPinosAtivos();
        mapearTeclado(&c);
        sleep_ms(150);
    }
}

void inicializarTeclado() {
    // Inicializa o conjunto de pinos que representa as linhas
    for (int i = 0; i < 4; i++) {
        gpio_init(PINS_ROWS[i]);
        gpio_set_dir(PINS_ROWS[i], GPIO_OUT);
        gpio_put(PINS_ROWS[i], 0);
    }
    
    // Inicializa o conjunto de pinos que representa as colunas
    for (int i = 0; i < 4; i++) {
        gpio_init(PIN_COLUMNS[i]);
        gpio_set_dir(PIN_COLUMNS[i], GPIO_IN);
        gpio_pull_down(PIN_COLUMNS[i]);
    }
}

char verificarPinosAtivos() {
    for (int i = 0; i < 4; i++) {
        gpio_put(PINS_ROWS[i], 1);
      
        for (int j = 0; j < 4; j++) {
            if (gpio_get(PIN_COLUMNS[j])) {
                gpio_put(PINS_ROWS[i], 0);
                return CONJUNTO_DE_CARACTERES[i][j];
            }
        }
        gpio_put(PINS_ROWS[i], 0);
    }
    return '\0';
}

void initleds() {
    // Inicializando as portas dos leds
    gpio_init(led_pin_verde);
    gpio_init(led_pin_azul);
    gpio_init(led_pin_vermelho);
    // Definindo as portas dos leds como saída
    gpio_set_dir(led_pin_verde, GPIO_OUT);
    gpio_set_dir(led_pin_azul, GPIO_OUT);
    gpio_set_dir(led_pin_vermelho, GPIO_OUT);
}

void led_verde() {
    gpio_put(led_pin_verde, true);
    gpio_put(led_pin_azul, false);
    gpio_put(led_pin_vermelho, false);
}

void led_azul() {
    gpio_put(led_pin_verde, false);
    gpio_put(led_pin_azul, true);
    gpio_put(led_pin_vermelho, false);
}

void led_vermelho() {
    gpio_put(led_pin_verde, false);
    gpio_put(led_pin_azul, false);
    gpio_put(led_pin_vermelho, true);
}

void all_leds_off() {
    gpio_put(led_pin_verde, false);
    gpio_put(led_pin_azul, false);
    gpio_put(led_pin_vermelho, false);
}

//Aciona todos os leds
void leds_simultaneos(){
    gpio_put(led_pin_verde,true);
    gpio_put(led_pin_azul,true);
    gpio_put(led_pin_vermelho,true);
}

// Inicializa o buzzer
void buzzer_init() {
    gpio_init(BUZZER_PIN);
    gpio_set_dir(BUZZER_PIN, GPIO_OUT);
    gpio_put(BUZZER_PIN, 0); // Garante que o buzzer esteja desligado inicialmente
}

// Emite som no buzzer por 1 segundo
void buzzer_beep_one_second() {
    for (int i = 0; i < 1000; i++) {
        gpio_put(BUZZER_PIN, 1); // Liga o buzzer
        sleep_us(500);          // Aguarda metade do ciclo
        gpio_put(BUZZER_PIN, 0); // Desliga o buzzer
        sleep_us(500);          // Aguarda metade do ciclo
    }
}

void mapearTeclado(char *caractere) { 
    switch (*caractere) {
        case 'A':
            led_vermelho();
            break;
        case 'B':
            led_azul();
            break;
        case 'C':
            led_verde();
            break;
        case 'D':
            leds_simultaneos();
            break;
        case '#':
            buzzer_beep_one_second();
            break;
        default:
            all_leds_off();
            break;
    }
}
