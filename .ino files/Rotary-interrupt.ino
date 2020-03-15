// Variable declaration
int count = 0;
int flag = 0;


void setup() {

  Serial.begin(9600);

  pinMode(D3, INPUT);
  pinMode(D4, INPUT);

  // Attach interrupt on pin D4.
  // The ISR function gets called when D4 recieves a LOW pulse
  attachInterrupt(digitalPinToInterrupt(D4), ISR, FALLING);
}

void loop() {
  count = (count > 50) ? 50 : (count = (count < 0) ? 0 : count);        // Restrain value of count between 0-50
  if (flag == 1) {
    Serial.println(count);
    flag = 0;
  }
}


//Interrupt function
ICACHE_RAM_ATTR void ISR() {

  static unsigned long previous = 0;
  unsigned long current = millis();

  if (current - previous > 50)    // Software debouncing the Rotary Encoder
  {
    if (!digitalRead(D3))         // Detects CW rotation (Falling edge of DT corresponds to LOW pulse in CLK)
    {
      count++;                    // Increase the value of count
      flag = 1;                   // Changes flag so that in the loop() function, its value gets printed once
    }
    else if (digitalRead(D3))     // Detects CCW rotation (Falling edge of DT corresponds to HIGH pulse in CLK)
    {
      count--;                    // Decrease the value of count
      flag = 1;                   // Changes flag so that in the loop() function, its value gets printed once
    }
  }
  previous = current;

}
