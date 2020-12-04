#ifndef TM_UTILS_H
#define TM_UTILS_H

#include <Windows.h>
#include <stdint.h>

namespace mt {
    struct Rect
    {
        int x;
        int y;
        int w;
        int h;
    };

    struct file_result
    {
        uint32_t FileSize;
        void* Content;
    };

#pragma pack(push, 1)
    struct bmp_header
    {
        uint16_t FileType;
        uint32_t FileSize;
        uint32_t Reserved;
        uint32_t Offset;
        uint32_t HeaderSize;
        uint32_t Width;
        uint32_t Height;
        uint16_t Planes;
        uint16_t BitsPerPixel;
        uint32_t Compression;
        uint32_t SizeOfBitmap;
        int32_t HorzResolution;
        int32_t VertResolution;
        uint32_t ColorsUsed;
        uint32_t ColorsImportant;

        uint32_t RedMask;
        uint32_t GreenMask;
        uint32_t BlueMask;
    };
#pragma pack(pop)

    struct bmp_image
    {
        int32_t Width;
        int32_t Height;
        uint32_t* Pixels;
    };

    file_result LoadFile(const char* Filepath)
    {
        file_result Result = {};
        HANDLE FileHande = CreateFileA(Filepath, GENERIC_READ, FILE_SHARE_READ, 0,
                                               OPEN_EXISTING, 0, 0);
        LARGE_INTEGER FileSize;
        if(GetFileSizeEx(FileHande, &FileSize))
        {
            Result.FileSize = FileSize.QuadPart;
            Result.Content = malloc(Result.FileSize);
            if(Result.Content)
            {
                DWORD BytesRead;
                if(!ReadFile(FileHande, Result.Content, Result.FileSize, &BytesRead, 0) &&
                            Result.FileSize == BytesRead)
                {
                    free(Result.Content);
                }
            }
        }
        return Result;
    }

    bmp_image LoadBMP(const char* Filepath)
    {
        bmp_image Image = {};
        uint32_t* NewImage = 0;
        file_result File = LoadFile(Filepath);
        bmp_header* ImageFile = (bmp_header*)File.Content;
        if(ImageFile)
        {
            Image.Pixels = (uint32_t*)((uint8_t*)File.Content + ImageFile->Offset);
            Image.Width = ImageFile->Width;
            Image.Height = ImageFile->Height;

            NewImage = (uint32_t*)malloc(ImageFile->Width*ImageFile->Height*32);

            for(int32_t y = (ImageFile->Height-1); y >= 0; y--)
            {
                for(int32_t x = 0; x < ImageFile->Width; x++)
                {
                    uint8_t Red, Green, Blue, Alpha = 0;
                    uint8_t* color = (uint8_t*)&Image.Pixels[x + (y * ImageFile->Width)];
                    Blue  = color[0];
                    Green = color[1];
                    Red   = color[2];
                    Alpha = color[3];

                    NewImage[x + (((ImageFile->Height-1) - y) * ImageFile->Width)] = Alpha << 24 | Blue << 16 | Green << 8 | Red;
                }
            }
        }
        Image.Pixels = NewImage;
        free(File.Content);
        return Image;
    }
}

#endif
