#include "GameClear.h"

GameClear::GameClear() {}

GameClear::~GameClear() {

	delete spriteC_;
}

void GameClear::Initialize() {
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();

	textureHandleClear_ = TextureManager::Load("GC.png");
	spriteC_ = Sprite::Create(textureHandleClear_, {0, 0});
}

void GameClear::Update() {

	XINPUT_STATE joyState;
	XINPUT_STATE joyStatePre;

	if (isSceneEnd == false) {

		if (Input::GetInstance()->GetJoystickState(0, joyState)) {
			Input::GetInstance()->GetJoystickStatePrevious(0, joyStatePre);
			if (joyState.Gamepad.wButtons == XINPUT_GAMEPAD_B &&
			    joyStatePre.Gamepad.wButtons != XINPUT_GAMEPAD_B) {
				isSceneEnd = true;
			}
		}
	} 
	else 
	{
		isSceneEnd = false;
	}
}

void GameClear::Draw() {

	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

	Sprite::PreDraw(commandList);

	spriteC_->Draw();

	Sprite::PostDraw();

}