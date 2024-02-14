org 00h ; #Origem
inicio: ; #Label de início
	MOV 	A,#2 ; #Move o valor 2 para o acumulador ACC
	MOV 	B,#3 ; #Move o valor 3 para o registrador B
	MOV 	20h,#7 ; #Move o valor 7 para o endereço de memória 20h
	ADD		A, 20h ; #Soma o conteúdo de 20h ao ACC
	DEC 	A;	#Decrementa 3 unidade do ACC
	INC		B;  #Incrementa 1 unidade em B
	SUBB	A,B; #Subtrai B de A
	MUL		AB;	 #Multiplica A por B
	INC 	B,#2;	#Incrementa B em 2 unidades
	DIV		AB;	#Divide A por B
	MOV		30h, A;	#Armazena o conteúdo de A 	no endereço 30h
	MOV		31h, B; #Armazena o conteúdo B no endereço 31h
	SJMP	inicio; #Salta para o início do programa
end


