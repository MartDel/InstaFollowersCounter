#define NBDIGITS 8
#define NBDISPLAY 5

#define A 2
#define B 3
#define C 4
#define D 5
#define E 6
#define G 7
#define H 8
#define FF 9

const int nb_pins[5] = {A1, A2, A3, A4, A5};
const int letter_pins[NBDIGITS] = {A, B, C, D, E, G, H, FF};

void setup() {
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
  printNumber(12345);
}

// On/Off letter pins to print a number to the current digit
void setNumber(int n) {
  bool combi[NBDIGITS];
  switch (n) {
    case 1 : setArrayContent(combi, 0,0,1,0,0,1,0,0); break;
    case 2 : setArrayContent(combi, 1,0,1,1,1,0,1,0); break;
    case 3 : setArrayContent(combi, 1,0,1,0,1,1,1,0); break;
    case 4 : setArrayContent(combi, 0,1,1,0,0,1,1,0); break;
    case 5 : setArrayContent(combi, 1,1,0,0,1,1,1,0); break;
    case 6 : setArrayContent(combi, 1,1,0,1,1,1,1,0); break;
    case 7 : setArrayContent(combi, 1,0,1,0,0,1,0,0); break;
    case 8 : setArrayContent(combi, 1,1,1,1,1,1,1,0); break;
    case 9 : setArrayContent(combi, 1,1,1,0,1,1,1,0); break;
    case 0 : setArrayContent(combi, 1,1,1,1,1,1,0,0); break;
    default: setArrayContent(combi, 0,0,0,0,0,0,0,0); break;
  }
  for(int i = 0; i < NBDIGITS; i++){
    digitalWrite(letter_pins[i], combi[i]);
  }
}

// On/Off nb pins to print a number to a specific digit (using setNumber)
void setDigit(int digit, int n) {
  bool combi[NBDISPLAY];
  switch(digit) {
    case 1 : setSmallArrayContent(combi, 0,1,1,1,1); break;
    case 2 : setSmallArrayContent(combi, 1,0,1,1,1); break;
    case 3 : setSmallArrayContent(combi, 1,1,0,1,1); break;
    case 4 : setSmallArrayContent(combi, 1,1,1,0,1); break;
    case 5 : setSmallArrayContent(combi, 1,1,1,1,0); break;
    default: setSmallArrayContent(combi, 0,0,0,0,0); break;
  }
  for(int i = 0; i < NBDISPLAY; i++){
    digitalWrite(nb_pins[i], combi[i]);
    setNumber(n);
  }
  if(digit == 2) digitalWrite(FF, 1);
  else digitalWrite(FF, 0);
}
void printNumber(int n) {
  int dm = n/10000;
  int m = (n-dm*10000)/1000;
  int c = (n-dm*10000-m*1000)/100;
  int d = (n-dm*10000-m*1000-c*100)/10;
  int u = (n-dm*10000-m*1000-c*100-d*10);

  int decompose[5] = {dm,m,c,d,u};
  for(int i = 5; i > 0; i--){
    setDigit(i, decompose[i-1]);
    delay(2);
  }
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

