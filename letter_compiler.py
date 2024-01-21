
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
  
file = open("./sketch_sep29a/letters_gen.h","w")

file.write("\n")
file.write("#ifndef _LETTERS_GEN_H_\n")
file.write("#define _LETTERS_GEN_H_\n\n")

file.write("#include <stdint.h>\n\n")

file.write("int8_t fullLetterList[] = {")
# write big x array
for i in range(128):
  if i in char_dict:
    for j in range(len(char_dict[i].x_points)):
      elem = char_dict[i].x_points[j] + (char_dict[i].y_points[j] << 2) \
        + (char_dict[i].pen_points[j] << 4)
      file.write(f"{elem},")
  file.write("-1,")
file.write("-1};\n\n")

file.write("#endif\n")
