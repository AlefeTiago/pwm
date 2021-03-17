/*Sabendo que a frequência para o efeito desejado se inicia em 30Hz, 
temos: 
M+1 = 1/t = f ---> F=30hZ ---> M=29 
T_PWM=1024 *f / 16e6 = 1,92e-3 ---> Limite= T/TPWM = 18 

*/

/*Iniciando as Bibliotecas (F_CPU apenas por precaução)*/

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL
#include <util/delay.h>
#define LIMITE 18

/* variável para estudar o tempo decorrido desde uma mudança do led*/ 
volatile unsigned int t_led = 0;

/*variável para estudar o sentido do evento (fade in/out)*/

volatile unsigned int sentido=0;



void setup(void){
  cli(); // No inicio eu desabilito as interrupções para me precaver de algum problema de setup.
  OCR2A=29;  //Carrego aqui o valor de M supracitado, visto que é o valor onde o Duty-Cicle = 1 (ponto de retorno)
  OCR2B=0; //Inicio o valor em 0, visto que durante a execução do programa irei incrementar até chegar em OCR2A
  
  TIMSK2=2;    //Define o modo de interrupção utilizando a comparação com o OCR2A.Define o modo de interrupção utilizando a comparação com o OCR2A.       
  
  
  //TCCR2B – Timer/Counter Control Register B
  //FOC2A FOC2B – – WGM22 CS22 CS21 CS20
  // 0       0         1     1    1   1  
  // Defino o modo de trabalho como Fast PWM - PRESCALE 1024 
  
  TCCR2B= 0x0F;
  
  //TCCR2A – Timer/Counter Control Register A
  //COM2A1 COM2A0 COM2B1 COM2B0 – – WGM21 WGM20
  // 0      0        1      0          1    1 
  // Defino o modo - Limpar OC2B para CM e setar 0C2B na descida. Modo Fast PWM
  
  TCCR2A= 0x23;
  
  //Defino a porta 3 como saída
  DDRD |= 8;
  
  //Defino a porta 13 como saída e inicio o led ligado, visto que o primeiro movimento é de subida. 
  DDRB |= 0x20; 
  PORTB &= ~0x20;
  
  // reativo as interrupções
  sei();
}
ISR(TIMER2_COMPA_vect){//Interrupção de comparação de OCR2A
  
  t_led++; //Incremento toda vez que entro na interrupção, até que 
  if(t_led>=LIMITE){ //No tempo LIMITE
  t_led=0; //zero a variável pois uma ação será executada a frente
    if (sentido==0){// verifico se é fade in (0) ou fade out (1)
    OCR2B++;// se for, incremento o valor do Duty-Cicle até que chegue em 1.
    
      if (OCR2B==29){// quando chega em 1
      sentido=1; // troco para fade out
      PORTB &= ~0x20; // mudo o estado do led que me indica o processo (fade in ou fade out)
      }
    }
    else{ // se estivermos em fade out 
    OCR2B --; //decremento o valor de duty até que chegue em zero
      if (OCR2B == 0){  //quando chego em zero, mudo para fade in e mudo novamente o estado do led
         sentido = 0; 
         PORTB |= 0x20; 
      }
    }
  }
}


//toda execução do programa será feita na rotina de interrupção. Por isso, na main só faço o setup e resolvo o bug do site.
int main(void){
  setup();
  while(1){
    _delay_ms(1);// bug do thinkerCad
  }
  return 0;
  
}