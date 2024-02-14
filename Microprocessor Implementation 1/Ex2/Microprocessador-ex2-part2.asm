org 00h ; Origem

inicio: ; Label de início

	MOV 	A, #4 ; Move o valor 4 para ACC
	MOV 	A, #3 ; Move o valor 3 para ACC

end ; Fim do programa

Para o teste adicional de mover os valores 
4 e 3 para o ACC em sequência e observar o 
bit menos significativo do registrador PSW, 
o algoritmo acima foi escrito. Neste sentido,
ao executar essas linhas e observar o registrador PSW, 
nota-se que o bit menos significativo (bit de carry) 
será 0 após a segunda operação de movimento. 
Isso ocorre porque o segundo movimento sobrescreve 
o valor anterior em ACC, e o bit de carry é zerado 
porque não houve nenhuma operação que o alterasse.

