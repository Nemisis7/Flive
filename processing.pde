import processing.serial.*; //imports processing serial from the library
Serial myPort; // Initialise a variable for the serial port.
void setup() {
  size(300, 300); // Create a canvas. We just have to have a canvas as this is a processing sketch, although it won't be used.
  
  println(Serial.list()); // List active USB Ports.
  myPort = new Serial(this, "/dev/cu.usbmodem1441", 9600); // Initialise serial port. 
  myPort.bufferUntil('n'); // Get data from serial port.
}

void draw() { // Function that runs every frame
  background(0, 0, 0); // Set background of canvas to black
    String[] lines = loadStrings("http://198.211.125.38:3000/app/?GET"); // Send GET HTTP Request to Server and return Text data.
    String message = lines[0]; // Get the text on line 1.
    
    for(int i = 0; i < message.length(); i++){ // Loop through the caharacters on the line.
     myPort.write(message.charAt(i)); // Send each character individually through the serial port to the Arduino.
    }
   
   myPort.write("_"); // At the end of the text, send an underscore to signify the text is finished.
   myPort.clear(); // Clear data going through the serial port and restart.
}