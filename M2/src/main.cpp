#include <Arduino.h>

//LED
#define R 4 //RED PORT
#define G 3 //GREEN PORT
#define B 2 //BLUE PORT

//BUTTONS
#define TURN 5  //TURN TO ENABLE LED

//FOTO RESITOR
#define FOTO A0 //FOTO RESITOR

//POTENCIOMETER
#define LEVEL A1 //Speed LED Blink

//ENUMS
enum Colors{
    RED, BLUE, GREEN, YELLOW, WHITE, MAGENTA, CIAN
};
//Variables
int sensor = 0;                  // LIGHT SENSOR INITIAL VALUE
int level = 0;
unsigned int speed = 1000;      // SPEED TO BLINK
int min_light = 150;            // MINIMAL TO ENABLE LIGHT
bool turn = false;              // BUTTON PRESSED
//Functions Prototypes

void Begin();                   //Init
void Update();                  //Update Variables
void Color(int color);          //
void Off();
void Blink();
void TurnButton();
void Count();

void setup() {
  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(TURN, INPUT);
  pinMode(FOTO, INPUT);
  pinMode(LEVEL, INPUT);

  Begin();

}

void loop() {
  
    Update();
    TurnButton();
    Blink();
}

void Begin()
{
    Off();
    sensor = 0;
    speed = 1000;
    Color(WHITE);
    delay(1000);
    Off();
}

void Update()
{
    sensor = analogRead(FOTO);
    level = analogRead(LEVEL);

    Serial.print("Light Intensity: ");
    Serial.print(sensor);
    Serial.print(" | Time: ");
    Serial.print(speed);
    Serial.println("/ms");

    speed = map(level, 0, 1023, 50, 1000) * 2;
}
void Color(int color)
{
    switch (color)
    {
    case RED:
        digitalWrite(R, HIGH);
        digitalWrite(G, LOW);
        digitalWrite(B, LOW);
        break;
    case GREEN:
        digitalWrite(R, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(B, LOW);
        break;
    case BLUE:
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(B, HIGH);
        break;
    case YELLOW:
        digitalWrite(R, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(B, LOW);
        break;
    case WHITE:
        digitalWrite(R, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(B, HIGH);
        break;
    case MAGENTA:
        digitalWrite(R, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(B, LOW);
        break;
    case CIAN:
        digitalWrite(R, LOW);
        digitalWrite(G, HIGH);
        digitalWrite(B, HIGH);
        break;
    default:
        Off();
        break;
    }
}
void Off()
{
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(B, LOW);
}
void Blink()
{
    //delay(speed);
    if(turn == true || sensor >= min_light )
    {
        Color(BLUE);
        delay(1000);
        Count();
    }
    else
        Off();
}
void TurnButton()
{
    if(digitalRead(TURN) == HIGH)
    {
        turn = !turn;
        if(turn)
            Serial.println("Light Enable");
        else
            Serial.println("Light Disable");
        delay(500);
    }
    else
        turn = false;
}
void Count()
{
    for(int i = 0; i < 10; i++)
    {
        if(digitalRead(TURN) == HIGH)
        {
            i = 0;
            Serial.println("Counting Reseted");
        } 

        switch (i)
        {
        case 0:
            Color(RED);
            delay(speed);
            break;
        case 1:
            Color(CIAN);
            delay(speed);
            break;
        case 2:
            Color(YELLOW);
            delay(speed);
            break;
        case 3:
            Color(MAGENTA);
            delay(speed);
            break;
        case 4:
            Color(YELLOW);
            delay(speed);
            break;
        case 5:
            Color(RED);
            delay(speed);
            break;
        case 6:
            Color(CIAN);
            delay(speed);
            break;
        case 7:
            Color(YELLOW);
            delay(speed);
            break;
        case 8:
            Color(RED);
            delay(speed);
            break;
        case 9:
            Color(MAGENTA);
            delay(speed);
            break;
        case 10:
            Color(YELLOW);
            delay(speed);
            break;
        }

        Serial.print("Counting: ");
        Serial.print(i + 1);
        Serial.print("/10 in Speed: ");
        Serial.print(speed);
        Serial.println("/ms");


        Off();
    }
    Color(GREEN);
    delay(1000);
    turn = false;
}