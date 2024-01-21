
import time

arduino_file = open("/dev/ttyACM1","w")

i = 0

while True:
  arduino_file.write(f"testing a string: {i}\n")
  time.sleep(1)
  i += 1