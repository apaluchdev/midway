#include "raylib.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Top-Down Game with Absolute Mouse Position");

    Camera2D camera = { 0 };
    camera.target = (Vector2){ 0, 0 };
    camera.offset = (Vector2){ screenWidth / 2.0f, screenHeight / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    Rectangle player = { 0, 0, 50, 50 };
    const int worldSize = 1000;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Update camera zoom based on mouse wheel
        float wheelMove = GetMouseWheelMove();
        camera.zoom += wheelMove * 0.1f;
        if (camera.zoom < 0.1f) camera.zoom = 0.1f;
        if (camera.zoom > 3.0f) camera.zoom = 3.0f;

        // Update player position with WASD
        if (IsKeyDown(KEY_W)) player.y -= 200 * GetFrameTime();
        if (IsKeyDown(KEY_S)) player.y += 200 * GetFrameTime();
        if (IsKeyDown(KEY_A)) player.x -= 200 * GetFrameTime();
        if (IsKeyDown(KEY_D)) player.x += 200 * GetFrameTime();

        // Set camera target to follow player
        camera.target = (Vector2){ player.x + player.width / 2, player.y + player.height / 2 };

        // Get mouse position in world coordinates
        Vector2 mouseScreenPos = GetMousePosition();
        Vector2 mouseWorldPos = GetScreenToWorld2D(mouseScreenPos, camera);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Begin camera mode
        BeginMode2D(camera);

        // Draw game world
        DrawRectangle(-worldSize / 2, -worldSize / 2, worldSize, worldSize, LIGHTGRAY);
        DrawRectangleRec(player, RED);  // Draw player

        // Draw a circle at the mouse world position
        DrawCircleV(mouseWorldPos, 5, BLUE);

        EndMode2D();

        // UI Overlay
        DrawText("Use W/A/S/D to move, mouse wheel to zoom", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Mouse World Position: [%.2f, %.2f]", mouseWorldPos.x, mouseWorldPos.y), 10, 40, 20, DARKGRAY);
        DrawText(TextFormat("Zoom: %.2f", camera.zoom), 10, 70, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
