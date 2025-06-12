#include <Arduino.h>
#include <BufferManager.h>

void setup() {
  Serial.begin(115200);

  // Define memory configuration
  bufferManager.init(Block(2, 32), Block(2, 64), Block(2, 128));

  // Get a buffer of 65 bytes
  Buffer* buf = bufferManager.get(65);
  if (buf) {
    buf[0] = 42;  // Write a value
    Serial.print("Buffer[0] = ");
    Serial.println(buf[0]);  // Read it back
    Serial.println(buf->size());
    buf->release();             // Release buffer after use
  } else {
    Serial.println("No buffer available!");
  }
}

void loop() {
  // Nothing here
}
