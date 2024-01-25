import os
import time
import serial

CHARS_PER_ROW = 8
# This is a very long time but it gets flickery if you refresh it too often
ITERS_FOR_REFRESH = 20

term_file_path = "./curr_term.log"
arduino_file_path = "/dev/ttyACM0"

arduino_ser = serial.Serial(arduino_file_path, 115200)

def dummy_print_term(buf: str):
  print("---------------------------\n\n")
  i = 0
  for c in buf:
    if c == "\n":
      print(' ',end='')
    else:
      print(c,end='')
    if i % CHARS_PER_ROW == (CHARS_PER_ROW - 1):
      print("")
    i += 1
  print("\n---------------------------\n\n")
  i=0
  for c in buf:
    print(ord(c),end=' ')
    if i % CHARS_PER_ROW == (CHARS_PER_ROW - 1):
      print("")
    i += 1
  print("\n\n")


# sequences
newl = chr(27) + "[?2004h"
newl2 = chr(27) + "[?2004l\n"
bel = chr(7)
bs = chr(8) + chr(27) + "[K"


term_file = open(term_file_path,"r")

# TODO delete
test_file = open("./test.log","w")

file_size = os.path.getsize(term_file_path)

term_file.seek(0,os.SEEK_END)

acc_term = ""
prev_acc = ""

iters = 0

while(True):
  new_bytes = term_file.read()

  acc_term += new_bytes
  # Pattern match, if the last few are smth, remove it
  # if newline, remove
  acc_term = acc_term.replace(newl,"")
  acc_term = acc_term.replace(newl2,"")
  # if backspace, do action
  if acc_term[-len(bs):] == bs:
    acc_term = acc_term[:-(len(bs)+1)]
  # if bel, simple remove
  acc_term = acc_term.replace(bel,"")

  # Convert to terminal form
  i = 0
  acc_send = ""
  for c in acc_term:
    if c == "\n":
      bytes_add = (CHARS_PER_ROW - (i % CHARS_PER_ROW))
      acc_send += " " * bytes_add
      i += bytes_add
    else:
      acc_send += c
      i += 1
  # top off last row 
  acc_send += " " * (CHARS_PER_ROW - (i % CHARS_PER_ROW))
  # Remove any extra prior stuff
  acc_send = acc_send[-(CHARS_PER_ROW*CHARS_PER_ROW):]


  # Send terminal bytes
  if acc_send != prev_acc or iters == ITERS_FOR_REFRESH:
    iters = 0
    # TODO remove
    dummy_print_term(acc_send)
    prev_acc = acc_send
    
    acc_send = acc_send + "\n"
    acc_send_ascii = acc_send.encode("ascii","ignore")
    arduino_ser.write(acc_send_ascii)
    arduino_ser.flush()
    # TODO remove
    test_file.write(acc_send)
    test_file.write("\n")
    test_file.flush()

  acc_term = acc_term[-256*4:]

  iters += 1
  time.sleep(.1)


