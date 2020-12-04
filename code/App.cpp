#include <stdio.h>
#include <stdint.h>

static float gCameraY;
static float gCameraX;
#include "mtEngine.h"

static void handelKeys(mt::Window* window)
{
    float Speed = 8;
    if( window->GetKey('W') )
    {
        gCameraY -= Speed;
    }
    if( window->GetKey('S') )
    {
        gCameraY += Speed;
    }
    if( window->GetKey('A') )
    {
        gCameraX -= Speed;
    }
    if( window->GetKey('D') )
    {
        gCameraX += Speed;
    }
}

int main()
{
    mt::Window window(1280, 720, "TM_2D_ENGINE!");
    mt::Renderer renderer(window.GetInfo());

    window.Init();
    //Valid OpenGLContext START HERE
    renderer.Init();
    window.SetVSync(true);

    mt::Texture SpriteSheet("../data/DCSpriteSheet.bmp");
    mt::TileMap Map(&SpriteSheet, "../data/map/lvl.map");

    mt::Sprite Nami("../data/nami.bmp", mt::vec2{800, 100});
    renderer.AddSprite(&Nami);

    while(!window.ShoudClose())
    {
        printf("%f\n", mt::Time::GetDeltaTime());
        window.Clear(0.0f, 0.0f, 0.0f);

        handelKeys(&window);

        renderer.Draw();
        Map.Draw();
        renderer.DrawRect(mt::vec2{300, 300}, mt::vec2{100, 100}, mt::vec4{1,0,0,1});
        renderer.DrawRect(mt::vec2{400, 300}, mt::vec2{100, 100}, mt::vec4{0,1,0,1});


        window.Update();
    }

    Nami.GetTexture()->FreeTexture();
    SpriteSheet.FreeTexture();



    return 0;
}
