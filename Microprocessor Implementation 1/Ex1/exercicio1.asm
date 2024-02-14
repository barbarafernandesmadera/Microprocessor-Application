	org		0000h
inicio:

	; Carrega o valor hexadecimal 5A em A (ou ACC)
	MOV ACC, #0x3A ; 2us

	; Move de forma imediata um valor qualquer em hexadecimal (de 00 a FF) para o registrador acumulador 
	MOV ACC,  #00h ; 4us

	; Move o valor hexadecimal 0x42 para o registrador R3
	MOV R3, #0x42 ; 5us

	; Move o valor hexadecimal 0x5A para o registrador B
	MOV B, #0x5A ;7us


	;Move a porta P1 para um endere�o de mem�ria RAM qualquer (entre 00 a 7F)
	MOV R0, P1 ; 9us
	MOV 0x20, R0 ; 11us

	;Move de forma direta o conte�do da posi��o de mem�ria escolhida na linha anterior para um registrador qualquer do Banco 01 (segundo banco)
	MOV ACC, #0x30 ; 13us
	MOV R2, ACC ; 15 us

	; Move o conte�do do registrador R2 para o endere�o de mem�ria 0x200
	MOV 0x70, R2 ; 17us
	
	; Move o valor imediato 0x200 para o registrador R1
	MOV R1, #0x70 ; 18us

	; Move o conte�do da mem�ria apontada por R1 para o acumulador A
	MOV ACC, @R1 ; 20us

	; Move o valor para O DPTR 
	MOV DPTR, #0x9A5B ; 22us

	NOP ; 23us

	end

; RESPOSTAS

; a) Vide o c�digo

; b)MOV A, 0x5A - 1 ciclo 
   ;MOV ACC, #00h - 3 ciclos
   ;MOV R3, #0x42 - 4 ciclos
   ;MOV B, #0x5A - 6 ciclos
   ;MOV R0, P1 - 8 ciclos
   ;MOV 0x20, R0 - 10 ciclos 
   ;MOV A, #0x30 - 11 ciclos 
   ;MOV R2, A - 12 ciclos 
   ;MOV 0x70, R2 - 14 ciclos 
   ;MOV R1, #0x70 - 15 ciclos
   ;MOV A, @R1 - 16 ciclos 
   ;MOV DPTR, #0x9A5B - 18 ciclos 
   ;NOP - 1 ciclo 
	
	; Total: 109 ciclos de m�quina

; c) Ao mover uma porta inteira de 8 registradores, como P1, para um registrador, como R0, o valor resultante � frequentemente 0xFF. Isso ocorre porque, por padr�o, os pinos da porta P1 s�o configurados como entradas de alta imped�ncia, e quando nenhum dispositivo externo os est� puxando para um estado espec�fico, eles tendem a ficar em um estado de "1" devido a resistores de pull-up internos.

; d) Continuou o mesmo valor anterior (0x30)

; e) Foi poss�vel mover um valor de 4 d�gitos (16 bits) para DPTR porque DPTR � um registrador especial de 16 bits usado para armazenar endere�os de mem�ria. O DPTR � formado pelos registradores DPH (byte mais significativo) e DPL (byte menos significativo). Ele pode armazenar valores de endere�o de mem�ria de at� 0xFFFF em hexadecimal (65535 em decimal), e � poss�vel verificar as mudan�as nos registradores DPH e DPL no simulador ao realizar a opera��o de carga em DPTR.