#include <Novice.h>

const char kWindowTitle[] = "LE2D_09_スガワラ_オオスケ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	int haikei[4] = {};

	int playerPosX = 0;
	int scrollX = 0;

	int posY = 0;

	int ksk = 8;

	haikei[0] = Novice::LoadTexture("./Resources/images/bg1.png");
	haikei[1] = Novice::LoadTexture("./Resources/images/bg2.png");
	haikei[2] = Novice::LoadTexture("./Resources/images/bg3.png");
	haikei[3] = Novice::LoadTexture("./Resources/images/bg4.png");



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
			playerPosX += ksk;
			if (playerPosX > 5088) {
				playerPosX = 5088;
			}
		}

		if (keys[DIK_A] != 0) {
			playerPosX -= ksk;
		}

		scrollX = playerPosX - 768;

		if (scrollX < 0) {
			scrollX = 0;
		}

		if (scrollX > 3840) {
			scrollX = 3840;
		}

		if(keys[DIK_LSHIFT] != 0){
			if (ksk <= 8) {
				ksk += 1;
			}

		}
		
		if (keys[DIK_LSHIFT] == 0 && ksk == 8) {
			if(ksk > 4){
				ksk -= 1;
			}
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		int screenY = posY;
		screenY -= 560;
		screenY *= -1;

		Novice::DrawSprite(0 - scrollX, 0, haikei[0], 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(1280 - scrollX, 0, haikei[1], 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(2560 - scrollX, 0, haikei[2], 1, 1, 0.0f, WHITE);
		Novice::DrawSprite(3840 - scrollX, 0, haikei[3], 1, 1, 0.0f, WHITE);

		Novice::DrawLine(800, 0, 800, 720, RED);

		Novice::DrawBox(playerPosX - scrollX, screenY, 32, 32, 0.0f, BLUE, kFillModeSolid);

		Novice::ScreenPrintf(50, 50, "WASD: Player");
		Novice::ScreenPrintf(50, 75, "ArrowKeys: Move Scroll Start Line");
		Novice::ScreenPrintf(50, 125, "Scroll X (on World Axis): %d", scrollX);
		Novice::ScreenPrintf(50, 150, "Scroll Start Line(on Screen Axis): 800");
		Novice::ScreenPrintf(50, 175, "player.pos.x: %d", playerPosX);
		Novice::ScreenPrintf(50, 200, "ksk: %d", ksk);
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
