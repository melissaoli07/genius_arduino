#include <EEPROM.h>

enum GameState {
  IDLE,
  RUNNING,
  GAME_OVER,
  RESTART
};

enum NivelDificuldade {
  EASY,
  MEDIUM,
  HARD,
  VERY_HARD
};

// Todas as cores que podem ser escolhidas
enum Color {
  RED,
  GREEN,
  BLUE,
  YELLOW,
  NONE_COLOR
};

// Estrutura para salvar quais cores estão ativas
struct RGB {
  bool red;
  bool green;
  bool blue;
  bool yellow;
};

struct SequenciaLeds {
  // tempo espera entre padroes de leds
  int espera;
  RGB rgb[4];
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
int localSalvarEEPROM;
int btn_red_vl;
int btn_blue_vl;
int btn_yellow_vl;
int btn_green_vl;
const int tempoExibirLed = 500;  // em milissegundos
const int dificuldadeInicial = EASY;
const int nivelInicial = 0;
const int tamanhoSequenciaJogoInicial = 1;


// Definicoes de jogo
int clicando = false;
int tamanhoSequenciaJogo = tamanhoSequenciaJogoInicial;
int nivelAtual = nivelInicial;
int recordeAtual = 0;
int maiorRecorde = 0;
GameState state = IDLE;
SequenciaLeds sequencia_idle = {
  100,
  { { HIGH, LOW, HIGH, LOW },
    { LOW, LOW, HIGH, LOW },
    { HIGH, HIGH, HIGH, LOW },
    { LOW, LOW, LOW, HIGH } },
};
NivelDificuldade dificuldade = dificuldadeInicial;
Color* sequenciaCarregada = nullptr;

// Espera o jogador iniciar o jogo
void idle();
// Se o botao especifico for clicado faca algo
bool verificaBotaoEspecificoClicou(Color cor);
// Se algum dos botoes que for clicado retorna true
Color verificaAlgumBotaoClicou();
// Acende a cor enviada por parametro
void emitirSomBotao(Color cor);
// Quando o iniciar o jogo inicia cria a sequencia
Color geraCorAleatoria();
// Verifica se as entradas do usuario estao dentro
// da sequencia gerada
bool verificaSequenciaJogador(Color* sequencia);
// Espera determinado tempo para o jogador escolher uma cor
Color pegarBotaoJogador();
void salvarRecorde();
void atualizarDificuldade();
void exibirSequencia(Color* sequencia);

void setup() {
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
  randomSeed(analogRead(0));

  if(EEPROM.read(0) != 0xff)
  {
    localSalvarEEPROM = EEPROM.read(0);
  }else{
    localSalvarEEPROM = 1;
    EEPROM.write(0, localSalvarEEPROM);
  }
}

void loop() {

  bool resultado;
  Color novaCor;
  Color sequenciaAtual[tamanhoSequenciaJogo];

  switch (state) {
    case IDLE:
      idle();
      break;
    case RUNNING:
      nivelAtual++;
      novaCor = geraCorAleatoria();

      if (sequenciaCarregada != nullptr) {
        for (int i = 0; i < tamanhoSequenciaJogo - 1; i++) {
          sequenciaAtual[i] = sequenciaCarregada[i];
        }
      }

      Serial.println(dificuldade);

      sequenciaAtual[tamanhoSequenciaJogo - 1] = novaCor;

      exibirSequencia(sequenciaAtual);
      resultado = verificaSequenciaJogador(sequenciaAtual);

      if (resultado == false) {
        nivelAtual--;
        state = GAME_OVER;
      }

      if (nivelAtual > recordeAtual) {
        recordeAtual = nivelAtual;
      }

      sequenciaCarregada = sequenciaAtual;
      tamanhoSequenciaJogo++;

      atualizarDificuldade();
      delay(250);
      break;
    case GAME_OVER:
      noTone(BUZZER);
      // caso seja game over, o buzzer apitar e voltar pro estado de jogar - play again
      tone(BUZZER, 262);
      delay(700);
      noTone(BUZZER);
      salvarRecorde();
      state = RESTART;
      break;
    case RESTART:
      // reinicia o jogo para o estado inicial
      // ver alguma forma de mudar o nivel do jogo
      tamanhoSequenciaJogo = tamanhoSequenciaJogoInicial;  // Reset da sequência inicial
      nivelAtual = nivelInicial;
      dificuldade = dificuldadeInicial;  // Volta para a dificuldade inicial
      // sequenciaCarregada = nullptr;
      state = IDLE;  // Coloca o jogo de volta em "espera"
      break;
  };
}

void idle() {
  for (int i = 0; i < 4; i++) {
    if (verificaAlgumBotaoClicou() != NONE_COLOR) {
      state = RUNNING;

      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW);

      delay(500);
      break;
    };

    digitalWrite(LED_RED, sequencia_idle.rgb[i].red);
    delay(sequencia_idle.espera);

    if (verificaAlgumBotaoClicou() != NONE_COLOR) {
      state = RUNNING;

      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW);

      delay(500);
      break;
    };

    digitalWrite(LED_GREEN, sequencia_idle.rgb[i].green);
    delay(sequencia_idle.espera);

    if (verificaAlgumBotaoClicou() != NONE_COLOR) {
      state = RUNNING;

      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW);

