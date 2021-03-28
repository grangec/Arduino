// des constantes 
const int switchPin = 6;
const int switchMoteurPin = 7;     // Le Pin du switch sur l'axe de rotation
const int moteurPin = 8;

// variables will change:
int etatSwitchMoteur = 0;         // variable for reading the pushbutton status

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(moteurPin, OUTPUT);
  pinMode(switchMoteurPin, INPUT);
  pinMode(switchPin, INPUT);
}

void rotateOne() {
  int start = 0;
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(moteurPin, HIGH);
  // attente de but rotation
  start=millis();
  while(digitalRead(switchMoteurPin)==LOW /*&& ((millis()-start)<500)*/) {delay(50);}
  //attente fin rotation
  start=millis();
  while(digitalRead(switchMoteurPin)==HIGH /*²&& ((millis()-start)<500)*/) {delay(500);}
  digitalWrite(moteurPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if (digitalRead(switchPin)==HIGH) {
    rotateOne();  
  }
}
