from PIL import Image

FRAME_COUNT = 6572

for i in range(1, FRAME_COUNT + 1):
	img = Image.open("shots/shot%d.png" % i)
	old_img = img.crop((0, 30, 954, 830))
	old_size = old_img.size
	new_size = (1000, 1000)
	new_img = Image.new("RGB", new_size, (12, 12, 12))
	box = tuple((n - o) // 2 for n, o in zip(new_size, old_size))
	new_img.paste(old_img, box)
	new_img.save("cropped/crop%d.png" % i)