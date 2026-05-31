#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif 

#include <raylib.h>
#include <raymath.h>

#include <iostream> 
#include <vector>

class t_piece
{
public:
    t_piece() = default;

    void drawPiece() 
    {
        for (Vector3& pos : m_array)
        {
            DrawCube(pos, m_size.x, m_size.y, m_size.z, PURPLE);
            DrawCubeWires(pos, m_size.x, m_size.y, m_size.z, BLACK);
        }
    }

    void movePiece(float moveX, float moveY, float moveZ)
    {
        for (Vector3& pos : m_array)
        {
            pos.x += moveX;
            pos.y += moveY;
            pos.z += moveZ;
        }
    }

    void setPosition(float moveX, float moveY, float moveZ)
    {
        for (Vector3& pos : m_array)
        {
            pos = {moveX, moveY, moveZ};
        }
    }

    Vector3 position() const { return m_array[0]; }

private:
    Vector3 m_pos1{0.0f, 2.0f, 0.0f};
    Vector3 m_pos2{2.0f, 2.0f, 0.0f};
    Vector3 m_pos3{-2.0f, 2.0f, 0.0f};
    Vector3 m_pos4{0.0f, 2.0f, 2.0f};

    Vector3 m_size{2.0f, 2.0f, 2.0f};

    std::vector<Vector3> m_array = {m_pos1, m_pos2, m_pos3, m_pos4};
};

int main()
{
    const int currentMonitor = GetCurrentMonitor();
    const int screenWidth {GetMonitorWidth(currentMonitor)};
    const int screenHeight {GetMonitorHeight(currentMonitor)};

    SetConfigFlags(FLAG_MSAA_4X_HINT);
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    // SetConfigFlags(FLAG_FULLSCREEN_MODE);

    InitWindow(screenWidth, screenHeight, "3DTRTRIS");
    MaximizeWindow();

    SetTargetFPS(120);

    Camera3D camera{};
    camera.position = {0.0f, 20.0f, 10.0f};
    camera.target = {0.0f, 0.0f, 0.0f};
    camera.up = {0.0f, 1.0f, 0.0f};

    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    t_piece Piece1{};

    while (!WindowShouldClose())
    {   
        float dt{GetFrameTime()};

        if (IsKeyDown(KEY_W)) Piece1.movePiece(0, 0, -5.5f * dt);
        if (IsKeyDown(KEY_S)) Piece1.movePiece(0, 0, 5.5f * dt);
        if (IsKeyDown(KEY_A)) Piece1.movePiece(-5.5f * dt, 0, 0);
        if (IsKeyDown(KEY_D)) Piece1.movePiece(5.5f * dt, 0, 0);

        Vector3 cameraTargetPos{Vector3Lerp(camera.target, Piece1.position(), 5.0f * dt)};
        camera.target += Vector3Subtract(cameraTargetPos, camera.target);

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        DrawGrid(10, 2.0f);

        Piece1.drawPiece();

        EndMode3D();

        DrawFPS(10, 10);

        EndDrawing();

    }

    CloseWindow();
}
