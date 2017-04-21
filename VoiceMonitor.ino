const int sampleWindow = 250; // Sample window width in mS (250 mS = 4Hz)
unsigned int inputSignal;

void setup() {
  Serial.begin(9600);
}

void loop() {
 unsigned long start= millis();  // Start of sample window
 unsigned int peakToPeak = 0;    // peak-to-peak level

 unsigned int signalMax = 0;
 unsigned int signalMin = 1024;

 // collect data for 250 miliseconds
 unsigned long sum = 0;
 unsigned long cnt = 0;
 while (millis() - start < sampleWindow){
  inputSignal = analogRead(A0);

  //This is the max of the 10-bit ADC so this loop will include all readings
  if (inputSignal < 1024){
    if (inputSignal > signalMax){
      signalMax = inputSignal;  // save just the max levels
    } else if (inputSignal < signalMin){
      signalMin = inputSignal;  // save just the min levels
    }
  }

  sum += inputSignal;
  
 }
 
 peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
 double volts = (peakToPeak * 3.3) / 1024;  // convert to volts
 
 //Serial.println(volts);
 Serial.println(sum/cnt);
 //Serial.println(analogRead(A1));

}
