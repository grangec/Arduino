#include <RCSwitch.h>

// Des constantes
const int switchPin = 6;  // bouton poussoir pour un tour moteur
const int switchMoteurPin = 7;     // Le Pin du switch sur l'axe de rotation
const int moteurPin = 8;  // le moteur
const int RCPin = 2; //Le PIN du RC 433Mhz (doit etre 2)

// variables will change:
int etatSwitchMoteur = 0;         // variable for reading the pushbutton status

// Recepteur RF 433
RCSwitch mySwitch = RCSwitch();

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  // Controle moteur + switchMoteur + bouton poussoir
  pinMode(moteurPin, OUTPUT);
  pinMode(switchMoteurPin, INPUT);
  pinMode(switchPin, INPUT);

  // Parametrage RF 433 
  Serial.begin(9600);
  mySwitch.enableReceive(0);  // Receiver on interrupt 0 => that is pin #2
}

void rotateOne() {
  // Faire faire un tour au moteur.
  int start = 0;
  digitalWrite(LED_BUILTIN, HIGH);
  digitalWrite(moteurPin, HIGH);
  // attente de but rotation
  start = millis();
  while (digitalRead(switchMoteurPin) == LOW /*&& ((millis()-start)<500)*/) {
    delay(50);
  }
  //attente fin rotation
  start = millis();
  while (digitalRead(switchMoteurPin) == HIGH /*²&& ((millis()-start)<500)*/) {
    delay(100);
  }
  digitalWrite(moteurPin, LOW);
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  // Bouton nourrir local
  if (digitalRead(switchPin) == HIGH) {
    rotateOne();
  }

  if (mySwitch.available()) {
    int val = mySwitch.getReceivedValue();
    int bitLength = mySwitch.getReceivedBitlength();
    int protocol = mySwitch.getReceivedProtocol();

    // Log les valeurs reçues.
    Serial.print("Received ");
    Serial.print( val );
    Serial.print(" / ");
    Serial.print( bitLength );
    Serial.print("bit ");
    Serial.print("Protocol: ");
    Serial.println( protocol );

    // Push On Button dans mon Domoticz
    if(val==21 && bitLength==24 && protocol==1) {
      rotateOne();
    }

    mySwitch.resetAvailable();
  }
}
