#include "Audio.h"
#include "AxisIndicator.h"
#include "DirectXCommon.h"
#include "GameScene.h"
#include "TitleScene.h"
#include "setumei.h"
#include "GameClear.h"
#include "ImGuiManager.h"
#include "PrimitiveDrawer.h"
#include "TextureManager.h"
#include "WinApp.h"

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	WinApp* win = nullptr;
	DirectXCommon* dxCommon = nullptr;
	// 汎用機能
	Input* input = nullptr;
	Audio* audio = nullptr;
	AxisIndicator* axisIndicator = nullptr;
	PrimitiveDrawer* primitiveDrawer = nullptr;
	GameScene* gameScene = nullptr;
	TitleScene* titleScene = nullptr;
	GameClear* gameClear = nullptr;
	setumei* Setumei = nullptr;

	// ゲームウィンドウの作成
	win = WinApp::GetInstance();
	win->CreateGameWindow();

	// DirectX初期化処理
	dxCommon = DirectXCommon::GetInstance();
	dxCommon->Initialize(win);

#pragma region 汎用機能初期化
	// ImGuiの初期化
	ImGuiManager* imguiManager = ImGuiManager::GetInstance();
	imguiManager->Initialize(win, dxCommon);

	// 入力の初期化
	input = Input::GetInstance();
	input->Initialize();

	// オーディオの初期化
	audio = Audio::GetInstance();
	audio->Initialize();

	// テクスチャマネージャの初期化
	TextureManager::GetInstance()->Initialize(dxCommon->GetDevice());
	TextureManager::Load("white1x1.png");

	// スプライト静的初期化
	Sprite::StaticInitialize(dxCommon->GetDevice(), WinApp::kWindowWidth, WinApp::kWindowHeight);

	// 3Dモデル静的初期化
	Model::StaticInitialize();

	// 軸方向表示初期化
	axisIndicator = AxisIndicator::GetInstance();
	axisIndicator->Initialize();

	primitiveDrawer = PrimitiveDrawer::GetInstance();
	primitiveDrawer->Initialize();
#pragma endregion

	// ゲームシーンの初期化
	gameScene = new GameScene();
	gameScene->Initialize();

	titleScene = new TitleScene();
	titleScene->Initialize();

	gameClear = new GameClear();
	gameClear->Initialize();

	Setumei = new setumei();
	Setumei->Initialize();

	SceneType sceneNo = SceneType::kTitle;

	// メインループ
	while (true) {
		// メッセージ処理
		if (win->ProcessMessage()) {
			break;
		}

		// ImGui受付開始
		imguiManager->Begin();
		// 入力関連の毎フレーム処理
		input->Update();
		// ゲームシーンの毎フレーム処理
		//gameScene->Update();
		// 軸表示の更新
		axisIndicator->Update();

		switch (sceneNo) {
		case SceneType::kTitle:

			titleScene->Update();

			if (titleScene->IsSceneEnd()) {

				sceneNo = titleScene->NextScene();
			}
			break;

		case SceneType::kSetumei:

			Setumei->Update();
			if (Setumei->IsSceneEnd()) {

				sceneNo = Setumei->NextScene();
			}

			break;
		case SceneType::kGamePlay:

			gameScene->Update();

			if (gameScene->IsSceneEnd()) {

				sceneNo = gameScene->NextScene();
			}

			break;

		case SceneType::kGameClear:

			gameClear->Update();

			if (gameClear->IsSceneEnd()) {

				sceneNo = gameClear->NextScene();
			}

			break;
		}

		// ImGui受付終了
		imguiManager->End();

		// 描画開始
		dxCommon->PreDraw();
		// ゲームシーンの描画
		//gameScene->Draw();

		switch (sceneNo) {
		case SceneType::kTitle:
			titleScene->Draw();
			break;
		case SceneType::kSetumei:
			Setumei->Draw();
			break;
		case SceneType::kGamePlay:
			gameScene->Draw();
			break;
		case SceneType::kGameClear:
			gameClear->Draw();
			break;
		}

		// 軸表示の描画
		axisIndicator->Draw();
		// プリミティブ描画のリセット
		primitiveDrawer->Reset();
		// ImGui描画
		imguiManager->Draw();
		// 描画終了
		dxCommon->PostDraw();
	}

	delete titleScene;
	delete gameClear;
	delete Setumei;

	// 各種解放
	SafeDelete(gameScene);
	audio->Finalize();
	// ImGui解放
	imguiManager->Finalize();

	// ゲームウィンドウの破棄
	win->TerminateGameWindow();

	return 0;
}