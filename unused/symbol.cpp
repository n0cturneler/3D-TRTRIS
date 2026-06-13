#include <raylib.h>
#include <vector>

class peaceSymbol
{
public:
    peaceSymbol() = default;

    void drawPiece()
    {
        for (Vector3& pos : m_array)
        {
            DrawCube(pos, m_size.x, m_size.y, m_size.z, RED);
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
    Vector3 m_pos3{4.0f, 2.0f, 0.0f};
    Vector3 m_pos4{4.0f, 2.0f, 2.0f};
    Vector3 m_pos5{4.0f, 2.0f, 4.0f};

    Vector3 m_pos6{-2.0f, 2.0f, 0.0f};
    Vector3 m_pos7{-4.0f, 2.0f, 0.0f};
    Vector3 m_pos8{-4.0f, 2.0f, -2.0f};
    Vector3 m_pos9{-4.0f, 2.0f, -4.0f};

    Vector3 m_pos10{0.0f, 2.0f, 2.0f};
    Vector3 m_pos11{0.0f, 2.0f, 4.0f};
    Vector3 m_pos12{-2.0f, 2.0f, 4.0f};
    Vector3 m_pos13{-4.0f, 2.0f, 4.0f};

    Vector3 m_pos14{0.0f, 2.0f, -2.0f};
    Vector3 m_pos15{0.0f, 2.0f, -4.0f};
    Vector3 m_pos16{2.0f, 2.0f, -4.0f};
    Vector3 m_pos17{4.0f, 2.0f, -4.0f};

    Vector3 m_size{2.0f, 2.0f, 2.0f};

    std::vector<Vector3> m_array = {m_pos1, m_pos2, m_pos3, m_pos4, m_pos5, m_pos6, m_pos7, m_pos8, m_pos9, m_pos10, m_pos11, m_pos12,
        m_pos13, m_pos14, m_pos15, m_pos16, m_pos17};
};