      delay(500);
      break;
    };

    digitalWrite(LED_BLUE, sequencia_idle.rgb[i].blue);
    delay(sequencia_idle.espera);

    if (verificaAlgumBotaoClicou() != NONE_COLOR) {
      state = RUNNING;

      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW);

      delay(500);
      break;
    };

    digitalWrite(LED_YELLOW, sequencia_idle.rgb[i].yellow);
    delay(sequencia_idle.espera);

    if (verificaAlgumBotaoClicou() != NONE_COLOR) {
      state = RUNNING;

      digitalWrite(LED_RED, LOW);
      digitalWrite(LED_GREEN, LOW);
      digitalWrite(LED_BLUE, LOW);
      digitalWrite(LED_YELLOW, LOW);

      delay(500);
      break;
    };
  }
}

Color verificaAlgumBotaoClicou() {

  btn_red_vl = digitalRead(BTN_RED);
  btn_blue_vl = digitalRead(BTN_BLUE);
  btn_yellow_vl = digitalRead(BTN_YELLOW);
  btn_green_vl = digitalRead(BTN_GREEN);

  clicando = true;

  if (btn_red_vl == LOW) {
    emitirSomBotao(RED);
    return RED;
  } else if (btn_blue_vl == LOW) {
    emitirSomBotao(BLUE);
    return BLUE;
  } else if (btn_yellow_vl == LOW) {
    emitirSomBotao(YELLOW);
    return YELLOW;
  } else if (btn_green_vl == LOW) {
    emitirSomBotao(GREEN);
    return GREEN;
  }
  clicando = false;

  return NONE_COLOR;
};

bool verificaBotaoEspecificoClicou(Color cor) {
  btn_red_vl = digitalRead(BTN_RED);
  btn_blue_vl = digitalRead(BTN_BLUE);
  btn_yellow_vl = digitalRead(BTN_YELLOW);
  btn_green_vl = digitalRead(BTN_GREEN);

  if (btn_red_vl == LOW && RED == cor) {
    emitirSomBotao(RED);
    return true;
  } else if (btn_blue_vl == LOW && BLUE == cor) {
    emitirSomBotao(BLUE);
    return true;
  } else if (btn_yellow_vl == LOW && YELLOW == cor) {
    emitirSomBotao(YELLOW);
    return true;
  } else if (btn_green_vl == LOW && GREEN == cor) {
    emitirSomBotao(GREEN);
    return true;
  }

  return false;
};

// definir o tamanho da sequencia no parametro e ir definindo/mudando de acordo com o nivel
Color geraCorAleatoria() {
  Color cores[] = { RED, GREEN, YELLOW, BLUE };
  // utiliza o random pra gerar numero aleatorio entre 0 e 3, as 4 cores possiveis e converte para Color
  Color corAleatoria = cores[random(0, 4)];

  return corAleatoria;
}

void emitirSomBotao(Color cor) {
  switch (cor) {
    case RED:
      tone(BUZZER, 262);  // Nota C
      break;
    case GREEN:
      tone(BUZZER, 294);  // Nota D
      break;
    case BLUE:
      tone(BUZZER, 330);  // Nota E
      break;
    case YELLOW:
      tone(BUZZER, 392);  // Nota G
      break;
  }
  delay(100);
  noTone(BUZZER);
}

bool verificaSequenciaJogador(Color* sequencia) {
  Color entradaJogador;
  for (int i = 0; i < tamanhoSequenciaJogo; i++) {
    entradaJogador = pegarBotaoJogador();

    if (entradaJogador == NONE_COLOR || entradaJogador != sequencia[i]) {
      return false;
    }
  }

  return true;
}

Color pegarBotaoJogador() {
  while (true) {
    // Verifica se o botão está sendo clicado
    if (clicando) {
      // Se estiver clicando, espera até que o botão seja solto
      while (clicando) {
        Color corClicada = verificaAlgumBotaoClicou();
        // Aguarda o botão ser solto
      }
    } else {
      // Verifica se algum botão foi clicado
      Color corClicada = verificaAlgumBotaoClicou();
      if (corClicada != NONE_COLOR) {
        return corClicada;
      }
    }
  }
}

void atualizarDificuldade() {
  if (nivelAtual % 4 == 0) {  // Aumenta a dificuldade a cada 5 níveis
    if (dificuldade == EASY)
      dificuldade = MEDIUM;
    else if (dificuldade == MEDIUM)
      dificuldade = HARD;
    else if (dificuldade == HARD)
      dificuldade = VERY_HARD;
  }
}

void salvarRecorde() {
  if (recordeAtual > maiorRecorde) {
    maiorRecorde = recordeAtual;
  }

  EEPROM.write(localSalvarEEPROM, maiorRecorde);
  delay(10);
  localSalvarEEPROM++;
  EEPROM.write(0, localSalvarEEPROM);
  delay(10);

  Serial.print("Game Over! Seu recorde atual foi: ");
  Serial.println(recordeAtual);
  Serial.print("Maior recorde: ");
  Serial.println(maiorRecorde);
}



void exibirSequencia(Color* sequencia) {
  int tempo = floor(tempoExibirLed / (dificuldade * 2 + 1));

  for (int i = 0; i < tamanhoSequenciaJogo; i++) {
    emitirSomBotao(sequencia[i]);
    if (sequencia[i] == RED) {
      digitalWrite(LED_RED, HIGH);
      delay(tempo);
      digitalWrite(LED_RED, LOW);

    } else if (sequencia[i] == BLUE) {
      digitalWrite(LED_BLUE, HIGH);
      delay(tempo);
      digitalWrite(LED_BLUE, LOW);

    } else if (sequencia[i] == GREEN) {
      digitalWrite(LED_GREEN, HIGH);
      delay(tempo);
      digitalWrite(LED_GREEN, LOW);
    } else {
      digitalWrite(LED_YELLOW, HIGH);
      delay(tempo);
      digitalWrite(LED_YELLOW, LOW);
    }
  }
}
