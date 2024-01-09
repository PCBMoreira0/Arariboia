#define pin 2

volatile unsigned long current_duration = micros();
volatile unsigned long total_period;
volatile int newPulseAvaliable = 0;
int cnt = 0;

void calcFreqISR(){
  unsigned long duration = micros();
  total_period = duration - current_duration;
  current_duration = duration;
  newPulseAvaliable = 1;
}

float rpm_line(float t){
    return 15.179 * t - 19.65;
}

void setup()
{
  Serial.begin(9600);
  pinMode(pin, INPUT);
  attachInterrupt(digitalPinToInterrupt(pin), calcFreqISR, RISING);
}

void loop()
{
  if(newPulseAvaliable){
    newPulseAvaliable = 0;
    float frequency = 1.0/(total_period/1000000.0); //micros to seconds
    Serial.println(rpm_line(frequency));
  }
}
