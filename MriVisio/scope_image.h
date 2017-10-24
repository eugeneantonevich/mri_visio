#pragma once

#include "definitions.h"

class scope_image
{
public:
	scope_image(image_t img)
	{
		m_img = img;
	}

	image_t operator = (image_t img)
	{
		m_img = img;
	}

	image_t operator* ()
	{
		return m_img;
	}

	~scope_image()
	{
		cvReleaseImage(&m_img);
	}
private:
	image_t m_img;
};
