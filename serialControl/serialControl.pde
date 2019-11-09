import processing.serial.*;       //use the Serial library
Serial myPort;                    // Create object from Serial class   

void setup() {
  size(200, 200);                                  //set window size to 200 by 200 pixels
  String portName = "/dev/ttyACM1";              //list serial ports, save the first one as portName
  myPort = new Serial(this, portName, 9600);       //initialize the serial port object
}

void draw() {                    //this is like the 'loop' section of code on Arduino
  background(255);           // set background color
}

void keyPressed() {
    if (  key == 's' || key == 'S'  ){  
      myPort.write(key);  
      println(key);  
    }   
    if (  key == 'a' || key == 'A'  ){  
    myPort.write(key);  
    println(key);  
  }   // if the key is a or A, write it to the serial port
    
}


 
