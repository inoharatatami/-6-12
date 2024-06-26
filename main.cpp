#include <Novice.h>

const char kWindowTitle[] = "LE2D_09_スガワラ_オオスケ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    // プレイヤーの位置と速度
    int playerPosX = 0;
    int playerPosY = 500; // 初期位置を少し下げる
    int scrollX = 0;

    int ksk = 8;

    int dashMultiplier = 1;
    const int maxDash = 3;
    const int dashInterval = 30;
    int frame = 0;

    // ジャンプ関連の変数
    const int jumpStrength = 20;
    int velocityY = 0;
    bool isJumping = false;
    const int gravity = 1;

    // ウィンドウの×ボタンが押されるまでループ
    while (Novice::ProcessMessage() == 0) {
        // フレームの開始
        Novice::BeginFrame();

        // キー入力を受け取る
        memcpy(preKeys, keys, 256);
        Novice::GetHitKeyStateAll(keys);

        ///
        /// ↓更新処理ここから
        ///

        if (keys[DIK_D] != 0) {
            playerPosX += ksk * dashMultiplier;
            if (playerPosX > 5088) {
                playerPosX = 5088;
            }
        }

        if (keys[DIK_A] != 0) {
            playerPosX -= ksk * dashMultiplier;
        }

        scrollX = playerPosX - 768;

        if (scrollX < 0) {
            scrollX = 0;
        }

        if (scrollX > 3840) {
            scrollX = 3840;
        }

        if (keys[DIK_LSHIFT] != 0) {
            frame++;
            if (frame >= dashInterval) {
                if (dashMultiplier < maxDash) {
                    dashMultiplier++;
                }
                frame = 0;
            }
        }
        else {
            dashMultiplier = 1;
            frame = 0;
        }

        // ジャンプ処理
        if (keys[DIK_SPACE] != 0 && !isJumping) {
            velocityY = -jumpStrength;
            isJumping = true;
        }

        // 重力の適用
        if (isJumping) {
            playerPosY += velocityY;
            velocityY += gravity;

            // 地面に着地した場合の処理
            if (playerPosY >= 500) {
                playerPosY = 500;
                velocityY = 0;
                isJumping = false;
            }
        }

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        int screenY = playerPosY;
        screenY -= 560;
        screenY *= -1;

        Novice::DrawLine(800, 0, 800, 720, RED);

        Novice::DrawBox(playerPosX - scrollX, playerPosY, 32, 32, 0.0f, BLUE, kFillModeSolid);

        Novice::ScreenPrintf(50, 125, "dashMultiplier: %d", dashMultiplier);
        
        Novice::ScreenPrintf(50, 175, "player.pos.x: %d", playerPosX);
        Novice::ScreenPrintf(50, 200, "player.pos.y: %d", playerPosY);

        ///
        /// ↑描画処理ここまで
        ///

        // フレームの終了
        Novice::EndFrame();

        // ESCキーが押されたらループを抜ける
        if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
            break;
        }
    }

    // ライブラリの終了
    Novice::Finalize();
    return 0;
}
