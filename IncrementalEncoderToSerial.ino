#define pin_encoderSignalA_Interrupt0 2 // encoder A signal
#define pin_encoderSignalZ_Interrupt0 3 // encoder Z signal
#define pin_encoderSignalB 4 //            encoder B signal

volatile int i = 0;
volatile int t = 0;

long time;

int impByTurn = 360;
long period_ms = 200;
int direction = 1; //1 ou -1
int floatprecision = 3;
bool printTime = false;

const unsigned int MAX_MESSAGE_LENGTH = 40;

void setup() {
  Serial.begin(9600);

  pinMode(pin_encoderSignalA_Interrupt0, INPUT_PULLUP);
  pinMode(pin_encoderSignalZ_Interrupt0, INPUT_PULLUP);
  pinMode(pin_encoderSignalB, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pin_encoderSignalA_Interrupt0), OnFallingSignalA, FALLING);
  attachInterrupt(digitalPinToInterrupt(pin_encoderSignalZ_Interrupt0), OnFallingSignalZ, FALLING);

  PrintStart();
  PrintParameters();
}

void loop(){
  if (millis() > time)
  {    
    time += period_ms;

    float turn = t + (float)i / 360;
    if (printTime) {
      Serial.print(time);
      Serial.print("\t");
    }
    Serial.println(turn, floatprecision);
  }
  else
  {
    String m = SerialRead();
    if (m != "")
      SetParameters(m);
  }
}

String SerialRead(){
  //Check to see if anything is available in the serial receive buffer
  while (Serial.available() > 0)
  {
    //Create a place to hold the incoming message
    static char message[MAX_MESSAGE_LENGTH];
    static unsigned int message_pos = 0;
    //Read the next available byte in the serial receive buffer
    char inByte = Serial.read();
    //Message coming in (check not terminating character) and guard for over message size
    if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) )
    {
      //Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
    }
    //Full message received...
    else
    {
      //Add null character to string
      message[message_pos] = '\0';
      //Print the message (or do other things)
      //Reset for the next message
      message_pos = 0;
      //Serial.println(message);
      return message;      
    }
  }
  return "";
}

void OnFallingSignalA(){ // encoder A signal
  if (digitalRead(pin_encoderSignalB))
    i -= direction;
  else
    i += direction;
}

void OnFallingSignalZ(){ // encoder Z signal => 1 turn
  if (digitalRead(pin_encoderSignalB))
  {   
    t -= direction; 
    i = impByTurn - 1;
  }
  else
  {
    t += direction;
    i = 0;
  }
}

void SetParameters(String m){
  char command = m[0];  
  m.remove(0, 1); // retire le 1er charactère de la chaîne
  int val = m.toInt();

  switch(command)
  {

    case 'd': //direction
      if (val == 1)
        direction = 1;
      else
        direction = -1;
      break;  

    case 'f': //float precision when serial printed
      if (val > 0)
        floatprecision = val;
      break;

    case 'i': //impulsions par tour
      if (val > 0)
        impByTurn = val;
      break;  

    case 'p': //period_ms
      if (val > 0)
        period_ms = val;
      break;

    case 't': //print Time
      if (val == 1)
        printTime = true;
      else
        printTime = false;
      break; 

    default:
      Serial.print("/!\\ unknown command : ");
      Serial.println(command);
      break;
  }
  PrintParameters();
}

void PrintParameters(){
  Serial.print("Direction : ");
  Serial.print(direction);

  Serial.print("\t");
  Serial.print("Period (ms) : ");
  Serial.print(period_ms);

  Serial.print("\t");
  Serial.print("Impulsions for 1 turn : ");
  Serial.print(impByTurn);

  Serial.print("\t");
  Serial.print("Value precision : ");
  Serial.print(floatprecision);

  Serial.print("\t");
  Serial.print("Print time : ");
  Serial.print(printTime);

  Serial.println("");
}

void PrintStart(){
  Serial.println("To change a parameter, send a letter with a value");
  Serial.println("'d' Direction of rotation (\"d1\" or \"d-1\")");
  Serial.println("'i' Coder impulsions for one full rotation (\"i1024\", \"i360\", ...)");
  Serial.println("'p' Period in millisecond between each serial message (\"p25\", \"p1000\", ...)");
  Serial.println("'f' float precision of the serial printed measure (\"f0\", \"f4\", ...)");
  Serial.println("'t' print time in serial message (\"t0\" or \"t1\")");
}