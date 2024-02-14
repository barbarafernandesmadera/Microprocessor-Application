    ORG 0000h    ; Escolhendo a origem em 0000h

inicio: 

    MOV A, #10110111b   ; Movendo de imediato o n�mero bin�rio 10110111 para o ACC
    MOV B, #10000111b   ; Movendo de imediato o n�mero bin�rio 10000111 para o B

    ANL A, B    ; Aplicando l�gica AND entre A e B

    RR A       ; Rotacionando A para a direita em um bit
    RR A       ; Rotacionando A para a direita em um bit

    CPL A       ; Complemento de A

    RL A       ; Rotacionando A para a esquerda em um bit
    RL A       ; Rotacionando A para a esquerda em um bit

    ORL A, B    ; Aplicando l�gica or e guardando em A

    XRL A, B    ; Aplicando l�gica xor e guardando em A

    SWAP A      ; Realizando SWAP de A

    JMP inicio  ; Saltar para a label inicial

    END         ; Encerrando o programa
