#include <NewPing.h>
///
#define TPL A3
#define EPL A0
#define TPF A4
#define EPF A1
#define TPR A5
#define EPR A2
#define MD 350
NewPing SL(TPL, EPL, MD);
NewPing SF(TPF, EPF, MD);
NewPing SR(TPR, EPR, MD);
#define ENA  3
#define MI1  4 //LEFT -
#define MI2  5 //LEFT +
#define MI3  7 //RIGHT -
#define MI4  8 //RIGHT +
#define ENB  9
#define MAX_SPEED 200
#define MAX_SPEED_OFFSET 20
#define MS 75

///


///
int Mod  =0 ;
int OldD =0 ;
int OldR =0 ;
int TOT  =0 ;
int L    =0 ;
int F    =0 ;
int FF   =0 ;
int R    =0 ;
int FOOL =0 ;
int IDK  =0 ;
int Save[50] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int SaveN =0;
int SaveT =0;
int Morse[140] ={1,1,1,1,3,1,4,1,1,3,1,1,1,4,1,2,1,1,3,1,1,3,1,2,3,1,2,1,4,1,2,2,1,3,1,2,1,1,3,1,3,1,2,3,1,1,1,3,1,4,1,1,1,2,3,2,2,2,3,1,2,2,1,4,1,1,1,1,3,1,1,3,2,2,4,1,1,2,1,3,1,2,1,3,2,2,2,3,2,2,4,2,1,2,1,3,2,2,2,3,2,1,3,2,3,1,2,1,3,2,2,2,3,1,2,1,1,3,1,2,1,1,3,1,1,3,2,1,3,2,2,1,4,2,2,3,1,0};
///

void setup() {
  Serial.begin(9600); 
  pinMode(TPL, OUTPUT); 
  pinMode(EPL, INPUT ); 
  pinMode(TPF, OUTPUT); 
  pinMode(EPF, INPUT ); 
  pinMode(TPR, OUTPUT); 
  pinMode(EPR, INPUT ); 
  pinMode(MI1, OUTPUT);
  pinMode(MI2, OUTPUT);
  pinMode(MI3, OUTPUT);
  pinMode(MI4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, MS); 
  analogWrite(ENB, MS); 
}

