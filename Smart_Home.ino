#include<LiquidCrystal.h>
LiquidCrystal lcd(7,6,5,4,3,2);


//main ldr
#define mldr A0

//main IR
#define mir 11
#define led 6

//Fire_system
#define lm A1
#define ldr A2
#define buzzer 10
#define button 9

//IR_Room1
#define led1 7
#define ir1 12 

//IR_Room2
#define led2 8
#define ir2 13

//Gas
#define gas 5

//Soil
#define soil 4
#define soil_adc A3

void setup() {
  //main ldr
  pinMode(mldr,INPUT);

  //main ir
  pinMode(mir,INPUT);

  //Fire_system  
  pinMode(lm, INPUT); 
  pinMode(ldr, INPUT); 
  pinMode(button, INPUT); 
  pinMode(buzzer, OUTPUT);

  //IR_Room1
  pinMode (led1,OUTPUT); 
  pinMode(ir1,INPUT); 

  //IR_Room2
  pinMode (led2,OUTPUT); 
  pinMode(ir2,INPUT); 

  //Gas 
  pinMode (gas,INPUT);

  //soil
  pinMode(soil,OUTPUT);
  pinMode(soil_adc,INPUT);
  digitalWrite(soil,LOW);  //to turn the sensor off by default

  lcd.begin(16,2);
  lcd.clear();
  Serial.begin(9600);
   
}

void loop() {
  Main_ldr();
  Main_IR();
  IR_Room1();
  IR_Room2();
  Gas();
  Soil();

  
}

void Fire_System(){
      int ldr = analogRead(ldr); 
      int adc = analogRead(lm); 
       int button_read = digitalRead(button);
      float tmp= (adc/1024.0)*500.0 ;
      Serial.println(tmp);
      if (ldr > 100)
      {
        if (tmp > 50)
        {
          while (true)
            {
              button_read = digitalRead(button);
              digitalWrite(buzzer, HIGH);
              if (button_read == HIGH)
              {
                digitalWrite(buzzer, LOW);
                break;
          }
          }
    
    }
  }
}

void Main_ldr(){
  
      int mldr=analogRead(A0);
      Serial.println(mldr);
      lcd.print("Temperature : " + String(tmp));
      lcd.setCursor(0,1); 

      if (mldr >= 512)
      { 
        lcd.print("Morning !");
      }
      else
      {
        lcd.print("Evening !");
      }
  }

  void Main_IR(){
  
         int ir_read=digitalRead(mir);
         if (ir_read==0)
         {
          digitalWrite(led,1);
         }
         else 
         {
          digitalWrite(led,0);
         }
      }

void IR_Room1(){
  
         int ir1_read=digitalRead(ir1);
         if (ir1_read==0)
         {
          digitalWrite(led1,1);
         }
         else 
         {
          digitalWrite(led1,0);
         }
}
   
void IR_Room2(){
  
         int ir2_read=digitalRead(ir2);
         if (ir2_read==0)
         {
          digitalWrite(led2,1);
         }
         else 
         {
          digitalWrite(led2,0);
         }
          
  }

void Gas(){
        int gas_read=digitalRead (gas);
        int button_read = digitalRead(button);
        if (gas_read==HIGH)
        {
          while (true)
              {
                button_read = digitalRead(button);
                digitalWrite(buzzer, HIGH);
                if (button_read == HIGH)
                {
                  digitalWrite(buzzer, LOW);
                  break;
        }    
     } 
  }
}

void Soil()
{
        digitalWrite (soil,HIGH);
        delay(25);
        int soil_read =analogRead (soil_adc);
        int button_read = digitalRead(button);
        delay(25);
        digitalWrite(soil,LOW);
        if (soil_read >= 512)
        {while (true)
                    {
                button_read = digitalRead(button);
                digitalWrite(buzzer, HIGH);
                if (button_read == HIGH)
                {
                  digitalWrite(buzzer, LOW);
                  break;
        }    
     } 
    
  }
  
}
