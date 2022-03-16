import matplotlib.pyplot as plt
from matplotlib import font_manager

for font in font_manager.fontManager.ttflist:
	if 'Gothic' in font.name:
		print(font.name, font.fname)