void loop() {
  OldR = LookF();
  if ( OldR <= 350 ) {
    if ( Mod <= 0 ) {
      OldD = LookF(); 
      do {
        OldR = LookF();
        Go();
        delay(30);
        TOT = TOT + 30 ;
      } while (OldR < OldD-20);
      Mod = 1 ;
    }
    else if ( Mod == 1 ) {
      L = LookL();
      F = LookF();
      R = LookR();
      if (R > 20) {
        Go();
        delay(TOT/2);
        Right();
        delay(TOT*0.785);
        Go();
        delay((TOT-L+8.5)/1.25);//CHANGE IT IF IT HIT SNESOR ANGEL CAN MAKE ERROR
      }
      else if (F > 20) {
        Go();
        delay(30);
      }
      else if (F < 20 && L>20) {
        Left ();
        delay(TOT*0.785);
      }
      else if (F < 20 && L <20) {
        do {
        L = LookL();
        ReturnAsYouGO();
        delay(30);
        } while (L > 20);
        ReturnAsYouGO();
        delay(TOT/2);
        BLeft();
        delay(TOT*0.785);
        Go();
        delay((TOT-R+8.5)/1.25);//CHANGE IT IF IT HIT SNESOR ANGEL CAN MAKE ERROR
      }
    }
    else if ( Mod == 2 ) {
      R = LookL();
      F = LookF();
      L = LookR();
      if (R > 20) {
        Go();
        delay(TOT/2);
        Left();
        delay(TOT*0.785);
        Go();
        delay((TOT-L+8.5)/1.25);//CHANGE IT IF IT HIT SNESOR ANGEL CAN MAKE ERROR
      }
      else if (F > 20) {
        Go();
        delay(30);
      }
      else if (F < 20 && L>20) {
        Right ();
        delay(TOT*0.785);
      }
      else if (F < 20 && L <20) {
        do {
        L = LookR();
        ReturnAsYouGO();
        delay(30);
        } while (L > 20);
        ReturnAsYouGO();
        delay(TOT/2);
        BRight();
        delay(TOT*0.785);
        Go();
        delay((TOT-R+8.5)/1.25);//CHANGE IT IF IT HIT SNESOR ANGEL CAN MAKE ERROR
      }
    }
    else if ( Mod == 3 ) {
      L = LookL();
      F = LookF();
      R = LookR();
      if (R > 20) {
        FOOL = random(3) ;
        if (FOOL==2) {
          Go();
          delay(TOT/2);
          Right();
          delay(TOT*0.785);
          Go();
          delay((TOT-L+8.5)/1.25);//CHANGE IT IF IT HIT SNESOR ANGEL CAN MAKE ERROR
        }
      }
      else if (F > 20) {
        Go();
        delay(30);
      }
      else if (F < 20 && L>20) {
        Left ();
        delay(TOT*0.785);
      }
      else if (F < 20 && L <20) {
        do {
        L = LookL();
        F = LookF();
        ReturnAsYouGO();
        delay(30);
        FF = LookF();
        if (FF==F&& IDK!=10) {
          IDK=IDK+1;
        }
        else if (FF==F&& IDK==10) {
          break;
        }
        } while (L > 20);
        ReturnAsYouGO();
        delay(TOT/2);
        BLeft();
        delay(TOT*0.785);
        Go();
        delay((TOT-R+8.5)/1.25);//CHANGE IT IF IT HIT SNESOR ANGEL CAN MAKE ERROR
      }
    }
    else if ( Mod == 4 ) {
      L = LookL();
      F = LookF();
      R = LookR();
      if (R > 20) {
        if (SaveT != 0) {
          Save[SaveN]=SaveT;
          SaveT = 0;
          SaveN = SaveN+1;
        }
        Save[SaveN]=1;
        SaveN = SaveN+1;
        Go();
        delay(TOT/2);
        Right();
        delay(TOT*0.785);
        Go();
        delay((TOT-L+8.5)/1.25);//CHANGE IT IF IT HIT SNESOR ANGEL CAN MAKE ERROR
      }
      else if (F > 20) {
        SaveT = SaveT + 30 ;
        Go();
        delay(30);
      }
      else if (F < 20 && L>20) {
        if (SaveT != 0) {
          Save[SaveN]=SaveT;
          SaveT = 0;
          SaveN = SaveN+1;
        }
        Save[SaveN]=2;
        SaveN = SaveN+1;
        Left ();
        delay(TOT*0.785);
      }
    }
    else if ( Mod == 5 ) {
      for (int i = 0; i < 51; i++) {
        if (Save[i] ==1) {
          Go();
          delay(TOT/2);
          Right();
          delay(TOT*0.785);
          Go();
          delay((TOT-L+8.5)/1.25);//CHANGE IT IF IT HIT SNESOR ANGEL CAN MAKE ERROR
        }
        else if (Save[i] >2) {
          Go();
          delay(Save[i]);
        }
        else if (Save[i] ==2) {
          Left ();
          delay(TOT*0.785);
        }
         else if (Save[i] ==0) {
           break;
        }
      }
    }
    else if ( Mod == 6 ) {
       for (int i = 0; i < 141; i++) {
        if (Morse[i] ==1) {
          Go();
          delay(TOT);
          ReturnAsYouGO;
          delay(TOT);
        }
        else if (Morse[i] ==2) {
          Go();
          delay(TOT);
          Stop();
          delay(250);
          ReturnAsYouGO;
          delay(TOT);
        }
        else if (Morse[i] ==3) {
          delay(250);
        }
        else if (Morse[i] ==4) {
          delay(750);
        }
         else if (Save[i] ==0) {
           break;
        }
      }
    }
    else if ( Mod == 7 ) {
      Go();
      delay(TOT);
      ReturnAsYouGO;
      delay(TOT);
       Go();
      delay(TOT);
      ReturnAsYouGO;
      delay(TOT);
       Go();
      delay(TOT);
      ReturnAsYouGO;
      delay(TOT);
      Stop();
      delay(500);
      Right();
      BLeft();
    }
  }


  
  /////////////////////////
  else if (OldR >= 400 ) {
    delay(3000);
     if ( OldR <= 7 ) {
       Stop();
       if ( Mod == 1 ) {
         Mod=2;
         Go();
         delay(100);
         Stop();
         delay(5000);
       }
       else if ( Mod == 2 ) {
         Mod=3;
         Go();
         delay(100);
         Stop();
         delay(5000);
       }
       else if ( Mod == 3 ) {
         Mod=4;
         Go();
         delay(100);
         Stop();
         delay(5000);
       }
       else if ( Mod == 4 ) {
         Mod=5;
         Go();
         delay(100);
         Stop();
         delay(5000);
       }
       else if ( Mod == 5 ) {
         Mod=6;
         Go();
         delay(100);
         Stop();
         delay(5000);
       }
       else if ( Mod == 6 ) {
         Mod=7;
         Go();
         delay(100);
         Stop();
         delay(5000);
       }
     }
  }
  //////////////////////////
}
/////


/////
void  Go() {
  digitalWrite(MI1, LOW);
  digitalWrite(MI2, HIGH);
  digitalWrite(MI3, LOW);
  digitalWrite(MI4, HIGH);
}
void ReturnAsYouGO() {
  digitalWrite(MI1, HIGH);
  digitalWrite(MI2, LOW);
  digitalWrite(MI3, HIGH);
  digitalWrite(MI4, LOW);
}
void Stop() {
  digitalWrite(MI1, LOW);
  digitalWrite(MI2, LOW);
  digitalWrite(MI3, LOW);
  digitalWrite(MI4, LOW);
}
void Right() {
  digitalWrite(MI1, LOW);
  digitalWrite(MI2, LOW);
  digitalWrite(MI3, LOW);
  digitalWrite(MI4, HIGH);
}

void Left() {
  digitalWrite(MI1, LOW);
  digitalWrite(MI2, HIGH);
  digitalWrite(MI3, LOW);
  digitalWrite(MI4, LOW);
}
void BRight() {
  digitalWrite(MI1, LOW);
  digitalWrite(MI2, LOW);
  digitalWrite(MI3, HIGH);
  digitalWrite(MI4, LOW);
}

void BLeft() {
  digitalWrite(MI1, HIGH);
  digitalWrite(MI2, LOW);
  digitalWrite(MI3, LOW);
  digitalWrite(MI4, LOW);
}
/////


/////
int LookL() {
  int cm = SL.ping_cm();
}
int LookF() {
  int cm = SF.ping_cm();
  if (cm == 0)
  {
    cm = 400;
  }
  return cm;
}
int LookR() {
  int cm = SR.ping_cm();
}
