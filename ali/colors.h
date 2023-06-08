#pragma once
namespace ali {
	namespace colors{
		int rgb(int r, int g, int b) // Converts an RGB value to a HEX value
		{
			return (r << 16) | (g << 8) | b;
		}
		namespace windows {
			static enum colors {
				black = 0x0c0c0c,
				electric = 0x0037da,
				leaf = 0x13a10e,
				lightblue = 0x3a96dd,
				red = 0xc50f1f,
				darkpurple = 0x881798,
				gold = 0xc19c00,
				lightgrey = 0xcccccc,
				grey = 0x767676,
				blue = 0x3b78ff,
				green = 0x16c60c,
				aqua = 0x61d6d6,
				salmon = 0xe74856,
				purple = 0xb4009e,
				yellow = 0xf9f1a5,
				white = 0xf2f2f2,
			};
		}
	}
}