#define NBDIGITS 8
#define NBDISPLAY 5

#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define G 7
#define H 8
#define DP 9 // F

const int nb_pins[5] = {A1, A2, A3, A4, A5};
const int letter_pins[NBDIGITS] = {A, B, C, D, E, G, H, DP};

String r = "";
int to_print = 0;

void setup() {
  Serial.begin(115200);
  
  for(int i = 0; i < NBDISPLAY; i++){
    pinMode(nb_pins[i], OUTPUT);
    digitalWrite(nb_pins[i], 1);
  }
  for(int i = 0; i < NBDIGITS; i++){
    pinMode(letter_pins[i], OUTPUT);
  }
  
  // Test first display
  /*for(int i = 0; i < 10; i++){
    setDigit(1, i);
    delay(1000);
  }*/
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if(c == '\n'){
      // End of transmission
      to_print = r.toInt();
      r = "";
      Serial.print("->");
      Serial.println(to_print);
    } else if(isDigit(c)) {
      r.concat(c);
      Serial.println(r);
    }
  }
  printNumber(to_print);
}

// Get digit sequence to print a specific number
void setArrayContent(bool* array, bool n1, bool n2, bool n3, bool n4, bool n5, bool n6, bool n7, bool n8){
  bool sequence[NBDIGITS] = {n1,n2,n3,n4,n5,n6,n7,n8};
  for (size_t i = 0; i < NBDIGITS; i++) {
    *array = sequence[i];
    array++;
  }
}

// Get digit sequence to print a specific number
void setSmallArrayContent(bool* array, bool n1, bool n2, bool n3, bool n4, bool n5){
  bool sequence[NBDISPLAY] = {n1,n2,n3,n4,n5};
  for (size_t i = 0; i < NBDISPLAY; i++) {
    *array = sequence[i];
    array++;
  }
}
