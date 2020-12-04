#ifndef TM_SPRITE_H
#define TM_SPRITE_H

#include "mtTexture.h"
#include "mtMath.h"

namespace mt {

    class Sprite
    {
    private:
        Texture m_Tex;
        vec2 m_Pos;
    public:

        Sprite();
        Sprite(Texture* tex, vec2 pos, Rect rec = {});
        Sprite(const char* filepath, vec2 pos);

        void Draw();

        uint32_t GetWidth()const { return m_Tex.GetWidth(); }
        uint32_t GetHegiht()const { return m_Tex.GetHeight(); }
        Texture* GetTexture() { return &m_Tex; }
        vec2 GetPosition()const { return m_Pos; }
        void SetPosition(vec2 pos) { m_Pos = pos; }
        void SetWidth(uint32_t w) { m_Tex.SetWidth(w); }
        void SetHegiht(uint32_t h) { m_Tex.SetHegiht(h); }
    };

    Sprite::Sprite()
    {

    }

    Sprite::Sprite(Texture* tex, vec2 pos, Rect rec)
    {
        m_Tex = *tex;
        m_Tex.ChangeRectPosition(rec);
        m_Pos = pos;
    }

    Sprite::Sprite(const char* filepath, vec2 pos)
    : m_Tex(filepath)
    {
        m_Pos = pos;
    }

    void Sprite::Draw()
    {
        m_Tex.Draw(m_Pos.x ,m_Pos.y);
    }

}
#endif
