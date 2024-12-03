from PIL import Image

FRAME_COUNT = 6572
alpha = "abcdefghijklmnopqrstuvwxyz"

def over(ca, cb):
	return (merge(ca[0], cb[0]), merge(ca[1], cb[1]), merge(ca[2], cb[2]))

colors = [("gray", (58, 58, 60)), ("yellow", (177, 160, 76)), ("green", (97, 140, 85))]
for i in range(26):
	img = Image.open("letter_shots/letter_%s.png" % alpha[i])
	img = img.crop((785, 184, 850, 249))
	for color_name, color_val in colors:
		new_img = img.copy()
		pix = new_img.load()
		for y in range(65):
			for x in range(65):
				if pix[x, y] == (86, 87, 88):
					pix[x, y] = (18, 18, 19)
				pix[x, y] = (255 - pix[x, y][0], 255 - pix[x, y][1], 255 - pix[x, y][2])
				avg = 0.21 * pix[x, y][0] + 0.72 * pix[x, y][1] + 0.07 * pix[x, y][2]
				pix[x, y] = (255 - round(avg * (255 - color_val[0]) / 255) , 255 - round(avg * (255 - color_val[1]) / 255), 255 - round(avg * (255 - color_val[2]) / 255))
		new_img.save("letters/letter_%s_%s.png" % (alpha[i], color_name))