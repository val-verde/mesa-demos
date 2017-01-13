//////////////////////////////////////////////////////////////////////////////////////////
//	IMAGE.h
//	functions for images to be turned to textures
//	Downloaded from: www.paulsprojects.net
//	Created:	20th July 2002
//
//	Copyright (c) 2006, Paul Baker
//	Distributed under the New BSD Licence. (See accompanying file License.txt or copy at
//	http://www.paulsprojects.net/NewBSDLicense.txt)
//////////////////////////////////////////////////////////////////////////////////////////	

#ifndef IMAGE_H
#define IMAGE_H

#include <stdio.h>

class IMAGE
{
public:
	IMAGE() : data(NULL), bpp(0), width(0), height(0)
	{}

	~IMAGE()
	{
		if(data)
			delete [] data;
		data=NULL;
	}
	
	bool Load(const char * filename);					//load a texture from a file

	bool LoadBMP(const char * filename);				//Load BMP
	bool Load24BitBMP(const char * filename);
	bool Load8BitBMP(const char * filename);

	bool LoadPCX(const char * filename);				//Load PCX

	bool LoadTGA(const char * filename);				//Load TGA
	bool LoadUncompressed8BitTGA(const char * filename);
	bool LoadUncompressedTrueColorTGA(const char * filename);
	bool LoadCompressedTrueColorTGA(const char * filename);
	
	//load an uncompressed greyscale TGA for alpha channel
	bool LoadAlphaTGA(const char * filename);

	//Alter the image
	void FlipVertically();

	unsigned char * data;				//Image data
	unsigned int	bpp;				//Image color depth in bits per pixel
	unsigned int	width;				//Image width
	unsigned int	height;			//Image height

	GLuint	 format;				//Data format, eg GL_RGBA
};

//Universal bitmap identifier
const DWORD BITMAP_ID=0x4D42;

#endif	//TEXTURE_IMAGE_H
