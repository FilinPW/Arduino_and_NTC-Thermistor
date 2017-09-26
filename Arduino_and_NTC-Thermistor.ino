#define THERMISTORPIN A0
#define THERMISTORNOMINAL 10000
#define TEMPERATURENOMINAL 25
#define NUMSAMPLES 10
#define BCOEFFICIENT 3950
#define SERIESRESISTOR 10000

int samples[NUMSAMPLES];

void setup(void) {
    Serial.begin(115200);
}

void loop(void) {
}

void serialEvent() {
    int getQ = Serial.read();
    if (getQ == '1') {
        float steinhart = getTemperature();
        Serial.println(steinhart);
    }
}

float getTemperature() {
    int get;
    uint8_t i;
    
    for (i = 0; i < NUMSAMPLES; i++) {
        samples[i] = analogRead(THERMISTORPIN);
        delay(10);
    }
    
    float average = 0;
    for (i = 0; i < NUMSAMPLES; i++) {
      average += samples[i];
    }
    average /= NUMSAMPLES;
    average = 1023 / average - 1;
    average = SERIESRESISTOR / average;
    
    float steinhart;
    steinhart = average / THERMISTORNOMINAL;
    steinhart = log(steinhart);
    steinhart /= BCOEFFICIENT;
    steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15);
    steinhart = 1.0 / steinhart;
    steinhart -= 273.15;
    steinhart = round(steinhart * 10) / 10.0;
    
    return steinhart;
}

