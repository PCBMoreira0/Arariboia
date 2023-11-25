// Código para ESP32

int pin = 7;
unsigned long total_period;
double frequency;

unsigned long start_time = 0;
unsigned long delay_time = 100; //milliseconds
int med_counter = 0;

float rpm_line(float t){
    return 15.179 * t - 19.65;
}

void setup()
{
  Serial.begin(9600);
  pinMode(pin, INPUT);
}

void loop()
{
  unsigned long current_time = millis();
  
  unsigned long low_duration = pulseIn(pin, LOW);
  unsigned long high_duration = pulseIn(pin, HIGH);
  total_period += low_duration + high_duration;
  med_counter++;
  
  if(current_time - start_time >= delay_time){
    unsigned long med_period = total_period / med_counter;
    frequency = 1.0 / (med_period/1000000.0); // micros to seconds
    float rpm = rpm_line((float)frequency);
    
    Serial.println(rpm);
    
    total_period = 0;
    med_counter = 0;
    start_time = current_time;
  }
}
