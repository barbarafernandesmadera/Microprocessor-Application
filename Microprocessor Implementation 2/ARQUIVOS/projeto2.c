
typedef int Boolean; // Tipo de dado booleano, representado como um inteiro (0 para falso, 1 para verdadeiro)

// Defini��o de constantes para verdadeiro e falso
#define Verdadeiro 1
#define Falso 0

// Defini��o dos valores bin�rios para os d�gitos no display de 7 segmentos
#define Numero7Seg0 0b00111111 // Representa��o bin�ria do d�gito 0
#define Numero7Seg1 0b00000110 // Representa��o bin�ria do d�gito 1
#define Numero7Seg2 0b01011011 // Representa��o bin�ria do d�gito 2
#define Numero7Seg3 0b01001111 // Representa��o bin�ria do d�gito 3
#define Numero7Seg4 0b01100110 // Representa��o bin�ria do d�gito 4
#define Numero7Seg5 0b01101101 // Representa��o bin�ria do d�gito 5
#define Numero7Seg6 0b01111101 // Representa��o bin�ria do d�gito 6
#define Numero7Seg7 0b00000111 // Representa��o bin�ria do d�gito 7
#define Numero7Seg8 0b01111111 // Representa��o bin�ria do d�gito 8
#define Numero7Seg9 0b01101111 // Representa��o bin�ria do d�gito 9
#define Erro7Seg 0b01111001    // Representa��o bin�ria do d�gito de erro 'E'

// Vari�vel global para controle do n�mero atual no display de 7 segmentos
int NumeroAtual7Seg = -1;

// Fun��es do display de 7 segmentos
void Inicializar7Seg(); // Inicializa as configura��es do display
void AumentarNumero7Seg(); // Incrementa o n�mero no display
void Atualizar7Seg(); // Atualiza o display com o n�mero atual
void Ligar7Seg(); // Liga o display
void Desligar7Seg(); // Desliga o display

// Defini��o dos tempos do projeto em segundos para o timer
#define TempoModoRapido 0.25f // Tempo para o modo r�pido
#define TempoModoLento 1.00f // Tempo para o modo lento

// Vari�veis relacionadas ao timer
int TempoAtualInicial = 0; // Tempo atual para o reload do timer
int TempoModoRapidoInicial = 0; // Tempo para o modo r�pido
int TempoModoLentoInicial = 0; // Tempo para o modo lento

// Fun��es do timer
void ConfigurarTimer(); // Configura as op��es do timer
void MudarParaModoRapido(); // Altera a velocidade do timer para r�pido
void MudarParaModoLento(); // Altera a velocidade do timer para lento
void RecarregarTimer(); // Reinicia a contagem do timer
void IniciarTimer(); // Liga o timer
void PararTimer(); // Para o timer

// Vari�vel global para controle do estado ligado/desligado
Boolean Ligado = Falso;

// Atualiza o display de 7 segmentos com o n�mero atual
void Atualizar7Seg() {
    int displayBinario;
    switch (NumeroAtual7Seg) { // Converte o n�mero atual para a representa��o bin�ria do display
    case 0:
        displayBinario = Numero7Seg0;
        break;
    case 1:
        displayBinario = Numero7Seg1;
        break;
    case 2:
        displayBinario = Numero7Seg2;
        break;
    case 3:
        displayBinario = Numero7Seg3;
        break;
    case 4:
        displayBinario = Numero7Seg4;
        break;
    case 5:
        displayBinario = Numero7Seg5;
        break;
    case 6:
        displayBinario = Numero7Seg6;
        break;
    case 7:
        displayBinario = Numero7Seg7;
        break;
    case 8:
        displayBinario = Numero7Seg8;
        break;
    case 9:
        displayBinario = Numero7Seg9;
        break;
    default:
        displayBinario = Erro7Seg;
    }
    LATD = displayBinario; // Atualiza o display de 7 segmentos
}
// Fun��o de interrup��o de alta prioridade
void InterrupcaoAltaPrioridade() iv 0x0008 ics ICS_AUTO {
    if (INTCON.INT0IF == 1) { // Verifica se houve interrup��o do bot�o RB0
        MudarParaModoLento(); // Muda para o modo lento
        INTCON.INT0IF = 0; // Zera a flag de interrup��o
    } else if (INTCON3.INT1IF == 1) { // Verifica se houve interrup��o do bot�o RB1
        MudarParaModoRapido(); // Muda para o modo r�pido
        INTCON3.INT1IF = 0; // Zera a flag de interrup��o
    }

    RecarregarTimer(); // Recarrega o timer

    if (!Ligado) { // Se n�o estiver ligado, liga agora
        Ligar7Seg();
        IniciarTimer();
        Ligado = Verdadeiro;
    }
}

