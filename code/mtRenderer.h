#ifndef TM_RENDERER_H
#define TM_RENDERER_H

#include <GL/gl.h>
#include <vector>

#include "mtTexture.h"
#include "mtWindow.h"
#include "mtSprite.h"


namespace mt {

    class Renderer
    {
    private:
        window_info* m_WindowInfo;
        std::vector<Sprite*> m_Textures;
    public:
        Renderer(window_info* windowInfo);
        void AddSprite(Sprite* texture);
        void Init();
        void Draw();
        void DrawRect(vec2 pos, vec2 dim, vec4 color);
    };

    Renderer::Renderer(window_info* windowInfo)
    {
        m_WindowInfo = windowInfo;
    }

    void Renderer::Init()
    {
        //Initialize Projection Matrix to Identity
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho( 0.0f, m_WindowInfo->Width, m_WindowInfo->Height, 0.0f, 1.0f, -1.0f );

        //Initialize Modelview Matrix to Identity
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D);
    }

    void Renderer::DrawRect(vec2 pos, vec2 dim, vec4 color)
    {
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glTranslatef(pos.x, pos.y, 0.0f);
        glBegin(GL_QUADS);
            glColor3f(color.r, color.g, color.b );
            glVertex2f(0.0f, 0.0f);
            glVertex2f(dim.x, 0.0f);
            glVertex2f(dim.x, dim.y);
            glVertex2f(0.0f, dim.y);
            glColor3f(1, 1, 1);
        glEnd();
    }

    void Renderer::AddSprite(Sprite* sprite)
    {
        m_Textures.push_back(sprite);
    }

    void Renderer::Draw()
    {
        for(Sprite* sprite : m_Textures)
        {
            sprite->GetTexture()->Draw(sprite->GetPosition().x, sprite->GetPosition().y);
        }
    }
}

#endif
