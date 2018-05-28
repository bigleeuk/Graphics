// ------------------------------------------------------------------------------------------------
// Image class Implementation file
// ------------------------------------------------------------------------------------------------
#include "ImageProc.h"
// ------------------------------------------------------------------------------------------------
// Convert to gray-scale
// ------------------------------------------------------------------------------------------------

void ImageProc::convertToGray()
{
	int  x, y;
	byte R, G, B;
	byte Gray;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			Gray = xClip(0.299*R + 0.587*G + 0.114*B);

			setPixel(x, y, Gray, Gray, Gray);
		}
	}
}

void ImageProc::convertToSepia()
{
	int  x, y;
	byte R, G, B;
	byte _R, _G, _B;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			_R = xClip(0.393*R + 0.769*G + 0.189*B);
			_G = xClip(0.349*R + 0.686*G + 0.168*B);
			_B = xClip(0.272*R + 0.534*G + 0.131*B);
			setPixel(x, y, _R, _G, _B);
		}
	}

}

void ImageProc::samplingBy2()
{
	int  x, y;
	byte R, G, B;
	byte* rgb = new byte[(m_iWidth*m_iHeight * 3) / 4];
	for (y = 0; y < m_iHeight / 2; y++)
	{
		for (x = 0; x < m_iWidth / 2; x++)
		{

			getPixel(x * 2, y * 2, R, G, B);
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 0] = R;
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 1] = G;
			rgb[(y * (m_iWidth / 2) * 3 + x * 3) + 2] = B;
		}
	}
	setRGB(rgb);
	m_iWidth /= 2;
	m_iHeight /= 2;
}

void ImageProc::quantization(int step)
{
	int  x, y;
	byte R, G, B;
	byte Gray;

	for (y = 0; y < m_iHeight; y++)
	{
		for (x = 0; x < m_iWidth; x++)
		{
			getPixel(x, y, R, G, B);

			for (int i = 0; i < 255 / step; i++) {
				if (step * i <= R && R < step * (i + 1)) {
					R = step * i;
				}
				if (step * i <= G && G < step * (i + 1)) {
					G = step * i;
				}
				if (step * i <= B && B < step * (i + 1)) {
					B = step * i;
				}
			}

			setPixel(x, y, R, G, B);
		}
	}
}

void ImageProc::Kuwahara() {
	int x;
	int y;
	byte R;
	byte G;
	byte B;

	struct info {
		int x;
		int y;
		byte R;
		byte G;
		byte B;


	};
	info Mask[25];
	info Block[9];

	double  avgR, avgB, avgG, val, avgMinR, avgMinB, avgMinG, valMin = 10000000000, sumR, sumB, sumG;

	for (int i = 0; i < m_iHeight; i++) {
		for (int j = 0; j < m_iWidth; j++) {
			for (int n = 0; n < 5; n++) {
				for (int m = 0; m < 5; m++) {
					getPixel(i + n - 2, j + m - 2, R, G, B);

					Mask[n * 5 + m].x = i + n;
					Mask[n * 5 + m].y = j + m;

					if (i + n - 2> m_iHeight || j + m - 2> m_iWidth) {
						getPixel(i + n + 1, j + m + 1, R, G, B);
						Mask[n * 5 + m].R = R;
						Mask[n * 5 + m].G = G;
						Mask[n * 5 + m].B = B;
					}
					else {
						Mask[n * 5 + m].R = R;
						Mask[n * 5 + m].G = G;
						Mask[n * 5 + m].B = B;
					}

					// 3*3 크기배열값을마스크배열에할당
				}
			}
			for (int n = 0; n < 3; n += 2) {
				for (int m = 0; m < 3; m += 2) {
					for (int a = 0; a < 3; ++a) {
						for (int b = 0; b < 3; ++b) {
							Block[a * 3 + b].x = Mask[(a + n) * 5 + b + m].x;
							Block[a * 3 + b].y = Mask[(a + n) * 5 + b + m].y;
							Block[a * 3 + b].G = Mask[(a + n) * 5 + b + m].G;
							Block[a * 3 + b].R = Mask[(a + n) * 5 + b + m].R;
							Block[a * 3 + b].B = Mask[(a + n) * 5 + b + m].B;
						}
					}
					sumR = 0;
					sumG = 0;
					sumB = 0;
					for (int a = 0; a < 9; ++a) {
						sumR += Block[a].R;
						sumG += Block[a].G;
						sumB += Block[a].B;
					}
					avgR = sumR / 9.0;
					avgG = sumG / 9.0;
					avgB = sumB / 9.0;

					sumR = 0;
					sumG = 0;
					sumB = 0;
					for (int a = 0; a < 9; ++a) {
						sumR += (Block[a].R - avgR)*(Block[a].R - avgR);
						sumB += (Block[a].B - avgB)*(Block[a].B - avgB);
						sumG += (Block[a].G - avgG)*(Block[a].G - avgG);
					}
					val = sumR + sumG + sumB / 8;
					if (valMin > val) {
						valMin = val;
						avgMinR = avgR;
						avgMinB = avgB;
						avgMinG = avgG;
					}
				}
			}
			setPixel(i, j, avgMinR, avgMinG, avgMinB);
			valMin = 10000000000;
		}
	}
}