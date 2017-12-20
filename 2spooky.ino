#define RED 4
#define ORANGE 6
#define YELLOW 7
#define BLUE 10
#define GREEN 12

#define BUTTON A4

enum states {
  OFF = 0,
  NOT_SPOOKY = 1,
  SPOOPY = 2,
  P_SPOOPY = 3,
  SPOOKY = 4,
  TWO_SPOOKY = 5
};

int state = 0;
int waitTime = 0;
int ledState = HIGH;
unsigned long previousMillis = 0;
unsigned long currentMillis = 0;
int color = 0;
bool buttInt = false;  // is the button interruputing?
bool buttLong = false; // is the button long-pressed?
unsigned long buttMillis = 0; // when was button depressed?
unsigned long buttDebounce = 0;
int buttState = HIGH;
int lastButtState = HIGH;

void setup() {
  // initialize pins
  pinMode(RED, OUTPUT);
  pinMode(ORANGE, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);
  
  // LED startup test
  digitalWrite(GREEN, HIGH);
  delay(200);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, HIGH);
  delay(200);
  digitalWrite(BLUE, LOW);
  digitalWrite(YELLOW, HIGH);
  delay(200);
  digitalWrite(YELLOW, LOW);
  digitalWrite(ORANGE, HIGH);
  delay(200);
  digitalWrite(ORANGE, LOW);
  digitalWrite(RED, HIGH);
  delay(200);
  digitalWrite(RED, LOW);
 
}


void loop() {
  currentMillis = millis();
  
  // flash current light
  if(state != OFF && previousMillis + waitTime < currentMillis)
  {
    previousMillis = currentMillis;
    if(ledState == LOW)
    {
      ledState = HIGH;
    }
    else { 
      ledState = LOW;
    }
    digitalWrite(color, ledState);
  }


  buttState = digitalRead(BUTTON);
  if (buttState != lastButtState)
  {
    buttDebounce = currentMillis;
  }
  lastButtState = buttState;


  if(buttState == LOW && currentMillis > buttDebounce + 50)
  {
    buttInt = true;
    if(buttMillis == 0)
    {    
      buttMillis=currentMillis;
    }
    else if(!buttLong && currentMillis > buttMillis + 1000)
    {
      buttLong = true;
      state = OFF;
      digitalWrite(color, LOW);
    }
    
  }
  if(buttState == HIGH && buttInt && currentMillis > buttDebounce + 50) // button released!
  {
    buttMillis = 0;
    buttInt = false;
    if(!buttLong) // has not been switched off
    {
      state = (state + 1) % 6;
      digitalWrite(color, LOW);
      previousMillis = currentMillis;
      switch(state)
      {
        case NOT_SPOOKY:
          color = GREEN;
          waitTime = 1000;
        break;

        case SPOOPY:
          color = BLUE;
          waitTime = 700;
        break;

        case P_SPOOPY:
          color = YELLOW;
          waitTime = 500;
        break;

        case SPOOKY:
          color = ORANGE;
          waitTime = 250;
        break;

        case TWO_SPOOKY:
          color = RED;
          waitTime = 120;
        break;
       
      }
      if(state != OFF)
      {
        digitalWrite(color, HIGH);
        ledState = HIGH;
      }
    }
    buttLong = false;
  }
}
