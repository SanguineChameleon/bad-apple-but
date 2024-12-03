from PIL import Image
import sys

FRAME_COUNT = 6572

alpha = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

with open("presets.txt", "w") as sys.stdout:
	for i in range(1, FRAME_COUNT + 1):
		img = Image.open("frames/frame%d.png" % i)
		img = img.resize((106, 17))
		pix = img.load()
		a = [[None] * 106 for _ in range(17)]
		for y in range(17):
			for x in range(106):
				S = round((pix[x, y][0] + pix[x, y][1] + pix[x, y][2]) / 3)
				if S <= 127:
					a[y][x] = 1
				else:
					a[y][x] = 0

		val = 0
		for x in range(106):
			for y in range(16, -1, -1):
				val = val * 2 + a[y][x]
		S = ""
		while val > 0:
			S += alpha[val % 62]
			val //= 62
		S = S[::-1]
		print(S)