// Fun��o de interrup��o de baixa prioridade
void InterrupcaoBaixaPrioridade() iv 0x0018 ics ICS_AUTO {
    if (INTCON.TMR0IF == 1) { // Verifica se houve interrup��o do timer
        AumentarNumero7Seg(); // Incrementa o n�mero no display
        RecarregarTimer(); // Recarrega o timer
        INTCON.TMR0IF = 0; // Zera a flag de interrup��o do timer
    }
}

// Configura��o das interrup��es
void ConfigurarInterrupcao() {
    ADCON1 |= 0xF; // Configura as portas como digitais
    RCON.IPEN = 1; // Habilita as duas prioridades

    INTCON2.INTEDG0 = 1; // Borda de subida para a interrup��o 0
    INTCON2.INTEDG1 = 1; // Borda de subida para a interrup��o 1

    INTCON3.INT1IP = 1; // Prioridade alta para a interrup��o 1

    INTCON.INT0IF = 0; // Zera a flag de interrup��o do bot�o RB0
    INTCON3.INT1IF = 0; // Zera a flag de interrup��o do bot�o RB1

    INTCON.INT0IE = 1; // Ativa as interrup��es para o bot�o RB0
    INTCON3.INT1IE = 1; // Ativa as interrup��es para o bot�o RB1

    INTCON.GIEL = 1; // Ativa a interrup��o de baixa prioridade
    INTCON.GIEH = 1; // Ativa a interrup��o de alta prioridade
}

// Configura��o do timer
void ConfigurarTimer() {
    T0CON = 0b00000100; // Configura��es do timer: 16 bits, clock interno, prescaler 1:32

    INTCON.TMR0IF = 0; // Zera a flag de interrup��o do timer
    INTCON2.TMR0IP = 0; // Prioridade baixa para a interrup��o do timer
    INTCON.TMR0IE = 1; // Ativa a interrup��o do timer

    TempoModoRapidoInicial = 49911; // Valor inicial para o modo r�pido
    TempoModoLentoInicial = 3036; // Valor inicial para o modo lento

    TempoAtualInicial = TempoModoLentoInicial; // Valor inicial do timer
}

// Inicia o timer
void IniciarTimer() {
    RecarregarTimer(); // Reinicia a contagem do timer
    T0CON.TMR0ON = 1; // Liga o timer
}

// Muda para o modo r�pido
void MudarParaModoRapido() {
    TempoAtualInicial = TempoModoRapidoInicial; // Muda a velocidade da contagem para r�pido
}

// Muda para o modo lento
void MudarParaModoLento() {
    TempoAtualInicial = TempoModoLentoInicial; // Muda a velocidade da contagem para lento
}

// Recarrega o timer
void RecarregarTimer() {
    TMR0H = (TempoAtualInicial >> 8); // Configura os bits mais significativos
    TMR0L = TempoAtualInicial; // Configura os bits menos significativos
    INTCON.TMR0IF = 0; // Zera a flag de interrup��o do timer
}

// Para o timer
void PararTimer() {
    T0CON.TMR0ON = 0; // Desliga o timer
}

// Aumenta o n�mero no display de 7 segmentos
void AumentarNumero7Seg() {
    NumeroAtual7Seg = (NumeroAtual7Seg + 1) % 10; // Incrementa o n�mero no display
    Atualizar7Seg(); // Atualiza o digito no visor
}

// Liga o display de 7 segmentos
void Ligar7Seg() {
    Atualizar7Seg(); // Liga o display
}

// Desliga o display de 7 segmentos
void Desligar7Seg() {
    LATD = 0x00; // Desliga o display
}

// Inicializa as configura��es do display de 7 segmentos
void Inicializar7Seg() {
    TRISD = 0x00;            // Seta a porta D inteira como sa�da
    NumeroAtual7Seg = 0; // Come�a com o display apresentando 0
    Desligar7Seg();        // Por redund�ncia, garante que ele comece desligado
}

void main() {
    ConfigurarTimer(); // Configura o timer
    Inicializar7Seg(); // Inicializa o display
    ConfigurarInterrupcao(); // Configura as interrup��es dos bot�es
}