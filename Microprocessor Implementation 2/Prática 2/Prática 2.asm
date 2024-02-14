ORG 0000h

MOV DPTR, #SEGMENTOS ; Carrega o endereço da tabela de segmentos em DPTR
JMP inicio ; Salta para o inicio

ORG 0033h

inicio:
 JNB P2.0, start ; Salta para start se o SW0 não estiver pressionado, caso contrário, continua aguardando
 JMP inicio ; Continua aguardando até que o SW0 seja pressionado


; Inicializa a variável R2 com 0
start:
 MOV R2, #00 

loop:
 MOV A, R2 ; Move o valor de R2 para o acumulador
 MOVC A, @A+DPTR ; Acessa o número na tabela que será exibido no display
 MOV P1, A ; Exibe o número no display
 INC R2 ; Incrementa R2 para obter o próximo número
 JMP checagem_delay ; Verifica qual atraso deve ser aplicado

pos_delay:
 CJNE R2, #10, LOOP ; Se o valor de R2 ainda não chegou a 10 -> continue a exibição
 JMP start ; Caso contrário, reinicie a contagem a partir de zero

checagem_delay:
 JNB P2.0, delay_025 ; Se o SW0 estiver pressionado, use o atraso de 0,25 segundos
 JNB P2.1, delay_1 ; Se o SW1 estiver pressionado, use o atraso de 1 segundo
 JMP checagem_delay ; Aguarde até que uma das portas esteja pressionada

delay_025:
 MOV R1, #500 ; Configura o valor de R1 para um atraso de 0,25 segundos
 JMP loop_delay ; Inicia o atraso

delay_1:
 MOV R1, #2000 ; Configura o valor de R1 para um atraso de 1 segundo
 JMP loop_delay ; Inicia o atraso

loop_delay:
 MOV R0, #250 ; Configura R0 para um valor de atraso
 DJNZ R0, $ ; Gasta 0,0005 segundos a cada iteração
 DJNZ R1, loop_delay ; Repete o atraso até que o tempo seja atingido
 JMP pos_delay ; Retorna à contagem após o atraso

; Tabela de segmentos para exibição de dígitos no display de 7 segmentos
SEGMENTOS:
DB 0c0h 
DB 0f9h
DB 0a4h
DB 0b0h
DB 99h
DB 92h
DB 82h
DB 0f8h
DB 80h
DB 90h