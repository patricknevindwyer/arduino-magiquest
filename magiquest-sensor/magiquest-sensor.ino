

int bin_0 = 300; // microsecond skinny pulse
int bin_1 = 500; // microsecond wide pulse

int ir_pin = A0;
int ir_value = 0;

void setup() {

  pinMode(ir_pin, INPUT);
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  while (!Serial) {
    ;
  }

  Serial.println("Comms enabled - beginning sensing");
}

void loop() {
  // put your main code here, to run repeatedly:

//  ir_value = pulseIn(ir_pin, LOW);
  get_ir_alt();
//  Serial.println("WEEEE");
  
//  Serial.println("low_count");
//  Serial.println(low_count);

}

void get_ir() {

  // let's wait until we actually start getting data
  while ( pulseIn(ir_pin, LOW) < bin_0 ) {
    // nop
    ;
  }

  // we're going to read 104 bits of data
  //    7 bytes (56 bits) - header
  //    3 bytes (24 bits) - wand_id
  //    3 bytes (24 bits) - strength/direction data
  //
  //  see: openschemes.com/2013/02/27/mq-widget-pic12f508-controlled-magiquest-toy/3/
  int i = 0;
  int bit = 0;

  // eat the header
  for (i = 0; i < 56; i++) {
    bit = pulseIn(ir_pin, LOW);
  }

  // let's get a wand ID
  long wand_id = 0;
  for (i = 0; i < 24; i++) {
    bit = pulseIn(ir_pin, LOW);

    if (bit > bin_1) {
      wand_id = wand_id + 1;
    }
    wand_id = wand_id << 1;
  }
  Serial.print("wand: ");
  Serial.println(wand_id, HEX);

  // eat the strength data
  for (i = 0; i < 24; i++) {
    ;
  }
//  Serial.println("Read data...");

}

void get_ir_alt() {

  // we need to be able to read 24 bits
  int data[24];
  int counter;
  long wand_id = 0;
  
  while ( pulseIn(ir_pin, LOW) < bin_0 ) {
    // nop
    ;
  }

  // now let's read 55 more inputs
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  // read wand ID
  data[0] = pulseIn(ir_pin, LOW);
  data[1] = pulseIn(ir_pin, LOW);
  data[2] = pulseIn(ir_pin, LOW);
  data[3] = pulseIn(ir_pin, LOW);
  data[4] = pulseIn(ir_pin, LOW);
  data[5] = pulseIn(ir_pin, LOW);
  data[6] = pulseIn(ir_pin, LOW);
  data[7] = pulseIn(ir_pin, LOW);

  data[8] = pulseIn(ir_pin, LOW);
  data[9] = pulseIn(ir_pin, LOW);
  data[10] = pulseIn(ir_pin, LOW);
  data[11] = pulseIn(ir_pin, LOW);
  data[12] = pulseIn(ir_pin, LOW);
  data[13] = pulseIn(ir_pin, LOW);
  data[14] = pulseIn(ir_pin, LOW);
  data[15] = pulseIn(ir_pin, LOW);

  data[16] = pulseIn(ir_pin, LOW);
  data[17] = pulseIn(ir_pin, LOW);
  data[18] = pulseIn(ir_pin, LOW);
  data[19] = pulseIn(ir_pin, LOW);
  data[20] = pulseIn(ir_pin, LOW);
  data[21] = pulseIn(ir_pin, LOW);
  data[22] = pulseIn(ir_pin, LOW);
  data[23] = pulseIn(ir_pin, LOW);

  // eat the last 24 bits
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);
  pulseIn(ir_pin, LOW);

  // convert bits to id
  for (counter = 0; counter < 24; counter++) {

    if (data[counter] > bin_1) {
      wand_id = wand_id + 1;
    }
    wand_id = wand_id << 1;
    
  }

  Serial.print("wand_id: ");
  Serial.println(wand_id, HEX);
}

