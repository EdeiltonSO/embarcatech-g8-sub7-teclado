#include <stdio.h>
#include "pico/stdlib.h"

#define led_pin_verde 11
#define led_pin_azul 12
#define led_pin_vermelho 13

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

void inicializarTeclado();
char verificarPinosAtivos();
void mapearTeclado(char *caractere);

int main() {
    stdio_init_all();
    inicializarTeclado();
    initleds();

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
    // Definindo as portas dos leds como saida
    gpio_set_dir(led_pin_verde,GPIO_OUT);
    gpio_set_dir(led_pin_azul,GPIO_OUT);
    gpio_set_dir(led_pin_vermelho,GPIO_OUT);
}

void led_verde() {
    //Ligando led verde, desligando as outras
    gpio_put(led_pin_verde,true);
    gpio_put(led_pin_azul,false);
    gpio_put(led_pin_vermelho,false);
}

void led_azul() {
    //Ligando led azul, desligando as outras
    gpio_put(led_pin_verde,false);
    gpio_put(led_pin_azul,true);
    gpio_put(led_pin_vermelho,false);
}

void led_vermelho() {
    //Ligando led vermelho, desligando as outras
    gpio_put(led_pin_verde,false);
    gpio_put(led_pin_azul,false);
    gpio_put(led_pin_vermelho,true);
}

void mapearTeclado(char *caractere) { 

    switch (*caractere) {

        case 'A':
            // Inserir o código para ligar o led vermelho

            break;

        case 'B':
            // Inserir o código para ligar o led azul

            break;

        case 'C':
            // Inserir o código para ligar o led verde

            break;

        case 'D':
            // Inserir o código para ligar TODOS os leds

            break;

        case '#':
            // Inserir o código para emitir um som com o buzzer

            break;

        default:
            // Inserir o código para desligar TODOS os leds
        break;
    }
}