
#include "text.hpp"
#include "raylib.h"

#include <iostream>
#include <vector>
#include <random>
#include <string>


int main(void)
{

    const int screenWidth = 800;
    const int screenHeight = 600;
    
    int fontScale = 1;
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Text Engine");

    FontSet cset; //cset is character set
    cset.font = LoadTexture("./ansifont8x12.png"); //ansifont8x12 is a 8px wide 12px tall font set, kind of formated like dwarf fortress but a bit off
    cset.fWidth = 8;
    cset.fHeight = 12;
    cset.rowSize = 16 - 1;
    cset.columnSize = 17 - 1;


    //Snake code
    int pX = 0;
    int pY = 0;
    Vector2 applePos = {0,0};
    std::vector<Vector2> snakeParts;
    std::vector<Vector2> history;
    std::vector<Vector2> hisRev;
    int score = 0;

    int frameCounter = 0;
    int gameSpeed = 8;
    int fpsCap = 60;

    int sX = cset.fWidth * fontScale;
    int sY = cset.fHeight * fontScale;

    SetTargetFPS(fpsCap);

    int columns = (int)(((GetScreenWidth() / cset.fWidth) / fontScale) + 0.5);
    int rows = (int)(((GetScreenHeight() / cset.fHeight)) + 0.5);

    
    applePos.x = (std::rand() % columns) + 1;
    applePos.y = (std::rand() % rows) + 1;

    // Main game loop
    while (!WindowShouldClose())    
    {
        
        frameCounter++;
        //  !!!!!!! FULLSCREEN IS BUGGED, TURNED OFF FOR TIME BEING !!!!!!!!!!
        if (IsKeyPressed(KEY_F11))
        {
            // see what display we are on right now
            int display = GetCurrentMonitor();

            // toggle the state
            //ToggleFullscreen();
            

            if (!IsWindowFullscreen())
            {
                // if we are full screen, then go back to the windowed size
                //SetWindowSize(screenWidth, screenHeight);
                //fontScale /= 2;
            }
            else
            {
                // if we are not full screen, set the window size to match the monitor we are on
                //SetWindowSize(GetMonitorWidth(display), GetMonitorHeight(display));
                //fontScale *= 2;
            }
            columns = (int)(((GetScreenWidth() / cset.fWidth) / fontScale) + 0.5);
            rows = (int)(((GetScreenHeight() / cset.fHeight)) + 0.5);

        }
        

        if (IsKeyPressed(KEY_UP)) { pX = 0; pY = -1; }
        else if (IsKeyPressed(KEY_DOWN)) { pX = 0; pY = 1; }
        else if (IsKeyPressed(KEY_LEFT)) { pX = -1; pY = 0; }
        else if (IsKeyPressed(KEY_RIGHT)) { pX = 1; pY = 0; }



        BeginDrawing();
        ClearBackground(BLACK);

        
        
        
        if (frameCounter >= (fpsCap/gameSpeed)) {
            
            frameCounter = 0;
            std::cout << applePos.x << " " << applePos.y << "\n";
            
            if (applePos.x == 0) {
                applePos.x += 8;
            }
            if (applePos.y == 0) {
                applePos.y += 8;
            }
            
            

            sX += pX * cset.fWidth * fontScale;
            sY += pY * cset.fHeight * fontScale;
            Vector2 nsnakepos = { sX, sY };
            history.push_back(nsnakepos);
            if (history.size() > snakeParts.size()) 
            {
                history.erase(history.begin());
            }
            for (int x = 0; x < snakeParts.size(); x++)
            {
                hisRev = history;
                std::reverse(hisRev.begin(), hisRev.end());
                snakeParts[x].x = hisRev[x].x;
                snakeParts[x].y = hisRev[x].y;
            }
            


            if (sX == applePos.x * cset.fWidth * fontScale && sY == applePos.y * cset.fHeight * fontScale) {
                
                score += 1;
                applePos.x = (std::rand() % columns) - 1;
                applePos.y = (std::rand() % rows) - 1;
                
                

                gameSpeed += 1;
                
                snakeParts.push_back(nsnakepos);
                
            }

            if (sX == 0 || sX == (columns-1) * cset.fWidth * fontScale || sY == 0 || sY == (rows-1) * cset.fHeight * fontScale)
            {
                gameSpeed = 0;
                insertStr("Game Over", columns / 4 * cset.fWidth * fontScale, rows / 4 * cset.fHeight * fontScale, cset, fontScale, WHITE, BLACK);
            }
            
             for (int x = 1; x < snakeParts.size(); x++) {
                if (sX == snakeParts[x].x && sY == snakeParts[x].y) {
                    if (x == snakeParts.size() - 1) {

                    }
                    else {
                        gameSpeed = 0;
                        insertStr("Game Over", columns / 4 * cset.fWidth * fontScale, rows / 4 * cset.fHeight * fontScale, cset, fontScale, WHITE, BLACK);
                

                    }
                }
             } 
        }
        for (int y = 0; y < rows; y++)
        {
            if (y == 0 || y == rows - 1)
            {
                for (int x = 0; x < columns; x++) {

                    insertStr("#", x * cset.fWidth, y * cset.fHeight, cset, fontScale);
                }
            }
            else {
                insertStr("#", 0, y * cset.fHeight, cset, fontScale);
                insertStr("#", (columns - 1) * cset.fWidth, y * cset.fHeight, cset, fontScale);
            }
        }
        insertStr("@", sX, sY, cset, fontScale);
        for (int i = 0; i < snakeParts.size(); i++)
        {
            insertStr("@", snakeParts[i].x, snakeParts[i].y, cset, fontScale);
        }
        insertStr("*", applePos.x * cset.fWidth * fontScale, applePos.y * cset.fHeight * fontScale, cset, fontScale, BLACK, RED);
        insertStr("Score: " + std::to_string(score), 0, 0, cset, fontScale, WHITE, BLACK);

        EndDrawing();
        
    }
    UnloadTexture(cset.font);
    CloseWindow(); 


    return 0;
}