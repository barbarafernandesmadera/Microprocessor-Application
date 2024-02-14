org 00h ; #Origem

; #Saltar para o programa principal(main)
SJMP 		main

org			33h;#Inicinalizar o programa princiapal com label informada anteriormente

main: 		;#Label principal
			CLR 	A;  #Limpar o ACC
			MOV 	RO, #5;#Mover um valor qualquer 5,por exemplo, para RO

; Primeiro bloco do código (bloco1)

bloco1:
			CJNE 	A, #0, bloco3; #Saltar para bloco3 se A ≠ 0
			NOP;	#Consumir 1μs
			SJMP 	bloco2;	#Saltar para bloco2

; Segundo bloco de código (bloco2)
bloco2:
		
			MOV		A, RO; #Mover o valor de RO para A
			SJMP	bloco1; #Saltar incondicionalemente para bloco1

; Terceiro bloco de código (bloco3)
bloco3:

			DJNZ	RO, bloco3; #Decrementar RO e saltar para bloco3 se	R0 ≠ 0
			SJMP	main; #Saltar incondicionalemente para o programa principal para reiniciar

end;  #Fim do programa

#O programa principal começa na label main.
#No primeiro bloco de código (bloco1), verifica-se se o valor em A é diferente de zero. Se for, salta-se para o terceiro bloco (bloco3), caso contrário, consume-se 1 μs (não realizamos operação) e salta-se para o segundo bloco (bloco2).
#No segundo bloco (bloco2), move-se o valor de R0 para A e salta-se incondicionalmente de volta para o primeiro bloco (bloco1).
#No terceiro bloco (bloco3), decrementa-se o valor em R0 e salta-se de volta para o terceiro bloco enquanto R0 for diferente de zero. Quando R0 se tornar zero, salta-se incondicionalmente de volta para o programa principal para reiniciar todo o processo.


			
	
	