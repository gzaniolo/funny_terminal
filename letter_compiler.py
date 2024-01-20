
class char_points:
  def __init__ (self, x_points, y_points, pen_points):
    self.x_points = x_points
    self.y_points = y_points
    self.pen_points = pen_points

file = open("./letter_doc.txt","r")
data = file.read()
file.close()

lines = data.split("\n")
removed_comments = [item for item in lines if len(item) > 0 and item[0] != "#"]

curr_char = 33
char_dict = {}
i = 0
x_points = []
y_points = []
for line in removed_comments:
  # split line into ints
  split_nums = line.split(",")
  nums = [int(item) for item in split_nums]
  if i == 0:
    x_points = nums
  elif i == 1:
    y_points = nums
  elif i == 2:
     assert len(x_points) == len(y_points) and len(x_points) == len(nums), \
      f"Different length arrays for a given char: {chr(curr_char)}"
     char_dict[curr_char] = char_points(x_points,y_points,nums)
     curr_char += 1

  i = (i + 1) % 3


# # Quick verification:
# print(char_dict[ord('a')].x_points)
# print(char_dict[ord('a')].y_points)
# print(char_dict[ord('a')].pen_points)
  
file = open("./sketch_sep29a/letters_gen.c","w")

file.write("#include \"letters_gen.h\"\n\n")

file.write("uint8_t fullXList_arr[] = {")
# write big x array
for i in range(128):
  if i in char_dict:
    for elem in char_dict[i].x_points:
      file.write(f"{elem},")
  file.write("-1,")
file.write("-1};\n")

file.write("uint8_t fullYList_arr[] = {")
# write big x array
for i in range(128):
  if i in char_dict:
    for elem in char_dict[i].y_points:
      file.write(f"{elem},")
  file.write("-1,")
file.write("-1};\n")

file.write("uint8_t fullPenUpList_arr[] = {")
# write big x array
for i in range(128):
  if i in char_dict:
    for elem in char_dict[i].x_points:
      file.write(f"{elem},")
  file.write("-1,")
file.write("-1};\n\n")

file.write("void letters_gen_init() {\n")
file.write("  fullXList = fullXList_arr;\n")
file.write("  fullYList = fullYList_arr;\n")
file.write("  fullPenUpList = fullPenUpList_arr;\n")
file.write("}\n")