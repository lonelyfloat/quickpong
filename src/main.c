#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    float ballSpeed = 100;
    float paddleSpeed = 200;
    float acceleration = 1.5;

    Vector2 ballPos = {screenWidth/2., screenHeight/2.};
    Vector2 ballVel = {-ballSpeed, -ballSpeed};
    float ballRadius = 5;
    Rectangle playerPaddle = {100, screenHeight/2. - 50, 25, 100};
    Rectangle opponentPaddle = {700, screenHeight/2. - 50, 25, 100};
    float opponentVel = 0;

    int score = 0;

    InitWindow(screenWidth, screenHeight, "speedrun pong");

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {    // Detect window close button or ESC key
        // Update
        //----------------------------------------------------------------------------------

        if (ballPos.y < 0 || ballPos.y > screenHeight) {
            ballVel.y = -ballVel.y;
        }

        if (ballPos.x > screenWidth) {
            ballVel.x = -ballVel.x;
        }
        
        if(ballPos.x < 0) {
            score = 0;
            ballPos = (Vector2){screenWidth/2., screenHeight/2.};
            ballVel = (Vector2){-ballSpeed, -ballSpeed};
            paddleSpeed = 200;
            ballSpeed = 100;
        }

        if (CheckCollisionCircleRec(ballPos, ballRadius, playerPaddle) ) {
           ballVel.x = -ballVel.x;
           ballSpeed += 5;
           paddleSpeed += 10;
           ++score;
        }
        if (CheckCollisionCircleRec(ballPos, ballRadius, opponentPaddle) ) {
           ballSpeed += 5;
           ballVel.x = -ballVel.x;
           paddleSpeed += 10;
           ++score;
        }
        
        // TODO: Fix these they don't work how i want
        if (ballPos.x > screenWidth/2.) { 
            opponentVel += Clamp(ballPos.y - opponentPaddle.y, -paddleSpeed, paddleSpeed) * acceleration; 
            opponentVel = Clamp(opponentVel, -paddleSpeed, paddleSpeed); 
        }
        else {
            opponentVel += Clamp(screenHeight/2. - 50 - opponentPaddle.y, -paddleSpeed, paddleSpeed) * acceleration; 
            opponentVel = Clamp(opponentVel, -paddleSpeed, paddleSpeed); 
        }

        
        opponentPaddle.y += opponentVel * GetFrameTime();
        playerPaddle.y += ( (IsKeyDown(KEY_S)) - (IsKeyDown(KEY_W)) ) * paddleSpeed * GetFrameTime();
        ballPos = Vector2Add (ballPos, Vector2Multiply(Vector2Normalize(ballVel), (Vector2){ballSpeed * GetFrameTime(), ballSpeed * GetFrameTime()} ) );
        opponentPaddle.y = Clamp(opponentPaddle.y, 0, screenHeight-100);
        playerPaddle.y = Clamp(playerPaddle.y, 0, screenHeight-100); 
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);
           
            DrawText(TextFormat("%d", score), screenWidth/2, 10, 20, WHITE);
            DrawRectangleRec(playerPaddle, WHITE);
            DrawRectangleRec(opponentPaddle, WHITE);
            DrawCircleV(ballPos, ballRadius, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
