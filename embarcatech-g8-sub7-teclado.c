#include <stdio.h>
#include "pico/stdlib.h"
#define led_pin_verde 11
#define led_pin_azul 12
#define led_pin_vermelho 13

//Protótipos das funções
void initleds();
void led_verde(); 
void led_azul();
void led_vermelho();


int main()
{    
    initleds();
    

    while (true) {
        
    }
}


void initleds(){
    // Inicializando as portas dos leds
    gpio_init(led_pin_verde);
    gpio_init(led_pin_azul);
    gpio_init(led_pin_vermelho);
    // Definindo as portas dos leds como saida
    gpio_set_dir(led_pin_verde,GPIO_OUT);
    gpio_set_dir(led_pin_azul,GPIO_OUT);
    gpio_set_dir(led_pin_vermelho,GPIO_OUT);
}
void led_verde(){
    //Ligando led verde, desligando as outras
    gpio_put(led_pin_verde,true);
    gpio_put(led_pin_azul,false);
    gpio_put(led_pin_vermelho,false);

}
void led_azul(){
    //Ligando led azul, desligando as outras
    gpio_put(led_pin_verde,false);
    gpio_put(led_pin_azul,true);
    gpio_put(led_pin_vermelho,false);
}
void led_vermelho(){
    //Ligando led vermelho, desligando as outras
    gpio_put(led_pin_verde,false);
    gpio_put(led_pin_azul,false);
    gpio_put(led_pin_vermelho,true);
}