int both = 10;

void setup() {
  Serial.begin(9600);
  Serial.println("Hello, World!");
  for(int i=0; i<10; i++) {
    Serial.println(i);delay(100);
    }
    Serial.println(both);
  /* --------------
      Task 2
  int c=7/4;
  float d=7/4;
  float a=7.0/4;
  float b=7.0/4.0;
  float f=(float)7/4;
  float e=(float)(7/4);
  int g=2/3.0;

  Serial.println (c);
  delay(100);
  Serial.println (a);
  delay(100);
  Serial.println (b);
  delay(100);
  Serial.println (f);
  delay(100);
  Serial.println (e);
  delay(100);
  Serial.println (g);

  */

  /* --------------
      Task 3

  Serial.println(++c);
  Serial.println(c);
  Serial.println(c++);
  Serial.println(c);
  */

  /* -------------- 
      Task 4

  int y = 0;
  int x = 5;
  Serial.println(x);
  
  x += 3;
  Serial.print("x += 3: ");Serial.println(x);
  x -= 4;
  Serial.print("x -+ 4: ");Serial.println(x);

//  x \*= 20; NOT POSSIBLE

  x /= 4;
  Serial.print("x /= 4: ");Serial.println(x);
  y = ++x;
  Serial.print("y = ++x: ");Serial.println(y);Serial.println(x);
  y = x--;
  Serial.print("y = x--: ");Serial.println(y);Serial.println(x);

  */

  

}

void loop() {
  Serial.println(both++);
  delay(500);

}
