/**
 * 
 * @file main.c
 * @author Eduardo Dueñas
 * @brief Exemplo de contador de eventos
 * @version 0.1
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
    unsigned char i;
    for(i=0;i<30;i++){              //testa o pino varias vezer para evitar leituras erradas
        if!(testBit(PORTB,pino)){   //testa se o pino deixou de ser 1
            return false;           //se sim, retorna falso
        }
    }
    return true;                    //retorna verdadeiro
}




int main(void){
    //Configuração de PORTB
    setBit(DDRB,PB0);       //Configura PB0 como entrada
    setBit(DDRB,PB1);       //Configura PB1 como entrada
    setBit(DDRB,PB2);       //Configura PB2 como entrada
    setBit(DDRB,PB3);       //Configura PB3 como entrada
    clearBit(DDRB,PB4);     //Configura PB4 como saida
    clearBit(DDRB,PB5);     //Configura PB5 como saida

    PORTB &= 0xF0;          //manda 0 para PB[3:0]
    
    unsigned char count = 0;

    for(;;){                   //loop infinito

        if(testBit(PORTB,PB5)){                 //testa de PB5 é 1
            if(debounce(PB5)){                  //verifica se realmente foi um aperto de botão
                count = 0;                      //se sim, reseta o contador
                while (testBit(PORTB,PB5)){}    //espera o botão parar de ser precionado
            }            
        }
        if(testBit(PORTB,PB4)){                 //testa de PB4 é 1
            if(debounce(PB4)){                  //verifica se realmente foi um aperto de botão
                count++;                        //se sim, incrementa o contador
                while (testBit(PORTB,PB4)){}    //espera o botão parar de ser precionado
                
            }            
        }
        count = count % 0x0F;                   //limpa o overflow docontador
        PORTB = ((PORTB & 0xF0) | count);       //manda o contador para PB[3:0]
    }              
}