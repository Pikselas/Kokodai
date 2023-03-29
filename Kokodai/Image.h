#pragma once
#include<memory>
#include<filesystem>
#include"GDIPlusManager.h"

struct ColorType
{
	unsigned char b = 255;
	unsigned char g = 255;
	unsigned char r = 255;
	unsigned char a = 255;
};

class Image
{
private:
	unsigned int height = 0;
	unsigned int width = 0;
	std::unique_ptr<ColorType[]> PIXEL_DATA = nullptr;
public:
	Image(const std::filesystem::path& file);
	Image(unsigned int width, unsigned height);
	unsigned int GetHeight() const;
	unsigned int GetWidth() const;
	ColorType GetPixel(unsigned int x , unsigned int y) const;
	void SetPixel(unsigned int x, unsigned int y, ColorType color);
	const ColorType* GetRaw() const;
};