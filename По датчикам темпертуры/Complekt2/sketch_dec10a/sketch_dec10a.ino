void setup() {

  // put your setup code here, to run once:

  Serial.begin(9600);
  // работаем без [] скобок
  byte myArray[] = {1, 2, 3, 4, 5};
  // выведет 1 2 3 4 5
  for (byte i = 0; i < 5; i++) {
    Serial.print(*(myArray + i));
    Serial.print(' ');
  }
  
  Serial.println();
  // работаем с отдельным указателем
  int myArray2[] = {10, 20, 30, 40, 50};
  int* ptr2 = myArray2; // указатель на массив
  // выведет 10 20 30 40 50
  for (byte i = 0; i < 5; i++) {
    Serial.print(*ptr2);
    ptr2++;
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();

  // работаем с отдельным указателем
  //int myArray3[] = {110, 120, 130, 140, 150, 160};

  int myArray3 [2][3] = 
  {
    {110,120,130},
    {140,150,160}
  }; 
  
  int* ptr3 = myArray3; // указатель на массив
  
  for (byte i = 0; i < 6; i++) 
  {
    Serial.print(*ptr3);
    ptr3++;
    Serial.print(' ');
  }

}

void loop() {
  // put your main code here, to run repeatedly:

}
