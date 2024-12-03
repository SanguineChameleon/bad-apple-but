from PIL import Image

FRAME_COUNT = 6572

for i in range(1, FRAME_COUNT + 1):
	img = Image.open("shots/frame%d.png" % i)
	old_img = img.crop((190, 36, 1714, 954))
	old_size = old_img.size
	new_size = (1920, 1080)
	new_img = Image.new("RGB", new_size, (221, 221, 221))
	box = tuple((n - o) // 2 for n, o in zip(new_size, old_size))
	new_img.paste(old_img, box)
	new_img.save("cropped/frame%d.png" % i)