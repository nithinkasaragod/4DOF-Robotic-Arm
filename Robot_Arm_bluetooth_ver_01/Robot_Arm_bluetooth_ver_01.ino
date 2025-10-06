//Created By Vinayak Jadhav
// Email id: vinayakjadhav1415@gmail.com

#include <Servo.h>

#define SERVO_BASE            2
#define SERVO_SHOULDER        3
#define SERVO_ELBOW           4
#define SERVO_GRIPPER         5

Servo myservo_1;  // create servo object to control a servo
Servo myservo_2;
Servo myservo_3;
Servo myservo_4;

unsigned char Data_String[25],Data_Index = 0,New_Data_Rec_Flag = 0;
unsigned int Received_Servo_Value[4],Final_Servo_Val[4];
unsigned char Index_i = 0,Index_j = 0,Counter_to_Refresh = 0;

void setup() {
  Serial.begin(9600);
  myservo_1.attach(SERVO_BASE);       // attaches the servo on pin 2 to the servo object
  myservo_2.attach(SERVO_SHOULDER);   // attaches the servo on pin 3 to the servo object
  myservo_3.attach(SERVO_ELBOW);      // attaches the servo on pin 4 to the servo object
  myservo_4.attach(SERVO_GRIPPER);    // attaches the servo on pin 5 to the servo object

  myservo_1.write(90);
  delay(200);
  myservo_2.write(90);
  delay(200);
  myservo_3.write(90);
  delay(200);
  myservo_4.write(90);
  delay(200);

  Received_Servo_Value[0] = 90;     // Default values
  Received_Servo_Value[1] = 90;
  Received_Servo_Value[2] = 90;
  Received_Servo_Value[3] = 45;
  
  Final_Servo_Val[0] = 90;          // Default values
  Final_Servo_Val[1] = 90;
  Final_Servo_Val[2] = 90;
  Final_Servo_Val[3] = 45;
}

void loop()
{
  if(New_Data_Rec_Flag==0)
  {
    if (Serial.available())     // check whether bluetooth data is available
    {
      // read incoming serial data:
      char inChar = Serial.read();    // read bluetooth data one by one
      //Serial.print(inChar);
      if(inChar==0x0A)                // End character of bluetooth data
      {
          Data_String[Data_Index] = inChar;
          Data_Index = 0;
          New_Data_Rec_Flag = 1;
      }
      else
      {
        if(inChar!=0x2C)              // removing ascii value, except for 0x2C which is ascii for ,
        {
            inChar = inChar - 0x30;   // removing Ascii value of 0, so that we can get exat value
        }
        Data_String[Data_Index] = inChar;
        Data_Index++;
      }
    }
  }

  if(New_Data_Rec_Flag==1)
  {
      Received_Servo_Value[0] = 0;
      Received_Servo_Value[1] = 0;
      Received_Servo_Value[2] = 0;
      Received_Servo_Value[3] = 0;
      
      for(Index_i = 0,Index_j = 0;;)
      {
            if(Data_String[Index_j]==0x2C)
            {
                Index_j++;
                Index_i++;
                Serial.print("A ");
            }
            else if(Data_String[Index_j]==0x0A)
            {
                  New_Data_Rec_Flag = 0;
                  Serial.print("B ");
                  break;
            }
            else
            {
                Received_Servo_Value[Index_i] = Received_Servo_Value[Index_i] * 10 + Data_String[Index_j];
                Index_j++;
                Serial.print("C ");
            }
      }
      Serial.print(Received_Servo_Value[0]);
      Serial.print("  ");
      Serial.print(Received_Servo_Value[1]);
      Serial.print("  ");
      Serial.print(Received_Servo_Value[2]);
      Serial.print("  ");
      Serial.println(2*Received_Servo_Value[3]);
  }
  
  Counter_to_Refresh++;
  delay(1);
  if(Counter_to_Refresh >= 10)    // delay of 10 msec = 1 msec * 10, this will allow smooth movement of servos
  {
      Counter_to_Refresh = 0;
      if(Received_Servo_Value[0]!=Final_Servo_Val[0])
      {
          if(Received_Servo_Value[0]>Final_Servo_Val[0])
          {
              Final_Servo_Val[0]++;
          }

          if(Received_Servo_Value[0]<Final_Servo_Val[0])
          {
              Final_Servo_Val[0]--;
          }
          myservo_1.write(180 - Final_Servo_Val[0]);      // adjuted as per app
      }

      if(Received_Servo_Value[1]!=Final_Servo_Val[1])
      {
          if(Received_Servo_Value[1]>Final_Servo_Val[1])
          {
              Final_Servo_Val[1]++;
          }

          if(Received_Servo_Value[1]<Final_Servo_Val[1])
          {
              Final_Servo_Val[1]--;
          }
          myservo_2.write(Final_Servo_Val[1]);
      }

      if(Received_Servo_Value[2]!=Final_Servo_Val[2])
      {
          if(Received_Servo_Value[2]>Final_Servo_Val[2])
          {
              Final_Servo_Val[2]++;
          }

          if(Received_Servo_Value[2]<Final_Servo_Val[2])
          {
              Final_Servo_Val[2]--;
          }
          myservo_3.write(Final_Servo_Val[2]);
      }

      if(Received_Servo_Value[3]!=Final_Servo_Val[3])
      {
          if(Received_Servo_Value[3]>Final_Servo_Val[3])
          {
              Final_Servo_Val[3]++;
          }

          if(Received_Servo_Value[3]<Final_Servo_Val[3])
          {
              Final_Servo_Val[3]--;
          }
          myservo_4.write(180 - (2*Final_Servo_Val[3]));  // adjuted as per app
      }
  }
}
