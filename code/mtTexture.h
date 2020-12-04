#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/gl.h>
#include "mtUtils.h"

namespace mt {
    class Texture
    {
    private:
        uint32_t m_TextureID;
        uint32_t* m_Pixels;
        Rect m_Rect;
        Rect m_Clip;

        int m_ImageWidth;
        int m_ImageHeight;
    public:
        Texture();
        Texture(const char* filepath);
        ~Texture();
        void LoadTextureFromBMP(const char* fileath);
        void FreeTexture();

        void ChangeRectPosition(Rect rect);
        void Draw(float x, float y);

        uint32_t GetTextureID()const { return m_TextureID; }
        uint32_t GetWidth()const { return m_Rect.w; }
        uint32_t GetHeight()const { return m_Rect.h; }
        void SetWidth(uint32_t w) { m_Rect.w = w; }
        void SetHegiht(uint32_t h) { m_Rect.h = h; }

        void SetRect(Rect rec){ m_Rect = rec; }
    };

    Texture::Texture()
    {
        m_TextureID = 0;
        m_Rect = {};
        m_Clip = {0, 0, 1, 1};
        uint32_t* m_Pixels = 0;
        m_ImageWidth = 0;
        m_ImageHeight = 0;
    }

    Texture::Texture(const char* filepath)
    {
        m_TextureID = 0;
        m_Rect = {};
        m_Clip = {0, 0, 1, 1};
        uint32_t* m_Pixels = 0;
        LoadTextureFromBMP(filepath);
    }

    Texture::~Texture()
    {
    }

    void Texture::ChangeRectPosition(Rect rect)
    {
        m_Rect = rect;
        int xx = m_Rect.x*m_Rect.w;
        int yy = m_Rect.y*m_Rect.h;
        m_Clip = { xx, yy, xx + m_Rect.w, yy + m_Rect.h };
    }

    void Texture::LoadTextureFromBMP(const char* fileath)
    {
        FreeTexture();
        bmp_image sprite = LoadBMP(fileath);
        m_Pixels = sprite.Pixels;
        m_ImageWidth =  sprite.Width;
        m_ImageHeight = sprite.Height;
        m_Rect.w = sprite.Width;
        m_Rect.h = sprite.Height;

        m_Clip = {m_Rect.x*m_Rect.w, m_Rect.y*m_Rect.h, m_ImageWidth, m_ImageHeight};
        glGenTextures(1, &m_TextureID);
        glBindTexture(GL_TEXTURE_2D, m_TextureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_ImageWidth, m_ImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Pixels);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glBindTexture(GL_TEXTURE_2D, 0);
    }


    void Texture::FreeTexture()
    {
        if(m_TextureID != 0)
        {
            glDeleteTextures(1, &m_TextureID);
            m_TextureID = 0;
        }
    }

    void Texture::Draw(float x, float y)
    {
        if(m_TextureID != 0)
        {
            int scale = 1;
            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            glTranslatef(x, y, 0.0f);
            glColor3f(1, 1, 1);
            glBindTexture(GL_TEXTURE_2D, m_TextureID);
            float texLeft = (float)m_Clip.x / (float)m_ImageWidth;
            float texRight = (float)m_Clip.w / (float)m_ImageWidth;
            float texTop = (float)m_Clip.y / (float)m_ImageHeight;
            float texBottom = (float)m_Clip.h / (float)m_ImageHeight;
            glBegin(GL_QUADS);
                glTexCoord2f(texLeft, texTop); glVertex2f(0.0f, 0.0f);
                glTexCoord2f(texRight, texTop); glVertex2f(m_Rect.w*scale, 0.0f);
                glTexCoord2f(texRight, texBottom); glVertex2f(m_Rect.w*scale, m_Rect.h*scale);
                glTexCoord2f(texLeft, texBottom); glVertex2f(0.0f, m_Rect.h*scale);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

#endif
