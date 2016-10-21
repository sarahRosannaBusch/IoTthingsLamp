//Firmware for Sarah Busch and Emily Wolfe's IoT Smart Lamp
//using a Particle Photon dev board
//Written by Sarah Rosanna Busch in October 2016

const int red1 = D0; //five pins control the red leds
const int red2 = D1;
const int red3 = D2;
const int red4 = D3;
const int red5 = D4;
const int warmWhite1 = A0; //two pins have warm white leds
const int warmWhite2 = A1;
const int white = A2; //one warm one cool
const int coolWhite1 = A3; //two pins have cool white leds
const int coolWhite2 = A4;

const int lightSensor = A5; //photoresistor
const int sensorPower = A6; //power to photoresistor

int analogLight; //to store the value read on A6

Timer checkLight(60000, readLight); //when in auto mode the sensor will periodically check the light level

bool automated = true; //this will be set from the webpage

void setup()
{
    pinMode(red1, OUTPUT);
    pinMode(red2, OUTPUT);
    pinMode(red3, OUTPUT);
    pinMode(red4, OUTPUT);
    pinMode(red5, OUTPUT);
    pinMode(warmWhite1, OUTPUT);
    pinMode(warmWhite2, OUTPUT);
    pinMode(white, OUTPUT);
    pinMode(coolWhite1, OUTPUT);
    pinMode(coolWhite2, OUTPUT);

    //ensure all LEDs are off to start
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
    digitalWrite(red4, LOW);
    digitalWrite(red5, LOW);
    digitalWrite(warmWhite1, LOW);
    digitalWrite(warmWhite2, LOW);
    digitalWrite(white, LOW);
    digitalWrite(coolWhite1, LOW);
    digitalWrite(coolWhite2, LOW);

    //declaration of Particle.function()s to be accessed from the cloud
    //requesting "day" runs dayLight() from this app
    Particle.function("day", dayLight);
    Particle.function("warm", warmLight);
    Particle.function("evening", eveningLight);
    Particle.function("night", nightLight);
    Particle.function("off", lampOff);

    //light sensor
    pinMode(lightSensor, INPUT); //reads analog value on pin A5
    pinMode(sensorPower, OUTPUT); //provides constant voltage to A6

    //digitalWrite(sensorPower, LOW); //make sure photoresistor is not powered on startup

    //declaration of Particle.variable()s that can be accessed from the cloud
    //requesting "lightLevel" references 'analogLight' in this app
    Particle.variable("lightLevel", &analogLight, INT);

    checkLight.start(); //check light level periodically
}

void loop()
{
    if(automated)
    {
        if(analogLight < 100)
            dayLight(""); //Particle.function forces me to give an arg :(
        else
            nightLight("");
    }
}

void readLight() //has to be a void for the Timer class to call it
{
    //turn on power to the photoresistor
    digitalWrite(sensorPower, HIGH);
    delay(100);

    //get the analog value of the photoresistor
    analogLight = analogRead(lightSensor);
    delay(100);

    //turn power to photoresistor off
    digitalWrite(sensorPower, LOW);
    delay(100);
}

//Particle.functions must take a string as an argument and return an integer
int dayLight(String command)
{
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
    digitalWrite(red3, HIGH);
    digitalWrite(red4, HIGH);
    digitalWrite(red5, HIGH);
    digitalWrite(warmWhite1, HIGH);
    digitalWrite(warmWhite2, HIGH);
    digitalWrite(white, HIGH);
    digitalWrite(coolWhite1, HIGH);
    digitalWrite(coolWhite2, HIGH);

    return 1;
}

int warmLight(String command) //cool whites turn off
{
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
    digitalWrite(red3, HIGH);
    digitalWrite(red4, HIGH);
    digitalWrite(red5, HIGH);
    digitalWrite(warmWhite1, HIGH);
    digitalWrite(warmWhite2, HIGH);
    digitalWrite(white, LOW);
    digitalWrite(coolWhite1, LOW);
    digitalWrite(coolWhite2, LOW);

    return 1;
}

int eveningLight(String command) //all whites are off
{
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
    digitalWrite(red3, HIGH);
    digitalWrite(red4, HIGH);
    digitalWrite(red5, HIGH);
    digitalWrite(warmWhite1, LOW);
    digitalWrite(warmWhite2, LOW);
    digitalWrite(white, LOW);
    digitalWrite(coolWhite1, LOW);
    digitalWrite(coolWhite2, LOW);

    return 1;
}

int nightLight(String command) //just a couple reds are on
{
    digitalWrite(red1, HIGH);
    digitalWrite(red2, HIGH);
    digitalWrite(red3, HIGH);
    digitalWrite(red4, LOW);
    digitalWrite(red5, LOW);
    digitalWrite(warmWhite1, LOW);
    digitalWrite(warmWhite2, LOW);
    digitalWrite(white, LOW);
    digitalWrite(coolWhite1, LOW);
    digitalWrite(coolWhite2, LOW);

    return 1;
}

int lampOff(String command)
{
    digitalWrite(red1, LOW);
    digitalWrite(red2, LOW);
    digitalWrite(red3, LOW);
    digitalWrite(red4, LOW);
    digitalWrite(red5, LOW);
    digitalWrite(warmWhite1, LOW);
    digitalWrite(warmWhite2, LOW);
    digitalWrite(white, LOW);
    digitalWrite(coolWhite1, LOW);
    digitalWrite(coolWhite2, LOW);

    return 1;
}
