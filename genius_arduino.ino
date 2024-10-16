enum GameState
{
  IDLE,
  RUNNING,
  GAME_OVER,
  RESTART
};

enum NivelDificuldade
{
  EASY,
  MEDIUM,
  HARD,
  VERY_HARD
};

enum Color
{
  RED,
  GREEN,
  BLUE,
  YELLOW
};

struct RGB
{
  bool red;
  bool green;
  bool blue;
  bool yellow;
};

struct SequenciaLeds
{
  // tempo espera entre padroes de leds
  int espera;
  //usar ponteiro
  RGB rgb[]; 
};

struct Nivel
{
  int numero_nivel;
  //usar ponteiro
  RGB sequencia[];  
};





// Leds
const int LED_RED = 6;
const int LED_BLUE = 7;
const int LED_YELLOW = 8;
const int LED_GREEN = 9;

// Buttons
const int BTN_RED = 4;
const int BTN_BLUE = 5;
const int BTN_YELLOW = 10;
const int BTN_GREEN = 11;

// Buzzer
const int BUZZER = 12;

// Variaveis globais
int btn_red_vl;
int btn_blue_vl;
int btn_yellow_vl;
int btn_green_vl;
int tempo_resposta_jogador = 300; // em milissegundos
int tamanhoSenquenciaJogo = 4;
RGB sequenciaJogo[4];
int nivelAtual = 1; 
int recordeAtual = 0;
int maiorRecorde = 0;


// Definicoes de jogo
GameState state = IDLE;
SequenciaLeds sequencia_idle = {
    100,
    {{true, false, true, false},
     {false, false, true, false},
     {true, true, true, false},
     {false, false, false, true}},
};
NivelDificuldade dificuldade = EASY;

// Espera o jogador iniciar o jogo
void idle();
bool verificaBotaoEspecificoClicou(Color cor);
// Se algum dos botoes que for clicado retorna true
bool verificaAlgumBotaoClicou();
// Acende a cor enviada por parametro
void onBtnClick(Color cor);
// Quando o iniciar o jogo inicia cria a sequencia
void criarSequenciaJogador(RGB arr[], int tamanhoSequencia); // criarSequenciaJogo ou criarSequencia ?
// Verifica se as entradas do usuario estao dentro
// da sequencia gerada
bool verificaSequenciaJogador(RGB sequencia);

void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  pinMode(BTN_RED, INPUT_PULLUP);
  pinMode(BTN_BLUE, INPUT_PULLUP);
  pinMode(BTN_YELLOW, INPUT_PULLUP);
  pinMode(BTN_GREEN, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);

  Serial.begin(9600);
}

void loop()
{
  RGB sequencia[tamanhoSenquenciaJogo];
  bool errou;
  switch (state)
  {
  case IDLE:
    idle();
    break;
  case RUNNING:
    criarSequenciaJogador(sequenciaJogo, tamanhoSenquenciaJogo); // gera uma nova sequência
    for (int i = 0; i < tamanhoSenquenciaJogo; i++) {
        digitalWrite(LED_RED, sequenciaJogo[i].red);
        digitalWrite(LED_GREEN, sequenciaJogo[i].green);
        digitalWrite(LED_BLUE, sequenciaJogo[i].blue);
        digitalWrite(LED_YELLOW, sequenciaJogo[i].yellow);
        delay(tempo_resposta_jogador); // mostra a cor por um tempo
    // desliga os LEDs entre as cores
        digitalWrite(LED_RED, LOW);
        digitalWrite(LED_GREEN, LOW);
        digitalWrite(LED_BLUE, LOW);
        digitalWrite(LED_YELLOW, LOW);
        delay(200);
    }

  // verifica a entrada do jogador
    if (verificaSequenciaJogador(sequenciaJogo, tamanhoSenquenciaJogo)) {
        tamanhoSenquenciaJogo++; // aumenta o tamanho da sequência para o próximo nível
        nivelAtual++;  
        atualizarDificuldade(nivelAtual);
    } else {
        state = GAME_OVER; // se o jogador errar
    }
    break;
  case GAME_OVER:
    // caso seja game over, o buzzer apitar e voltar pro estado de jogar - play again
    salvarRecorde(); 
    digitalWrite(BUZZER, HIGH);
    delay(1000);
    digitalWrite(BUZZER, LOW);
    state = RESTART;
    break;
  case RESTART:
    // reinicia o jogo para o estado inicial
    // ver alguma forma de mudar o nivel do jogo
    tamanhoSenquenciaJogo = 4; // Reset da sequência inicial
    dificuldade = EASY; // Volta para a dificuldade inicial
    state = IDLE; // Coloca o jogo de volta em "espera"
    break;
  };

  // btn_red_vl = digitalRead(BTN_RED);
  // btn_blue_vl = digitalRead(BTN_BLUE);
  // btn_yellow_vl = digitalRead(BTN_YELLOW);
  // btn_green_vl = digitalRead(BTN_GREEN);
}







