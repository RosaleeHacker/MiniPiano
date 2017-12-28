//buttons and touch sensors
int button = A3; //analog pin 3
int touch0 = A0; //analog pin 0
int touch1 = A1; //analog pin 1
int touch4 = 4; //digital D4/D5
int touch6 = 6; //digital D6/D7
int touch7 = 7; //digital D7/D8

//speakers
int speakerPin0 = 0; //digital D0/D1
int speakerPin1 = 1; //digital D1/D2
int speakerPin2 = 2; //digital D2/D3
int speakerPin3 = 3; //digital D3/D4
int speakerPin8 = 8; //digital D8/D9
bool playing = false;

//notes and beats
//plays the beginning of the song Welcome to the Black Parade by My Chemical Romance
int length = 11; //the number of notes
String notes[] = {"G5","FS5","B5","E5","D5","G5","C4","B4","E5","A4","D5"};
int beats[] = {4,2,2,4,2,2,4,2,2,4,4};
int tempo = 300;
struct color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

//method for playing tone, takes in a tone, duration and speaker
void playTone(int tone, int duration,int speaker) {
  for (long i=0; i < duration * 1000L; i += tone*2) {
    digitalWrite(speaker,HIGH);
    delayMicroseconds(tone);
    digitalWrite(speaker,LOW);
    delayMicroseconds(tone);
  }
}

//sets notes to frequencies, sets a color to them as well.
//the loop sets the colors to the notes and calls the playTone method
void playNote(String note, int duration) {
  String names[] = {"G5","FS5","B5","E5","D5","C4","B4","A4","D5"};
  int tones[] = {784,740,988,659,587,262,494,440,587};
  color colors[] = {{255,0,0},{244,244,66},{66,182,244},{0,255,0},{143,66,244},{244,66,241},{146,244,66},{0,0,255}};

  for(int i =0; i < 8; i++) {
    if (names[i] == note) {
      Bean.setLed(colors[i].r,colors[i].g,colors[i].b);
      playTone(tones[i],duration,speakerPin0);
      Bean.setLed(0,0,0);
    }
  }
}

//sets sensors to inputs and outputs
void setup() {
  pinMode(button,INPUT);
  pinMode(touch0,INPUT);
  pinMode(touch1,INPUT); 
  pinMode(touch4,INPUT);
  pinMode(touch6,INPUT);
  pinMode(touch7,INPUT);
  pinMode(speakerPin0,OUTPUT);
  pinMode(speakerPin1,OUTPUT);
  pinMode(speakerPin2,OUTPUT);
  pinMode(speakerPin3,OUTPUT);
  pinMode(speakerPin8,OUTPUT);

}

//loop that runs actions from sensors
void loop() {
//NOTE C4
  if(digitalRead(touch0) == 1) {
    playTone(262,500,speakerPin0);
    Bean.setLed(255,0,0);
    playing = true;
  }

//NOTE D4
  if(digitalRead(touch1) == 1) {
    playTone(294,500,speakerPin1);
    Bean.setLed(0,255,0);
    playing = true;
  }

//NOTE E4
  if(digitalRead(touch4) == 1) {
    playTone(330,500,speakerPin2);
    Bean.setLed(0,0,255);
    playing = true;
  }

//NOTE G4
  if(digitalRead(touch6) == 1) {
    playTone(392,500,speakerPin3);
    Bean.setLed(255,0,255);
    playing = true;
  }

//NOTE A4
  if(digitalRead(touch7) == 1) {
    playTone(440,500,speakerPin8);
    Bean.setLed(252, 93, 153);
    playing = true;
  }

  //plays the notes as long as there's something reading from the touch sensors and button
  for (int i = 0; i < length && digitalRead(button) == 1; i++) {
    if (notes[i] == " ") {
      Bean.setLed(0,0,0);
      delay(beats[i]*tempo);
    } else {
      playNote(notes[i], beats[i]*tempo);
    }    //pause between notes

    delay(tempo/2);
  }
}




