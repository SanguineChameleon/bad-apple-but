s = ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. ----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----.".split()
s.append("/")
s.append(" ")
for x in s:
	chunks = []
	for y in x:
		if len(chunks) == 0 or (chunks[-1][-1] == "-" and y == "-"):
			chunks.append("")
		chunks[-1] += y
	print("{" + ", ".join(['"%s"' % ch for ch in chunks]) + "},",)