import PIL

from PIL import Image
import os

# read all the images in the current folder
# and place them by their size
# if 16*16, then place in "16" folder
# if 48* 48 then place in "48" folder

def sort_image():
    for filename in os.listdir(os.getcwd()):
        if filename.endswith(".png"):
            img = Image.open(filename)
            width, height = img.size
            if width == 16 and height == 16:
                if not os.path.exists("16"):
                    os.makedirs("16")
                os.rename(filename, "16/" + filename)
            elif width == 48 and height == 48:
                if not os.path.exists("48"):
                    os.makedirs("48")
                os.rename(filename, "48/" + filename)