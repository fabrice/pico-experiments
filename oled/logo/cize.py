
from PIL import Image

img = Image.open("/Users/fabrice/cfpt-e.png")
#img = img.resize((128, 64), Image.LANCZOS)
img = img.convert("1", dither=Image.Dither.NONE)

# SSD130x format: each byte is a vertical column of 8 pixels, LSB on top
width, height = 128, 160
pixels = img.load()

data = []
for page in range(height / 8):
	for x in range(width):
		byte = 0
		for bit in range(8):
			y = page * 8 + bit
			if pixels[x, y] == 0:  # black pixel in source → lit on OLED
				byte |= (1 << bit)
		data.append(byte)

# Print as C array
print("static const uint8_t cfpt_logo[] = {")
for i in range(0, len(data), 16):
	line = ", ".join(f"0x{b:02X}" for b in data[i:i+16])
	print(f"    {line},")
print("};")
