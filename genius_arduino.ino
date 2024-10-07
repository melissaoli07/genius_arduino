enum GameState
{
  START,
  RUNNING,
  GAME_OVER,
  PLAY_AGAIN
};

enum NivelDificuldade
{
  EASY = 0,
  MEDIUM = 1,
  HARD = 2,
  VERY_HARD = 3
}

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
  // tempo espera entre padrão de leds
  int espera;
  RGB rgb[];
};

struct SequenciaJogo
{
  Color cores[];
};

struct Nivel
{
  int numero_nivel;
  int vel = 1;
  Sequencia sequencia[];
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

// Definições de jogo
GameState state = START;
SequenciaLeds sequencia_idle = {
  100,
  {
    {true, false, true, false},
    {false, false, true, false},
    {true, true, true, false},
    {false, false, false, true}
  },
};
NivelDificuldade dificuldade = EASY;


// Espera o jogador iniciar o jogo
void idle();
bool verificaBotaoEspecificoClicou(Color cor);
// Se algum dos botoes for clicado retorna true
bool verificaAlgumBotaoClicou();
// Acende a cor enviada por parametro
void onBtnClick();
// Quando o iniciar o jogo inicia cria a sequencia
SequenciaJogo criarSequenciaJogo();
// Verifica se as entradas do usuario estão dentro 
// da sequencia gerada
bool verificaSequenciaJogador(SequenciaJogo sequencia);


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
  switch (state)
  {
  case START:
    idle();
    break;
  case RUNNING:
    SequenciaJogo sequencia = criarSequencia();
    bool errou = verificarSequenciaJogador(sequencia);
    break;
  case GAME_OVER:
    break;
  case PLAY_AGAIN:
    break;
  };
  
  // btn_red_vl = digitalRead(BTN_RED);
  // btn_blue_vl = digitalRead(BTN_BLUE);
  // btn_yellow_vl = digitalRead(BTN_YELLOW);
  // btn_green_vl = digitalRead(BTN_GREEN);
}



void idle()
{
  
  for(int i = 0; i < 4; i++)
  {
    if(verificaAlgumBotaoClicou()){
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
  
  if (btn_red_vl == LOW 
      or btn_blue_vl == LOW
      or btn_yellow_vl == LOW
      or btn_green_vl == LOW)
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
  }else if( btn_blue_vl == LOW && BLUE == cor)
  {
    return true;
  }else if(btn_yellow_vl == LOW && YELLOW == cor)
  {
    return true;
  }else if(btn_green_vl == LOW && GREEN == cor)
  {
    return true;
  }
  
  return false;
  
};

SequenciaJogo criarSequencia()
{
  SequenciaJogo sequencia;
  
  for (int i = 0; i < 4; i++)
  {
    sequencia.cores[i] = ;
  }
  
  return sequencia;
}
