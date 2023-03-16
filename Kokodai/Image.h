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
	size_t height = 0 ;
	size_t width = 0;
	std::unique_ptr<ColorType[]> PIXEL_DATA = nullptr;
public:
	Image(const std::filesystem::path& file);
	size_t GetHeight() const;
	size_t GetWidth() const;
	ColorType GetPixel(unsigned int x , unsigned int y) const;
	void SetPixel(unsigned int x, unsigned int y, ColorType color);
	const ColorType* GetRaw() const;
};