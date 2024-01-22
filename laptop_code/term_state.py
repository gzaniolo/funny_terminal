import os
import time


def dummy_print_term(buf: str):
  print("---------------------------\n\n")
  i = 0
  for c in buf:
    if c == "\n":
      print(' ',end='')
    else:
      print(c,end='')
    if i % 16 == 15:
      print("")
    i += 1
  print("\n---------------------------\n\n")
  i=0
  for c in buf:
    print(ord(c),end=' ')
    if i % 16 == 15:
      print("")
    i += 1
  print("\n\n")

# dummy_print_term("somebody once told me the world was gonna roll me, I ain't the sharpest tool in the shed")

# sequences
newl = chr(27) + "[?2004h"
newl2 = chr(27) + "[?2004l\n"
bel = chr(7)
bs = chr(8) + chr(27) + "[K"



term_file_path = "./curr_term.log"

term_file = open(term_file_path,"r")

arduino_file = open("/dev/ttyACM1","w")

# TODO delete
test_file = open("./test.log","w")

file_size = os.path.getsize(term_file_path)

term_file.seek(0,os.SEEK_END)

acc_term = ""
prev_acc = ""

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
      bytes_add = (16 - (i % 16))
      acc_send += " " * bytes_add
      i += bytes_add
    else:
      acc_send += c
      i += 1
  # top off last row 
  acc_send += " " * (16 - (i % 16))
  # Remove any extra prior stuff
  acc_send = acc_send[-256:]


  # Send terminal bytes
  if acc_send != prev_acc:
    # TODO remove
    dummy_print_term(acc_send)
    prev_acc = acc_send
    
    acc_send = acc_send + "\n"
    arduino_file.write(acc_send)
    arduino_file.flush()
    # TODO remove
    test_file.write(acc_send)
    test_file.write("\n")
    test_file.flush()

  acc_term = acc_term[-256*4:]
  time.sleep(.1)


