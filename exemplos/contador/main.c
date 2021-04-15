/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos
 * @version 1.0
 * @date 06/04/2021
 * 
 */

#include <avr/io.h>

#define F_CPU 16500000L

 	
#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))


//debounce do push button para desconciderarmos ruido e bouncing do botão
char debounce(int pino){
    unsigned int i;
    for(i=0;i<300;i++){              //testa o pino varias vezer para evitar leituras erradas
        if(!(testBit(PINB,pino))){   //testa se o pino deixou de ser 1
            return 0;           //se sim, retorna falso
        }
    }
    return 1;                    //retorna verdadeiro
}




int main(void){
    //Configuração de PORTB
    clearBit(DDRB,PB0);     //Configura PB0 como saida
    setBit(DDRB,PB1);       //Configura PB1 como entrada
    setBit(DDRB,PB2);       //Configura PB2 como entrada
    setBit(DDRB,PB3);       //Configura PB3 como entrada
    setBit(DDRB,PB4);       //Configura PB4 como entrada

    PORTB &= 0xE1;          //manda 0 para PB[4:1]
    
    unsigned char count = 0;

    for(;;){                   //loop infinito

        if(testBit(PINB,PB0)){                 //testa de PB0 é 1
            if(debounce(PB0)){                  //verifica se realmente foi um aperto de botão
                count++;                        //se sim, incrementa o contador
                while (testBit(PINB,PB0)){}    //espera o botão parar de ser precionado
                
            }            
        }
        count = count % 0x10;                   //limpa o overflow docontador
        PORTB = ((PORTB & 0xE1) | (count<<1));       //manda o contador para PB[4:1]
    }              
}