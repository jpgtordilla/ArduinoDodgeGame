// Buttons

const int ButtonUp = 2; 
const int ButtonDown = 3; 
int ButtonUpState = 0;
int ButtonDownState = 0; 
int buttonCounter = 0; 
char lastButton = 'd'; 

// Player 

const int PlayerLedDown = 13; 
const int PlayerLedUp = 12; 
//  | P | 1 | 2 | 3 | 4 | 
//  | P | 1 | 2 | 3 | 4 | 

// NPC 

// NPC up LEDs
const int NPCLed1Up = 7; 
const int NPCLed2Up = 6; 
const int NPCLed3Up = 5; 
const int NPCLed4Up = 4; 
// NPC down LEDs
const int NPCLed1Down= 11; 
const int NPCLed2Down = 10; 
const int NPCLed3Down = 9; 
const int NPCLed4Down = 8; 
const int NPCLEDs[] = {NPCLed1Up, NPCLed2Up, NPCLed3Up, NPCLed4Up, 
                      NPCLed1Down, NPCLed2Down, NPCLed3Down, NPCLed4Down}; 
// NPC variables
int NPCSpeed = 50; // number of frames to wait between moving 
int NPCCounter = 0; // number of frames elapsed for moving NPC 
bool generateNPC = true; 
int NPCX = 4; 
int NPCY = 1; // up, 0 is down

void setup() {
  pinMode(ButtonUp, INPUT); 
  pinMode(ButtonDown, INPUT); 
  pinMode(PlayerLedDown, OUTPUT); 
  pinMode(PlayerLedUp, OUTPUT); 
  for (int i = 4; i <= 11; i++) {
    pinMode(i, OUTPUT); 
  }
}

void loop() { 
  // turn off all NPC LEDs
  for (int i = 0; i <= 7; i++) {
    digitalWrite(NPCLEDs[i], LOW); 
  }
  // turn off the up player LED if the last button pressed was not the up LED
  if (lastButton != 'u' && digitalRead(PlayerLedUp) == HIGH) {
    digitalWrite(PlayerLedUp, LOW); 
  }
  // similar for down player LED
  else if (lastButton != 'd' && digitalRead(PlayerLedDown) == HIGH) {
    digitalWrite(PlayerLedDown, LOW); 
  }

  // game over condition
  if (NPCX == 0 && NPCY == 1 && lastButton == 'u') {
    gameOver(); 
  }
  if (NPCX == 0 && NPCY == 0 && lastButton == 'd') {
    gameOver(); 
  }

  // if the NPC is moved all the way to the left, generate a new NPC
  if (NPCX < 0) {
    generateNPC = true; 
  }
  if (generateNPC) {
    NPCX = 4; 
    NPCY = random(0, 2); // pick either the up or down row randomly
    generateNPC = false; 
  }

  // determine which LED to turn on
  // upper row
  if (NPCX == 0 && NPCY == 1 && ButtonUpState == LOW) {
    digitalWrite(PlayerLedUp, HIGH); 
  }
  if (NPCX == 1 && NPCY == 1) {
    digitalWrite(NPCLed1Up, HIGH); 
  }
  else if (NPCX == 2 && NPCY == 1) {
    digitalWrite(NPCLed2Up, HIGH); 
  }
  else if (NPCX == 3 && NPCY == 1) {
    digitalWrite(NPCLed3Up, HIGH); 
  }
  else if (NPCX == 4 && NPCY == 1) {
    digitalWrite(NPCLed4Up, HIGH); 
  }
  // lower row
  else if (NPCX == 0 && NPCY == 0 && ButtonDownState == LOW) {
    digitalWrite(PlayerLedDown, HIGH); 
  }
  else if (NPCX == 1 && NPCY == 0) {
    digitalWrite(NPCLed1Down, HIGH); 
  }
  else if (NPCX == 2 && NPCY == 0) {
    digitalWrite(NPCLed2Down, HIGH); 
  }
  else if (NPCX == 3 && NPCY == 0) {
    digitalWrite(NPCLed3Down, HIGH); 
  }
  else if (NPCX == 4 && NPCY == 0) {
    digitalWrite(NPCLed4Down, HIGH); 
  }
  
  // initially, set down LED to be on 
  if (buttonCounter == 0) {
    ButtonDownState == HIGH; 
    digitalWrite(PlayerLedDown, HIGH); 
  }

  // if up button is pressed, switch to up LED
  ButtonUpState = digitalRead(ButtonUp); 
  if(ButtonUpState == HIGH) {
    lastButton = 'u'; 
    buttonCounter++; 
    digitalWrite(PlayerLedUp, HIGH); 
    ButtonDownState = LOW; 
    if (NPCX != 0 || NPCY != 0) { // de morgan's law
      digitalWrite(PlayerLedDown, LOW); 
    }
  }

  // if down button is pressed, switch to down LED
  ButtonDownState = digitalRead(ButtonDown); 
  if(ButtonDownState == HIGH) {
    lastButton = 'd'; 
    buttonCounter++; 
    digitalWrite(PlayerLedDown, HIGH); 
    ButtonUpState = LOW; 
    if (NPCX != 0 || NPCY != 1) { // de morgan's law
      digitalWrite(PlayerLedUp, LOW); 
    }
  }

  NPCCounter++; // count frames
  // if the number of frames elapsed is greater than the speed parameter
  if (NPCCounter > NPCSpeed) {
    NPCCounter = 0; 
    NPCX--; 
    if (NPCSpeed > 15) {
      // decrease speed with each count
      NPCSpeed -= 1; 
    }
  }
  if (buttonCounter > 100) {
    buttonCounter = 1; 
  }
  delay(10); // 100 fps
}

void gameOver() {
  // turn on all lights
  for (int i = 0; i <= 7; i++) {
    digitalWrite(NPCLEDs[i], HIGH); 
  }
  digitalWrite(PlayerLedUp, HIGH); 
  digitalWrite(PlayerLedDown, HIGH); 
  delay(30); 
  NPCSpeed = 50; 
}
