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
  if(digit == 2) digitalWrite(DP, 1);
  else digitalWrite(DP, 0);
}

// Print a number to digits displays
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
