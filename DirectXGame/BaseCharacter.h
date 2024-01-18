﻿#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <list>
#include "Windows.h"

#include <cassert>
#include "Input.h"
class BaseCharacter {
protected:
	//モデルデータ配列
	std::vector<Model*> models_;
	//ワールド変換データ
	WorldTransform worldTransform_;

	//メンバ変数
public:
	virtual void Initalize(const std::vector<Model*>& models);
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="models_">モデルデータ配列</param>
	    virtual void Initialize(const std::vector<Model*>& models);

	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	virtual void Draw(ViewProjection& viewProjection);

	/// <summary>
	/// 描画
	/// </summary>
	///<param name="viewProjection">ビュープロジェクション(参照渡し)</param>
	    virtual void Draw(const ViewProjection& viewProjection);
	/// <summary>
	/// ワールド変換データを取得
	/// </summary>
	/// <returns>
	///	<returns>ワールド変換データ</returns>
	const WorldTransform& GetWorldTransform() { return worldTransform_; }
	

protected:
	WorldTransform worldTransform_;

	std::vector<Model*> models_;

	



};
