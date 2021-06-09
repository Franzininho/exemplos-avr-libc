/**
 * 
 * @file main.c
 * @author Eduardo Dueñas / Daniel Quadros
 * @brief Exemplo tocar musicas usando buzzer
 * @version 1.0
 * @date 21/04/2021
 * 
 * última modificação: 15/05/2021
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16500000L


#define setBit(valor,bit) (valor |= (1<<bit))
#define clearBit(valor,bit) (valor &= ~(1<<bit))
#define toogleBit(valor,bit) (valor ^= (1<<bit))
#define testBit(valor,bit)    (valor & (1<<bit))


#define NumNotas 32
#define CONT(freq) ((F_CPU*10L)/(256L*freq))

enum notas{Pausa,Do, DoS, Re, ReS, Mi, Fa, FaS, Sol, SolS, La, LaS, Si, DoM, DoSM, ReM};
long f[16] = { 255L, (long)CONT(5232L), (long)CONT(5543L), (long)CONT(5873L), (long)CONT(6222L), (long)CONT(6592L), (long)CONT(6984L),
             (long)CONT(7400L), (long)CONT(7840L), (long)CONT(8306L), (long)CONT(8800L), (long)CONT(9323L), (long)CONT(9877L),
             (long)CONT(10465L), (long)CONT(11087L), (long)CONT(11746L)};
            //{0xFF,123, 116, 110, 104, 98, 92, 87, 82, 78, 73, 69, 65, 62, 58, 54}
            //Lookup table com os valores de cada nota a ser colocado na flag do timer
            
char Partitura[NumNotas] = {Re,Mi,Mi,Re,Sol,FaS,FaS,FaS,Re,Mi,Mi,Re,La,Sol,Sol,Sol,Re,ReM,ReM,Si,Sol,FaS,FaS,Mi,
                            DoM,Si,Si,Sol,La,Sol,Sol,Sol};                          //partitura da música
volatile char cont = 0;                                          //local da partitura
volatile long aux = 0;


//tratamento de interrupção 
ISR (TIM0_COMPB_vect){  //vetor de comparação B
    if (aux<=0xff) {                        //se aux menor que 8bits 
        OCR0B=(TCNT0+aux)&(0xff);           //mandar aux para o contador
        aux=f[Partitura[cont]];             //reinicia o aux
        toogleBit(PORTB,PB1);               //inverter o buzzer
    }
    else{                                   //se não
       OCR0B=TCNT0;                         //mandar o tempoatual para o contador, o mesmo que esperar um overflow
       aux-=0xff;                           //subitrair 8bits do aux
    }            
}


//função main
int main(){
    enum notas nota;  
    setBit(DDRB,PB1);            //configura o PortB1 como saida, pino do buzzer

    //configuração do timer
    TCCR0A=0x00;                            //configura pino de compararação desconectado
    TCCR0B=0x04;                            //configura o prescaler como 256
    setBit(TIMSK,OCIE0B);        //habilita a interrupção por comparação de COMPB
    sei();                                  //habilita interrupções globais
    aux=f[Partitura[cont]];                 //inicia o contador de COMPB

    if (aux<=0xff) {
        OCR0B=(TCNT0+aux)&(0xff);
        aux=f[Partitura[cont]];
        toogleBit(PORTB,PB1);
    }
    else{
       OCR0B=TCNT0;
       aux-=0xff;
    }
    

    //loop infinito
    for(;;){                       
        long i;
        for(i=0;i<1000000L;i++){
            //long j;
            //for(j=0;j<1;j++){}
        }       //espera um tempo (altere o valor central para acelerar ou desacelerar a música)
        cont++;                         //avança na partitura
        if (cont >= NumNotas)cont=0;    //toca de novo
    }
}