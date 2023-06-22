int senal= A0;
int led=13;
float dato;

void setup() {
// put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(senal,INPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  dato=analogRead(senal);
  Serial.println(dato);
  delay(100);

  if(dato<160){
    digitalWrite(led,HIGH);
  }
  else{
    digitalWrite(led,LOW);
  }
}
