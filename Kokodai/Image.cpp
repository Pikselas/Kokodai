#include "Image.h"

Image::Image(const std::filesystem::path& file)
{
	GDIPlusManager manager;
	Gdiplus::Bitmap bitmap(file.c_str());
	if (bitmap.GetLastStatus() == Gdiplus::Status::Ok)
	{
		height = bitmap.GetHeight();
		width = bitmap.GetWidth();
		PIXEL_DATA = std::make_unique<ColorType[]>(width * height);
		Gdiplus::Color c;
		for (auto i = 0; i < height; ++i)
		{
			for (auto j = 0; j < width; ++j)
			{
				bitmap.GetPixel(j, i, &c);
				ColorType color = { c.GetR() , c.GetG() , c.GetB() };
				SetPixel(j, i, color);
			}
		}
	}
}

Image::Image(unsigned int width,unsigned int height)
{
	this->width = width;
	this->height = height;
	PIXEL_DATA = std::make_unique<ColorType[]>(width * height);
}

unsigned int Image::GetHeight() const
{
    return height;
}

unsigned int Image::GetWidth() const 
{
    return width;
}

ColorType Image::GetPixel(unsigned int x, unsigned int y) const
{
	return PIXEL_DATA[width * y + x];
}

void Image::SetPixel(unsigned int x, unsigned int y, ColorType color)
{
	PIXEL_DATA[width * y + x] = color;
}

const ColorType* Image::GetRaw() const
{
	return PIXEL_DATA.get();
}
