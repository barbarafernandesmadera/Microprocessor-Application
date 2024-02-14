
typedef int Boolean; // Tipo de dado booleano, representado como um inteiro (0 para falso, 1 para verdadeiro)

// Definição de constantes para verdadeiro e falso
#define Verdadeiro 1
#define Falso 0

// Definição dos valores binários para os dígitos no display de 7 segmentos
#define Numero7Seg0 0b00111111 // Representação binária do dígito 0
#define Numero7Seg1 0b00000110 // Representação binária do dígito 1
#define Numero7Seg2 0b01011011 // Representação binária do dígito 2
#define Numero7Seg3 0b01001111 // Representação binária do dígito 3
#define Numero7Seg4 0b01100110 // Representação binária do dígito 4
#define Numero7Seg5 0b01101101 // Representação binária do dígito 5
#define Numero7Seg6 0b01111101 // Representação binária do dígito 6
#define Numero7Seg7 0b00000111 // Representação binária do dígito 7
#define Numero7Seg8 0b01111111 // Representação binária do dígito 8
#define Numero7Seg9 0b01101111 // Representação binária do dígito 9
#define Erro7Seg 0b01111001    // Representação binária do dígito de erro 'E'

// Variável global para controle do número atual no display de 7 segmentos
int NumeroAtual7Seg = -1;

// Funções do display de 7 segmentos
void Inicializar7Seg(); // Inicializa as configurações do display
void AumentarNumero7Seg(); // Incrementa o número no display
void Atualizar7Seg(); // Atualiza o display com o número atual
void Ligar7Seg(); // Liga o display
void Desligar7Seg(); // Desliga o display

// Definição dos tempos do projeto em segundos para o timer
#define TempoModoRapido 0.25f // Tempo para o modo rápido
#define TempoModoLento 1.00f // Tempo para o modo lento

// Variáveis relacionadas ao timer
int TempoAtualInicial = 0; // Tempo atual para o reload do timer
int TempoModoRapidoInicial = 0; // Tempo para o modo rápido
int TempoModoLentoInicial = 0; // Tempo para o modo lento

// Funções do timer
void ConfigurarTimer(); // Configura as opções do timer
void MudarParaModoRapido(); // Altera a velocidade do timer para rápido
void MudarParaModoLento(); // Altera a velocidade do timer para lento
void RecarregarTimer(); // Reinicia a contagem do timer
void IniciarTimer(); // Liga o timer
void PararTimer(); // Para o timer

// Variável global para controle do estado ligado/desligado
Boolean Ligado = Falso;

// Atualiza o display de 7 segmentos com o número atual
void Atualizar7Seg() {
    int displayBinario;
    switch (NumeroAtual7Seg) { // Converte o número atual para a representação binária do display
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
// Função de interrupção de alta prioridade
void InterrupcaoAltaPrioridade() iv 0x0008 ics ICS_AUTO {
    if (INTCON.INT0IF == 1) { // Verifica se houve interrupção do botão RB0
        MudarParaModoLento(); // Muda para o modo lento
        INTCON.INT0IF = 0; // Zera a flag de interrupção
    } else if (INTCON3.INT1IF == 1) { // Verifica se houve interrupção do botão RB1
        MudarParaModoRapido(); // Muda para o modo rápido
        INTCON3.INT1IF = 0; // Zera a flag de interrupção
    }

    RecarregarTimer(); // Recarrega o timer

    if (!Ligado) { // Se não estiver ligado, liga agora
        Ligar7Seg();
        IniciarTimer();
        Ligado = Verdadeiro;
    }
}

// Função de interrupção de baixa prioridade
void InterrupcaoBaixaPrioridade() iv 0x0018 ics ICS_AUTO {
    if (INTCON.TMR0IF == 1) { // Verifica se houve interrupção do timer
        AumentarNumero7Seg(); // Incrementa o número no display
        RecarregarTimer(); // Recarrega o timer
        INTCON.TMR0IF = 0; // Zera a flag de interrupção do timer
    }
}

// Configuração das interrupções
void ConfigurarInterrupcao() {
    ADCON1 |= 0xF; // Configura as portas como digitais
    RCON.IPEN = 1; // Habilita as duas prioridades

    INTCON2.INTEDG0 = 1; // Borda de subida para a interrupção 0
    INTCON2.INTEDG1 = 1; // Borda de subida para a interrupção 1

    INTCON3.INT1IP = 1; // Prioridade alta para a interrupção 1

    INTCON.INT0IF = 0; // Zera a flag de interrupção do botão RB0
    INTCON3.INT1IF = 0; // Zera a flag de interrupção do botão RB1

    INTCON.INT0IE = 1; // Ativa as interrupções para o botão RB0
    INTCON3.INT1IE = 1; // Ativa as interrupções para o botão RB1

    INTCON.GIEL = 1; // Ativa a interrupção de baixa prioridade
    INTCON.GIEH = 1; // Ativa a interrupção de alta prioridade
}

// Configuração do timer
void ConfigurarTimer() {
    T0CON = 0b00000100; // Configurações do timer: 16 bits, clock interno, prescaler 1:32

    INTCON.TMR0IF = 0; // Zera a flag de interrupção do timer
    INTCON2.TMR0IP = 0; // Prioridade baixa para a interrupção do timer
    INTCON.TMR0IE = 1; // Ativa a interrupção do timer

    TempoModoRapidoInicial = 49911; // Valor inicial para o modo rápido
    TempoModoLentoInicial = 3036; // Valor inicial para o modo lento

    TempoAtualInicial = TempoModoLentoInicial; // Valor inicial do timer
}

// Inicia o timer
void IniciarTimer() {
    RecarregarTimer(); // Reinicia a contagem do timer
    T0CON.TMR0ON = 1; // Liga o timer
}

// Muda para o modo rápido
void MudarParaModoRapido() {
    TempoAtualInicial = TempoModoRapidoInicial; // Muda a velocidade da contagem para rápido
}

// Muda para o modo lento
void MudarParaModoLento() {
    TempoAtualInicial = TempoModoLentoInicial; // Muda a velocidade da contagem para lento
}

// Recarrega o timer
void RecarregarTimer() {
    TMR0H = (TempoAtualInicial >> 8); // Configura os bits mais significativos
    TMR0L = TempoAtualInicial; // Configura os bits menos significativos
    INTCON.TMR0IF = 0; // Zera a flag de interrupção do timer
}

// Para o timer
void PararTimer() {
    T0CON.TMR0ON = 0; // Desliga o timer
}

// Aumenta o número no display de 7 segmentos
void AumentarNumero7Seg() {
    NumeroAtual7Seg = (NumeroAtual7Seg + 1) % 10; // Incrementa o número no display
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

// Inicializa as configurações do display de 7 segmentos
void Inicializar7Seg() {
    TRISD = 0x00;            // Seta a porta D inteira como saída
    NumeroAtual7Seg = 0; // Começa com o display apresentando 0
    Desligar7Seg();        // Por redundância, garante que ele comece desligado
}

void main() {
    ConfigurarTimer(); // Configura o timer
    Inicializar7Seg(); // Inicializa o display
    ConfigurarInterrupcao(); // Configura as interrupções dos botões
}