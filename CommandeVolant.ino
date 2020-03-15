#include <SPI.h>
byte address=0x11;
int CS= 10;

int seuil = 30;
int molette = 0;

int valeur_descente = 50;
int valeur_monte = 90;

int valeur_menu = 130;
int valeur_source = 170;

int valeur_plus  = 210;
int valeur_moins = 250;

void setup() {
  Serial.begin(9600);
  
  Serial.println("init");
  pinMode (CS, OUTPUT);
  SPI.begin();
  // adjust high and low resistance of potentiometer
  // adjust Highest Resistance .
  digitalPotWrite(0x00);
  delay(1000);
  
    // adjust  wiper in the  Mid point  .
  digitalPotWrite(0x80);
  delay(1000);
  
  // adjust Lowest Resistance .
  digitalPotWrite(0xFF);
  delay(1000);
   
  
  Serial.println("fin init");
}

void loop() {
    
    boolean plus = false;
    boolean moins = false;
    boolean source = false;
    boolean menu = false;
    boolean modif = false;
    boolean monte = false;
    boolean descente = false;
    
    int valeur_a_transmettre = 0;
    
  
    int val0 = analogRead(A0);
    int val1 = analogRead(A1);
    int val2 = analogRead(A2);
    delay(1);

    
    if (verif(val0, 0) && verif(val1, 300) && verif(val2, 0)) {
      if (molette == 3) {
        modif = true;
        monte = true;
        valeur_a_transmettre = valeur_monte;
      }
      if (molette == 2) {
        modif = true;
        descente = true;
        valeur_a_transmettre = valeur_descente;
      }
      molette = 1;
    }
    if (verif(val0, 0) && verif(val1, 650) && verif(val2, 0)) {
      if (molette == 1) {
        modif = true;
        monte = true;
        valeur_a_transmettre = valeur_monte;
      }
      if (molette == 3) {
        modif = true;
        descente = true;
        valeur_a_transmettre = valeur_descente;
      }
      molette = 2;
    }
    if (verif(val0, 0) && verif(val1, 1000) && verif(val2, 0)) {
      if (molette == 2) {
        modif = true;
        monte = true;
        valeur_a_transmettre = valeur_monte;
      }
      if (molette == 1) {
        modif = true;
        descente = true;
        valeur_a_transmettre = valeur_descente;
      }
      molette = 3;
    }
    
    if (verif(val0, 0) && verif(val1, 650) && verif(val2, 210)) {
      plus = true;
      modif = true;
      valeur_a_transmettre = valeur_plus;
    }
    if (verif(val0, 0) && verif(val1, 1000) && verif(val2, 210)) {
      plus = true;
      modif = true;
      valeur_a_transmettre = valeur_plus;
    }
    if (verif(val0, 0) && verif(val1, 150) && verif(val2, 150)) {
      plus = true;
      modif = true;
      valeur_a_transmettre = valeur_plus;
    }
    
    if (verif(val0, 0) && verif(val1, 300) && verif(val2, 568)) {
      moins = true;
      modif = true;
      valeur_a_transmettre = valeur_moins;
    }
    if (verif(val0, 0) && verif(val1, 488) && verif(val2, 488)) {
      moins = true;
      modif = true;
      valeur_a_transmettre = valeur_moins;
    }
    if (verif(val0, 0) && verif(val1, 1000) && verif(val2, 568)) {
      moins = true;
      modif = true;
      valeur_a_transmettre = valeur_moins;
    }
    
    // *-*-*-*-*-*-*-*-*-* SOURCE *-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    if (verif(val0, 0) && verif(val1, 300) && verif(val2, 1000)) {
        source = true;
        modif = true;
        valeur_a_transmettre = valeur_source;
    }
    if (verif(val0, 0) && verif(val1, 650) && verif(val2, 1000)) {
        source = true;
        modif = true;
        valeur_a_transmettre = valeur_source;
    }
    if (verif(val0, 0) && verif(val1, 997) && verif(val2, 997)) {
        source = true;
        modif = true;
        valeur_a_transmettre = valeur_source;
    }
    
    if (verif(val0, 999) && verif(val1, 300) && verif(val2, 0)) {
      menu = true;
      modif = true;
      valeur_a_transmettre = valeur_menu;
    }
    if (verif(val0, 999) && verif(val1, 651) && verif(val2, 0)) {
      menu = true;
      modif = true;
      valeur_a_transmettre = valeur_menu;
    }
    if (verif(val0, 997) && verif(val1, 997) && verif(val2, 0)) {
      menu = true;
      modif = true;
      valeur_a_transmettre = valeur_menu;
    }
    
    
    if (modif) {
      Serial.print("molette : ");
      Serial.print(molette);
      Serial.print(", ");
      
      Serial.print("vol+ : ");
      Serial.print(plus);
      Serial.print(", ");
      
      Serial.print("vol- : ");
      Serial.print(moins);
      Serial.print(", ");
      
      Serial.print("source : ");
      Serial.print(source);
      Serial.print(", ");
      
      Serial.print("menu : ");
      Serial.print(menu);
      Serial.print(", ");
      
      Serial.print("monte : ");
      Serial.print(monte);
      Serial.print(", ");
      
      Serial.print("descente : ");
      Serial.println(descente);


      digitalPotWrite(valeur_a_transmettre);
      delay(50);
      if (valeur_a_transmettre == valeur_monte || valeur_a_transmettre == valeur_descente) {
        delay(100);
      }
    } else {
      digitalPotWrite(0);
    }
    
    // Serial.print(val0);
    //   Serial.print(" : ");
    //   Serial.print(val1);
    //   Serial.print(" : ");
    //   Serial.println(val2);
}

boolean verif(int valeur_lue, int valeur_a_comparer) {
  if ((valeur_lue > valeur_a_comparer - seuil) && (valeur_lue < valeur_a_comparer + seuil)) {
    return true;
  }
  return false;
}

int digitalPotWrite(int value)
{
  digitalWrite(CS, LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(CS, HIGH);
}
