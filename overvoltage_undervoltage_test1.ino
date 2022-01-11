byte batterIP0 = A0;
byte batterIP1 = A1;
byte batterIP2 = A2;
byte batterIP3 = A3;
const int MOS = 4;
const int selectPins[3] = {7, 6, 5};
int sensePin = A5;
int sensorInput;    
double temp;        
float voltage0;
float voltage1;
float voltage2;
float voltage3;
float current;




void setup()
{
  pinMode(batterIP0, INPUT);
  pinMode(batterIP1, INPUT);
  pinMode(batterIP2, INPUT);
  pinMode(batterIP3, INPUT);
  pinMode(MOS, OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  int readValue0 = analogRead(A0);
  int readValue1 = analogRead(A1);
  int readValue2 = analogRead(A2);
  int readValue3 = analogRead(A3);
  digitalWrite(4,LOW);
  digitalWrite(5,LOW);
  digitalWrite(6,LOW);
  float totalvoltage = voltage0+voltage1+voltage2+voltage3;
  voltage0 = readValue0*(5.0/1023.0);
  voltage1 = readValue1*(5.0/1023.0);
  voltage2 = readValue2*(5.0/1023.0);
  voltage3 = readValue3*(5.0/1023.0);
  current = voltage3/62.745;
  for (byte pin=0; pin<=3; pin++)
  {
    selectMuxPin(pin); // Select one at a time
    int inputValue = analogRead(A5); // and read Z
    temp = (double)sensorInput / 1024;       //find percentage of input reading
    temp = temp * 5;                 //multiply by 5V to get voltage
    temp = temp - 0.5;               //Subtract the offset 
    temp = temp * 100;               //Convert to degrees 


}
  Serial.print("Current Temperature: ");
  Serial.println(temp);
  Serial.print("Voltage1 = ");
  Serial.println(voltage0);
  Serial.print("Voltage2 = ");
  Serial.println(voltage1);
  Serial.print("Voltage3 = ");
  Serial.println(voltage2);
  Serial.print("Voltage4 = ");
  Serial.println(voltage3);
  Serial.print("Total Voltage = ");
  Serial.println(totalvoltage); 
  Serial.print("Total Current = ");
  Serial.println(current); 
                 
  if (voltage0 > 3.8 || voltage0 < 2.5){
    digitalWrite(MOS,LOW);
    if (voltage0 < 2.5){
      Serial.println("UNDERVOLTAGE at 1");
    }
    else{
      Serial.println("OVERVOLTAGE at 1");
    }
  }
  else if ((voltage1 > 3.8)||(voltage1 < 2.5)){
    digitalWrite(MOS,LOW);
    if (voltage1 < 2.5){
      Serial.println("UNDERVOLTAGE at 2");
    }
    else{
      Serial.println("OVERVOLTAGE at 2");
    }
  
  }
  else if (voltage2 > 3.8 ||(voltage2 < 1.2)){
    digitalWrite(MOS,LOW);
    if (voltage2 < 1.2){
      Serial.println("UNDERVOLTAGE at 3");
    }
    else{
      Serial.println("OVERVOLTAGE at 3");
    }
  
  }
  else if (voltage3>3.8||(voltage3< 1.2)){
    digitalWrite(MOS,LOW);
    if(voltage3 < 1.2){
      Serial.println("UNDERVOLTAGE at 4");
    }
    else{
      Serial.println("OVERVOLTAGE at 4");
    }
  }
  else if (totalvoltage>13){
    Serial.println("OVERVOLTAGE DETECTED RUN FOR YOUR LIFE");
  }
  else{
    digitalWrite(MOS,HIGH);
 
  }
}
void selectMuxPin(byte pin)
{
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
