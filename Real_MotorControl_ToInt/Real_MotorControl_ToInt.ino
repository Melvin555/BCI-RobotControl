int motorrightpositive = 11;
int motorrightnegative = 10;
int motorleftpositive = 6;
int motorleftnegative = 5;
int led = 13;
int i = 0;
int matlab = 0;
long prevmillis = 0;
long currentmillis = 0;
String inString = "";
int inChar;

void setup() 
{
  pinMode(motorrightpositive, OUTPUT);
  pinMode(motorrightnegative, OUTPUT);
  pinMode(motorleftpositive, OUTPUT);
  pinMode(motorleftnegative, OUTPUT);
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {

    prevmillis = millis();
    currentmillis = millis();    
    i = 0;   
    while(currentmillis-prevmillis<3000)  {
      digitalWrite(led, HIGH);
      inChar = Serial.read();
      if (isDigit(inChar)){
        inString += (char)inChar;
      }
      if (inChar == '\n'){
        matlab = inString.toInt();
        inString = "";
      }
      
      if (matlab>=5 && matlab<=9){
        i++;
        matlab = 0;
      }
      if (matlab>2 && matlab <=4){
        digitalWrite(motorrightpositive, HIGH);
        digitalWrite(motorrightnegative, LOW);
        digitalWrite(motorleftpositive, HIGH);
        digitalWrite(motorleftnegative, LOW);
        matlab = 0;
      }
      if (i>3){
        break;
      }

      currentmillis = millis();
    }
    digitalWrite(led, LOW);

    if (i==1){
      digitalWrite(motorrightpositive, LOW);
      digitalWrite(motorleftpositive, LOW);
      delay(300);
      digitalWrite(motorrightpositive, HIGH);
      digitalWrite(motorrightnegative, LOW);
      digitalWrite(motorleftpositive, LOW);
      digitalWrite(motorleftnegative, HIGH);
      delay(300);
      digitalWrite(motorrightpositive, LOW);
      digitalWrite(motorleftnegative, LOW);
    }
    else if (i==2){
      digitalWrite(motorrightpositive, LOW);
      digitalWrite(motorleftpositive, LOW);
      delay(300);
      digitalWrite(motorrightpositive, LOW);
      digitalWrite(motorrightnegative, HIGH);
      digitalWrite(motorleftpositive, HIGH);
      digitalWrite(motorleftnegative, LOW);
      delay(300);
      digitalWrite(motorrightnegative, LOW);
      digitalWrite(motorleftpositive, LOW);    
    }
    else if (i==3){
      digitalWrite(motorrightpositive, LOW);
      digitalWrite(motorleftpositive, LOW);
      delay(300);
      digitalWrite(motorrightpositive, LOW);
      digitalWrite(motorrightnegative, HIGH);
      digitalWrite(motorleftpositive, HIGH);
      digitalWrite(motorleftnegative, LOW);
      delay(1200);
      digitalWrite(motorrightnegative, LOW);
      digitalWrite(motorleftpositive, LOW);    
    }

}
