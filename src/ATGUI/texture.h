#pragma once

#include "../interfaces.h"
#include "../Utils/lodepng.h"
#include "../Utils/xorstring.h"
#include <iostream>

class Texture
{
public:

		unsigned char* ldImg(const char* filename, int w, int h)
		{
			std::vector<unsigned char> image;
			unsigned width, height;
			width = w;
			height = h;
			unsigned error = lodepng::decode(image, width, height, filename);
			if ( error ) std::cout << "decoder error " << error << ": " << lodepng_error_text ( error ) << std::endl;
			unsigned char* a = new unsigned char[image.size()];
			std::copy(image.begin(), image.end(), a);
			image.clear();
			return a;
		}

        Texture(const unsigned char* data, const unsigned int& width, const unsigned int& height)
            : m_width(width), m_height(height), m_bg(255, 255, 255, 255), m_valid(false)
        {
                m_iTexture = surface->CreateNewTextureID(true);
                if (!m_iTexture)
                        return;
				const unsigned char* converted_data = ldImg(data, width, height);
                surface->DrawSetTextureRGBA(m_iTexture, converted_data, width, height);
                m_valid = true;
        }

        bool IsValid() const
        {
                return m_valid;
        }

	unsigned int GetTextureId() const
	{
		return m_iTexture;
	}

	bool Draw(const unsigned int& x, const unsigned int& y, const unsigned int& w, const unsigned int& h)
	{
		if (!surface->IsTextureIDValid(m_iTexture))
			return false;
		surface->DrawSetColor(m_bg);
		surface->DrawSetTexture(m_iTexture);
		surface->DrawTexturedRect(x, y, x+w, y+h);

		return true;
	}

private:
        unsigned int m_width;
        unsigned int m_height;

        unsigned int m_iTexture;
        Color m_bg;
        bool m_valid;

};
