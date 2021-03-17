O desafio proposto nesta atividade é desenvolver um programa que faça com que a intensidade luminosa
de um LED seja controlada por um sinal PWM. Mais especificamente, desejamos que a intensidade cresça
em, aproximadamente, 1 segundo desde a mínima até a máxima, de maneira que enxerguemos o LED
acendendo aos poucos. Então, uma vez atingida a máxima intensidade, devemos reduzi-la até o valor
mínimo também em um intervalo de, aproximadamente, 1 segundo.
A fim de permitir uma visualização suave do aumento da intensidade do LED (processo de fade in), o
registrador que controla o duty cycle do sinal PWM deve ser progressivamente incrementado desde 0 até
seu valor máximo durante o intervalo de 1 segundo. Um raciocínio análogo vale para o processo de
redução da intensidade do LED (fade out). A figura a seguir ilustra os processos de fade in e fade out,
mostrando a evolução do valor do registrador que controla o duty cycle do sinal PWM ao longo do tempo.

![alt text](https://github.com/AlefeTiago/pwm/blob/main/pwm.PNG)

Note que M é o valor armazenado em OCR2X quando o duty cycle é 100% (LED aceso com máxima
intensidade) e T é o intervalo de tempo com que OCR2X deve ser atualizado (incrementado ou
decrementado) para produzir os efeitos de fade in e fade out. Portanto, definido M, o intervalo pode ser
obtido a partir da relação T = 1/M segundos, com T maior ou igual a um período do sinal PWM.
Durante o fade in, o LED incorporado (pino 13) deve permanecer aceso e apagado durante o fade out, ou
seja, ele deve piscar com frequência de aproximadamente 0,5 Hz, sincronizado com o acionamento do
outro LED. O sinal gerado no pino 13 pode ser usado para verificar se os tempos de fade in e fade out estão
corretamente configurados. Um osciloscópio pode ser usado para esse fim no Tinkercad.
As especificações do temporizador (e.g., prescaler, valor máximo da contagem, etc.) devem ser projetadas
por cada aluno e justificadas nos comentários do código-fonte. Notem que há mais de uma maneira de se
configurar o temporizador para atingir o comportamento desejado do sistema.
Somente o temporizador 2 poderá ser utilizado na atividade, sendo que o modo de operação explorado
deve ser o Fast PWM.
Observações:
É possível usar o modo Fast PWM do timer 2 com a contagem avançando desde 0 até 255, ou com a
contagem partindo de 0 até o valor armazenado em OCR2A. O LED (com resistor) deve ser conectado no
terminal em que a forma de onda é gerada (depende do canal/modo escolhido).
