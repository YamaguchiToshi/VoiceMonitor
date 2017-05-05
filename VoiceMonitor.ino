const int sampleWindow = 250; // Sample window width in mS (250 mS = 4Hz)
unsigned int inputSignal;
unsigned int inputSignals[] = {0, 0, 0};



void setup() {
  Serial.begin(9600);
}

void loop() {
 unsigned long start= millis();  // Start of sample window
 unsigned int peakToPeak = 0;    // peak-to-peak level

 unsigned int signalMax = 0;
 unsigned int signalMin = 1024;

 // collect data for 250 miliseconds
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
  
 }
 
 peakToPeak = signalMax - signalMin;  // max - min = peak-peak amplitude
 //double volts = (peakToPeak * 3.3) / 1024;  // convert to volts

 inputSignals[2] = inputSignals[1];
 inputSignals[1] = inputSignals[0];
 inputSignals[0] = peakToPeak;

 if(avg() > analogRead(A1)){
   Serial.println("1");
   analogWrite( 9, 80 );
 } else {
   Serial.println("0");  
   analogWrite( 9, 0 );
 }
 
 //Serial.println(peakToPeak);
 //Serial.println(volts);
 //Serial.println(analogRead(A1));

}

unsigned int avg(){
  unsigned int sum = 0;
  for(int i = 0; i < 3; ++i){
    sum += inputSignals[i];
  }
  return sum/3;
}
