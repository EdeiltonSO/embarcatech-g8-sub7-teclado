#include <stdio.h>
#include "pico/stdlib.h"

const uint PIN_COLUMNS[] = {5,4,3,2};
const uint PINS_ROWS[] = {9,8,7,6};

const char CONJUNTO_DE_CARACTERES[4][4] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'},
};

void inicializarTeclado();
char verificarPinosAtivos();
void mapearTeclado(char *caractere);

int main()
{
    stdio_init_all();
    inicializarTeclado();

    while (true)
    {
        char c = '\0';
        c = verificarPinosAtivos();
        mapearTeclado(&c);
        sleep_ms(150);
    }
}
void inicializarTeclado()
{
    // Inicializa o conjunto de pinos que representa as linhas
    for (int i = 0; i < 4; i++)
    {
        gpio_init(PINS_ROWS[i]);
        gpio_set_dir(PINS_ROWS[i], GPIO_OUT);
        gpio_put(PINS_ROWS[i], 0);
    }
    // Inicializa o conjunto de pinos que representa as colunas
    for (int i = 0; i < 4; i++)
    {
        gpio_init(PIN_COLUMNS[i]);
        gpio_set_dir(PIN_COLUMNS[i], GPIO_IN);
        gpio_pull_down(PIN_COLUMNS[i]);
    }
}

char verificarPinosAtivos()
{
    for (int i = 0; i < 4; i++)
    {
        gpio_put(PINS_ROWS[i], 1);
        for (int j = 0; j < 4; j++)
        {
            if (gpio_get(PIN_COLUMNS[j]))
            {
                
                gpio_put(PINS_ROWS[i], 0);
                return CONJUNTO_DE_CARACTERES[i][j];
            }
        }
        gpio_put(PINS_ROWS[i], 0);
    }
    return '\0';
}
void mapearTeclado(char *caractere)
{ 

    switch (*caractere)
    {

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
    }
}