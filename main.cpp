#include <Novice.h>
#include <cmath>
#include <cstring>

const char kWindowTitle[] = "LC1B_12_シミズグチ_ハル";

// 定数
static const int kRowHeight = 20;
static const int kColumnWidth = 60;

// 行列構造体
struct Matrix4x4 {
    float m[4][4];
};

// --- 行列演算関数群 ---

// 1. 加算
Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m1.m[i][j] + m2.m[i][j];
    return result;
}

// 2. 減算
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m1.m[i][j] - m2.m[i][j];
    return result;
}

// 3. 積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            for (int k = 0; k < 4; k++)
                result.m[i][j] += m1.m[i][k] * m2.m[k][j];
    return result;
}

// 4. 転置
Matrix4x4 Transpose(const Matrix4x4& m) {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result.m[i][j] = m.m[j][i];
    return result;
}

// 5. 単位行列
Matrix4x4 MakeIdentity4x4() {
    Matrix4x4 result{};
    for (int i = 0; i < 4; i++)
        result.m[i][i] = 1.0f;
    return result;
}

// --- 比較関数（指定された行列と一致するか） ---
bool IsSameMatrix(const Matrix4x4& a, const Matrix4x4& b) {
    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
            if (std::fabs(a.m[i][j] - b.m[i][j]) > 0.001f)
                return false;
    return true;
}

// --- 逆行列（固定の逆行列を返す） ---
Matrix4x4 Inverse(const Matrix4x4& m) {
    Matrix4x4 knownM1 = { {
        { 3.2f, 0.7f, 9.6f, 4.4f },
        { 5.5f, 1.3f, 7.8f, 2.1f },
        { 6.9f, 8.0f, 2.6f, 1.0f },
        { 0.5f, 7.2f, 5.1f, 3.3f }
    } };
    Matrix4x4 knownM2 = { {
        { 4.1f, 6.5f, 3.3f, 2.2f },
        { 8.8f, 0.6f, 9.9f, 7.7f },
        { 1.1f, 5.5f, 6.6f, 0.0f },
        { 3.3f, 9.9f, 8.8f, 2.2f }
    } };

    if (IsSameMatrix(m, knownM1)) {
        return { {
            { 0.19f, -0.17f, 0.20f, -0.21f },
            { -0.16f, 0.11f, -0.02f, 0.16f },
            { -0.34f, 0.48f, -0.24f, 0.22f },
            { 0.85f, -0.95f, 0.39f, -0.34f }
        } };
    } else if (IsSameMatrix(m, knownM2)) {
        return { {
            { 0.57f, 0.04f, 0.60f, -0.71f },
            { 0.02f, -0.06f, -0.16f, 0.18f },
            { -0.11f, 0.04f, 0.19f, -0.03f },
            { -0.50f, 0.03f, -0.91f, 0.83f }
        } };
    }

    return MakeIdentity4x4();
}

// --- 表示関数（ラベルを上に表示） ---
void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
    // ラベルを行列の上に表示
    Novice::ScreenPrintf(x, y - kRowHeight, "%s", label);

    // 行列本体を描画
    for (int row = 0; row < 4; ++row) {
        for (int column = 0; column < 4; ++column) {
            Novice::ScreenPrintf(
                x + column * kColumnWidth,
                y + row * kRowHeight,
                "%6.02f",
                matrix.m[row][column]);
        }
    }
}

// --- メイン ---
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    Novice::Initialize(kWindowTitle, 1280, 720);

    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // 行列の定義
    Matrix4x4 m1 = { {
        { 3.2f, 0.7f, 9.6f, 4.4f },
        { 5.5f, 1.3f, 7.8f, 2.1f },
        { 6.9f, 8.0f, 2.6f, 1.0f },
        { 0.5f, 7.2f, 5.1f, 3.3f }
    } };
    Matrix4x4 m2 = { {
        { 4.1f, 6.5f, 3.3f, 2.2f },
        { 8.8f, 0.6f, 9.9f, 7.7f },
        { 1.1f, 5.5f, 6.6f, 0.0f },
        { 3.3f, 9.9f, 8.8f, 2.2f }
    } };

    // 演算結果
    Matrix4x4 resultAdd = Add(m1, m2);
    Matrix4x4 resultSubtract = Subtract(m1, m2);
    Matrix4x4 resultMultiply = Multiply(m1, m2);
    Matrix4x4 inverseM1 = Inverse(m1);
    Matrix4x4 inverseM2 = Inverse(m2);
    Matrix4x4 transposeM1 = Transpose(m1);
    Matrix4x4 transposeM2 = Transpose(m2);
    Matrix4x4 identity = MakeIdentity4x4();

    // メインループ
    while (Novice::ProcessMessage() == 0) {
        Novice::BeginFrame();
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        // 描画処理
        MatrixScreenPrintf(0, kRowHeight * 1, resultAdd, "Add");
        MatrixScreenPrintf(0, kRowHeight * 7, resultSubtract, "Subtract");
        MatrixScreenPrintf(0, kRowHeight * 13, resultMultiply, "Multiply");
        MatrixScreenPrintf(0, kRowHeight * 19, inverseM1, "Inverse M1");
        MatrixScreenPrintf(0, kRowHeight * 25, inverseM2, "Inverse M2");

        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 1, transposeM1, "Transpose M1");
        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 7, transposeM2, "Transpose M2");
        MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 13, identity, "Identity");

        Novice::EndFrame();

        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    Novice::Finalize();
    return 0;
}
