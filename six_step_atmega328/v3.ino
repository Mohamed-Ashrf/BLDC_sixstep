#define mosh1 11
#define mosl1 10 

#define mosh2 9 
#define mosl2 6    

#define mosh3 5
#define mosl3 3

#define Sensor1 A0
#define Sensor2 A1
#define Sensor3 A2



int conpin = 1;
int counter = 0;
int SPEED = 0;
int STEP = 0;
int ha,hc,hb;
int conf = 0;
int step_counter = 1;
int x=0;
int a, b, c;
int steps();
void action(int st,int spp);
void STOP();
void setup() { 
Serial.begin(9600);
Serial.println("start");

pinMode(mosh1,1);
pinMode(mosh2,1);
pinMode(mosh3,1);

pinMode(mosl1,1);
pinMode(mosl2,1);
pinMode(mosl3,1);


pinMode(Sensor1,0);
pinMode(Sensor2,0);
pinMode(Sensor3,0);
//pinMode(Sensor1,INPUT_PULLUP);
//pinMode(Sensor2,INPUT_PULLUP);
//pinMode(Sensor3,INPUT_PULLUP);

pinMode(A4,0);

Serial.println("starting after 5 seconds");
//delay(5000);
x = steps();
action(x,255);
delay(50);
//x = steps();
//action(x,255);
//delay(50);
Serial.println("starting NOW");


SREG  = SREG  | 0b10000000;
PCICR = PCICR | 0b00000010;  // pin chage int 8 to 14       
PCMSK1= PCMSK1| 0b00000111;  // pcint8 A0, pcint9 A1, pcint10 A2

}


void loop() {
}



ISR(PCINT1_vect){
    PCICR |= ~(1<<1);
    
    Serial.print(" pin int ");
    x = steps();
    action(x,255);
    Serial.println(x);

    
    PCICR |= (1<<1);   
  }

  
int steps(){
  
  ha = digitalRead(Sensor1);
  hb = digitalRead(Sensor2);
  hc = digitalRead(Sensor3);
  
  if( ha == 1 && hb == 0 && hc == 0 ){         // step 6  //100
    STEP = 6;
    }    
    else if( ha == 0 && hb == 1 && hc == 0 ){  // step 4  //010  
    STEP = 4;
    }
    else if( ha == 1 && hb == 1 && hc == 0){  // step 5  //110
    STEP = 5;
    }
    else if( ha == 0 && hb == 0 && hc ==1 ){   // step 2  //001
    STEP = 2;
    }
    else if( ha == 1 && hb ==0 && hc ==1 ){    // step 1  //101
    STEP = 1;
    }
    else if( ha == 0 && hb == 1 && hc == 1 ){  // step 3  //011
    STEP = 3;
    }else{
    STEP = 0;
      }
    return STEP;
}
void STOP(){
    digitalWrite(2,0);
    digitalWrite(3,0);
    digitalWrite(4,0);
    digitalWrite(5,0);
    digitalWrite(6,0);
    digitalWrite(7,0);
  }


void action(int st,int spp){
    int spedh = 1;
    int spedl = 0;
    switch (st) {
      case 6:
        digitalWrite(mosh1,spedh);
        digitalWrite(mosl1,0);
        digitalWrite(mosh2,0);
        digitalWrite(mosl2,0);
        digitalWrite(mosh3,0);
        digitalWrite(mosl3,spedh);
        break;
        
      case 4:
        digitalWrite(mosh1,0);
        digitalWrite(mosl1,spedh);
        digitalWrite(mosh2,spedh);
        digitalWrite(mosl2,0);
        digitalWrite(mosh3,0);
        digitalWrite(mosl3,0);
        break;

        
      case 5:
        digitalWrite(mosh1,0);
        digitalWrite(mosl1,0);
        digitalWrite(mosh2,spedh);
        digitalWrite(mosl2,0);
        digitalWrite(mosh3,0);
        digitalWrite(mosl3,spedh);
        break;
        
      case 2:
        digitalWrite(mosh1,0);
        digitalWrite(mosl1,0);
        digitalWrite(mosh2,0);
        digitalWrite(mosl2,spedh);
        digitalWrite(mosh3,spedh);
        digitalWrite(mosl3,0);
        break;
        
      case 1:
        digitalWrite(mosh1,spedh);
        digitalWrite(mosl1,0);  
        digitalWrite(mosh2,0);
        digitalWrite(mosl2,spedh);
        digitalWrite(mosh3,0);
        digitalWrite(mosl3,0);
        break;
        
      case 3:
        digitalWrite(mosh1,0);
        digitalWrite(mosl1,spedh);
        digitalWrite(mosh2,0);
        digitalWrite(mosl2,0);
        digitalWrite(mosh3,spedh);
        digitalWrite(mosl3,0);
        break;
        
      default:
        digitalWrite(mosh1,0);
        digitalWrite(mosl1,0);
        digitalWrite(mosh2,0);
        digitalWrite(mosl2,0);
        digitalWrite(mosh3,0);
        digitalWrite(mosl3,0);
        break;
  }  
}
