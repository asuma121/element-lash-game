/**
 * @file Plane.h
 * @brief ゲームオブジェクト 平面
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "FbxObject3D.h"
#include "JSONLoader.h"

class Plane
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;
	//メンバ関数
public://静的メンバ関数

	//コンストラクタ デストラクタ
	Plane() {};
	~Plane();

	/// <summary>
	///デバイスセット
	/// </summary>
	static void SetCamera(Camera* camera) { Plane::camera = camera; }

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///座標取得
	/// </summary>
	XMFLOAT3 GetPosition() { return position; }

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation() { return rotation; }

	/// <summary>
	///スケール取得
	/// </summary>
	XMFLOAT3 GetScale() { return scale; }

	//静的メンバ変数
private:
	//カメラ
	static Camera* camera;

	//メンバ変数
public:

	//オブジェクト
	FbxObject3D* object = nullptr;
	//モデル
	FbxModel* model = nullptr;

	//コライダーデータ
	JSONLoader::ColliderData colliderData;

	//座標
	XMFLOAT3 position = { 0.0f,0.0f,0.0f };
	//回転
	XMFLOAT3 rotation = { 0.0f,0.0f,0.0f };
	//サイズ
	XMFLOAT3 scale = { 100000.0f,100000.0f,1.0f };
};
