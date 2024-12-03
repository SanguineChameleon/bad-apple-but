from PIL import Image
import sys

scale = 3
colors = [(255, 255, 255), (0, 0, 0)]

with open("rect.txt", "r") as sys.stdin:
	img = Image.new("RGB", (480 * scale, 360 * scale), (255, 0, 0))
	pix = img.load()
	cnt = 0
	for y in range(360):
		for x in range(480):
			D = int(input())
			for b in range(scale):
				for a in range(scale):
					pix[x * scale + a, y * scale + b] = colors[D]
	img.save("rect/frame%s.png" % sys.argv[1])