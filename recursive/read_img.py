from PIL import Image
import sys
img = Image.open(sys.argv[1])
pix = img.load()
with open("data.txt", "w") as sys.stdout:
	for y in range(img.size[1]):
		for x in range(img.size[0]):
			S = pix[x, y][0] + pix[x, y][1] + pix[x, y][2]
			print(round(S / 3))