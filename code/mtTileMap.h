#ifndef TM_TILE_MAP_H
#define TM_TILE_MAP_H

#include "mtSprite.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

namespace mt {

    class TileMap
    {
    private:
        Texture* m_SpriteSheet;
        file_result m_MapSrpitesFile;

        Sprite m_MapSrpites[4];
        std::vector<int> m_Tiles;

        int m_MapWidth;
        int m_MapHeight;

        void ProcessMapFile(const char* filepath);
        void InitMapTextures();
        std::vector<int> splitMap(std::string line, std::string delim);
    public:
        TileMap(Texture* texture, const char* filepath);
        TileMap(const char* filepath);
        ~TileMap();
        void Draw();
    };

    TileMap::TileMap(Texture* texture, const char* filepath)
    {
        m_SpriteSheet = texture;
        m_MapWidth = 0;
        m_MapHeight = 0;
        InitMapTextures();
        ProcessMapFile(filepath);
    }

    TileMap::TileMap(const char* filepath)
    {
        //TODO: Make this function works
    }

    TileMap::~TileMap()
    {

    }

    void TileMap::InitMapTextures()
    {
        m_MapSrpites[1] = Sprite(m_SpriteSheet, vec2{0, 0}, Rect{0, 14, 32, 32});
        m_MapSrpites[2] = Sprite(m_SpriteSheet, vec2{0, 0}, Rect{29, 13, 32, 32});
        m_MapSrpites[3] = Sprite(m_SpriteSheet, vec2{0, 0}, Rect{55, 14, 32, 32});
    }

    void TileMap::Draw()
    {
        for(int y = 0; y < m_MapHeight; y++)
        {
            for(int x = 0; x < m_MapWidth; x++)
            {
                if(m_Tiles[x + y * m_MapWidth] != 0)
                {
                    int scale = 1;
                    Sprite tile = m_MapSrpites[m_Tiles[x + y * m_MapWidth]];
                    tile.SetPosition(vec2{(float)x*32*scale, (float)y*32*scale});
                    tile.Draw();
                }
            }
        }
    }

    void TileMap::ProcessMapFile(const char* filepath)
    {
        std::string line;
        std::ifstream mapFile;

        mapFile.open(filepath, std::ios::in);
        if(mapFile.is_open())
        {
            std::vector<int> tileLine;
            while(getline(mapFile, line))
            {
                tileLine = splitMap(line, " ");
                for(int tile : tileLine)
                {
                    m_Tiles.push_back(tile);
                }
                m_MapHeight++;
            }
            m_MapWidth = tileLine.size();
            mapFile.close();
        }
    }

    std::vector<int> TileMap::splitMap(std::string str, std::string delim)
    {
        std::vector<int> Tokens;
        int pos, prev = 0;
        while(pos < str.length() && prev < str.length())
        {
            pos = str.find(delim, prev);
            int token = stoi(str.substr(prev, pos-prev));
            Tokens.push_back(token);
            prev = pos + delim.length();
        }

        return Tokens;
    }
}

#endif