bool verificaSequenciaJogador(RGB sequencia[], int tamanhoSequencia){
    for (int i = 0; i < tamanhoSequencia; i++) {
        if (!verificaBotaoEspecificoClicou(sequencia[i])) {
          return false; 
        }
        delay(200); // tempo para o próximo input do jogador
    }
    return true; 
  }
     

 



void idle()
{

  for (int i = 0; i < 4; i++)
  {
    if (verificaAlgumBotaoClicou())
    {
      state = RUNNING;

      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW);
      break;
    };

    digitalWrite(LED_RED, sequencia_idle.rgb[i].red);
    delay(sequencia_idle.espera);

    digitalWrite(LED_GREEN, sequencia_idle.rgb[i].green);
    delay(sequencia_idle.espera);

    digitalWrite(LED_BLUE, sequencia_idle.rgb[i].blue);
    delay(sequencia_idle.espera);

    digitalWrite(LED_YELLOW, sequencia_idle.rgb[i].yellow);
    delay(sequencia_idle.espera);
  }
}

bool verificaAlgumBotaoClicou()
{

  btn_red_vl = digitalRead(BTN_RED);
  btn_blue_vl = digitalRead(BTN_BLUE);
  btn_yellow_vl = digitalRead(BTN_YELLOW);
  btn_green_vl = digitalRead(BTN_GREEN);

  if (btn_red_vl == LOW or btn_blue_vl == LOW or btn_yellow_vl == LOW or btn_green_vl == LOW)
  {
    return true;
  }

  return false;
};

bool verificaBotaoEspecificoClicou(Color cor)
{
  btn_red_vl = digitalRead(BTN_RED);
  btn_blue_vl = digitalRead(BTN_BLUE);
  btn_yellow_vl = digitalRead(BTN_YELLOW);
  btn_green_vl = digitalRead(BTN_GREEN);

  if (btn_red_vl == LOW and RED == cor)
  {
    return true;
  }
  else if (btn_blue_vl == LOW && BLUE == cor)
  {
    return true;
  }
  else if (btn_yellow_vl == LOW && YELLOW == cor)
  {
    return true;
  }
  else if (btn_green_vl == LOW && GREEN == cor)
  {
    return true;
  }

  return false;
};

// definir o tamanho da sequencia no parametro e ir definindo/mudando de acordo com o n├¡vel
void criarSequenciaJogador(RGB arr[], int tamanhoSequencia){
  for (int i = 0; i < tamanhoSenquencia; i++){
    int corAleatoria = random(0, 4);
    switch (corAleatoria) {
      case 0:
        arr[i] = {true, false, false, false}; // RED
        break;
      case 1:
        arr[i] = {false, true, false, false}; // GREEN
        break;
      case 2:
        arr[i] = {false, false, true, false}; // BLUE
        break;
      case 3:
        arr[i] = {false, false, false, true}; // YELLOW
        break;
    }
  }
}



void onBtnClick(Color cor)
{
  // switch (cor) {
  //     case RED:
  //         tone(BUZZER, 262); // Nota C
  //         break;
  //     case GREEN:
  //         tone(BUZZER, 294); // Nota D
  //         break;
  //     case BLUE:
  //         tone(BUZZER, 330); // Nota E
  //         break;
  //     case YELLOW:
  //         tone(BUZZER, 392); // Nota G
  //         break;
  // }
  delay(200);
  noTone(BUZZER);
}


void atualizarDificuldade(int nivel) {
  if (nivel % 5 == 0) { // Aumenta a dificuldade a cada 5 níveis
    if (dificuldade == EASY) dificuldade = MEDIUM;
    else if (dificuldade == MEDIUM) dificuldade = HARD;
    else if (dificuldade == HARD) dificuldade = VERY_HARD;
  }

  if (nivel % 3 == 0) { // Aumenta o tamanho da sequência a cada 3 níveis
    tamanhoSenquenciaJogo++;
  }
}




void salvarRecorde() {
    if (recordeAtual > maiorRecorde) {
        maiorRecorde = recordeAtual;  
    }
    Serial.print("Game Over! Seu recorde atual foi: ");
    Serial.println(recordeAtual);
    Serial.print("Maior recorde: ");
    Serial.println(maiorRecorde);
}
