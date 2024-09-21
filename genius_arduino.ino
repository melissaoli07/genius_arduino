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

int btn_red_vl;
int btn_blue_vl;
int btn_yellow_vl;
int btn_green_vl;

enum GameState
{
  START,
  RUNNING,
  GAME_OVER,
  PLAY_AGAIN
};

struct Level
{
  int numero_level;
  int sequencia;
};

GameState state = START;

// Gera as sequencia
void idle();
// Acende a cor enviada por parametro
void onBtnClick(char cor[]);
void init();

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
  btn_red_vl = digitalRead(BTN_RED);
  btn_blue_vl = digitalRead(BTN_BLUE);
  btn_yellow_vl = digitalRead(BTN_YELLOW);
  btn_green_vl = digitalRead(BTN_GREEN);

  switch (state)
  {
  case START:
    break;
  case RUNNING:
    break;
  case GAME_OVER:
    break;
  case PLAY_AGAIN:
    break;
  };
}

void idle()
{
  if (btn_red_vl == LOW)
  {
    digitalWrite(LED_RED, HIGH);
    tone(BUZZER, 100);
    delay(100);
    noTone(BUZZER);
    digitalWrite(LED_RED, LOW);
  }
  else if (btn_blue_vl == LOW)
  {
    digitalWrite(LED_BLUE, HIGH);
    tone(BUZZER, 500);
    delay(100);
    noTone(BUZZER);
    digitalWrite(LED_BLUE, LOW);
  }
  else if (btn_yellow_vl == LOW)
  {
    digitalWrite(LED_YELLOW, HIGH);
    tone(BUZZER, 880);
    delay(100);
    noTone(BUZZER);
    digitalWrite(LED_YELLOW, LOW);
  }
  else if (btn_green_vl == LOW)
  {
    digitalWrite(LED_GREEN, HIGH);
    tone(BUZZER, 764);
    delay(100);
    noTone(BUZZER);
    digitalWrite(LED_GREEN, LOW);
  }
}