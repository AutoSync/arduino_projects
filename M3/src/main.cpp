#include <Arduino.h>

#define R 4
#define G 3
#define B 2
#define BOMBA 5
#define KEY 8
#define SENSOR_DIG 9
#define RX A0
#define RY A1
#define MIC A2

bool baixo = false, cima = false, esquerda = false, direita = false, center = false;
int horizontal;
int vertical;
unsigned time = 0;

enum Colors
{
    RED = 1, GREEN, BLUE, WHITE, CIAN, MAGENTA, 
};
enum Directional
{
    UP, DOWN, LEFT, RIGHT, CENTER
};

void Color(int color = 0);
void Paint(int r, int g, int b);
void Controls(int direction);
void Update();
void Bomba();

void setup() {

  Serial.begin(9600);
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(BOMBA, OUTPUT);
  pinMode(KEY, INPUT_PULLUP);

  pinMode(RX, INPUT);
  pinMode(RY, INPUT);

}

void loop() {
    if(time >= 65000)
        time = 0;
    time++;
    Update();
    Bomba();

    if(center)
        Paint(sin(time), 0, 0);
}

void Color(int color = 0)
{
    switch(color)
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
        case WHITE:
        digitalWrite(R, HIGH);
        digitalWrite(G, HIGH);
        digitalWrite(B, HIGH);
            break;
        case 0:
        digitalWrite(R, LOW);
        digitalWrite(G, LOW);
        digitalWrite(B, LOW);
            break;
        default:
            digitalWrite(R, LOW);
            digitalWrite(G, LOW);
            digitalWrite(B, LOW);
            break;
    }
    
}
void Controls(int direction)
{
    if(direction == UP)
        cima = true;
    else
        cima = false;
    if(direction == DOWN)
        baixo = true;
    else
        baixo = false;
    if(direction == LEFT)
        esquerda = true;
    else
        esquerda = false;
    if(direction == RIGHT)
        direita = true;
    else
        direita = false;
    if(direction == CENTER)
        center = true;
    else
        center = false;
}
void Update()
{
    horizontal = analogRead(RX);
    vertical = analogRead(RY);

    if(horizontal <= 10)
    {
        Controls(RIGHT);
    }
    else
    {
        if(horizontal >= 900)
        {
            Controls(LEFT);

        }
        else
        {
            if(vertical <= 10)
            {
                Controls(UP);

            }
            else
            {
                if(vertical >= 900)
                {
                    Controls(DOWN);

                }
                else
                {
                    if(digitalRead(KEY) == LOW)
                        {
                            Controls(CENTER);
                        }

                }
            }
        }
    }
    Serial.print("X: ");
    Serial.print(horizontal);
    Serial.print("Y: ");
    Serial.println(vertical);
}
void Bomba()
{
    

}
void Paint(int r, int g, int b)
{
    analogWrite(R, r);
    analogWrite(G, g);
    analogWrite(B, b);
}