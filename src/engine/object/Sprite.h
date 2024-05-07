/**
 * @file Sprite.h
 * @brief スプライトのオブジェクト
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "d3dx12.h"
#include "DirectXMath.h"
#include "array"
#include "TextureManager.h"

class Sprite
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:	//サブクラス
	//定数バッファ
	struct ConstBuffMaterial
	{
		XMFLOAT4 color;
	};
	//定数バッファ2
	struct ConstBuffTransform
	{
		XMMATRIX mat;	//3D変換行列
	};
	//頂点データ用構造体
	struct Vertex
	{
		XMFLOAT3 pos;
		XMFLOAT2 uv;
	};

public:	//メンバ関数

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///更新
	/// </summary>
	void Update(XMFLOAT2 position,XMFLOAT2 scale);

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);

public:	//静的メンバ変数セッター

	/// <summary>
	///デバイスセット
	/// </summary>
	static void SetDevice(ID3D12Device* device) { Sprite::device = device; }

	/// <summary>
	///デバイスセット
	/// </summary>
	static void SetTextureManager(TextureManager* spriteManager) { Sprite::spriteManager = spriteManager; }

	/// <summary>
	///デバイスセット
	/// </summary>
	static void CreateGraphicsPipeLine();

public:	//セッター

	/// <summary>
	///アルファ値セット
	/// </summary>
	void SetAlpha(float alpha) { color.w = alpha; }

	/// <summary>
	///色セット
	/// </summary>
	void SetColor(XMFLOAT3 c) { color.x = c.x; color.y = c.y; color.z = c.z; }

	/// <summary>
	///テクスチャの番号をセット
	/// </summary>
	void SetTextureNum(int num) { textureNum = num; }

	/// <summary>
	///座標セット
	/// </summary>
	void SetPosition(XMFLOAT2 pos) { position = pos; }

	/// <summary>
	///角度セット
	/// </summary>
	void SetRotation(float rot) { rotation = rot; }

	/// <summary>
	///スケールセット
	/// </summary>
	void SetScale(XMFLOAT2 sca) { scale = sca; }

public:	//ゲッター

	/// <summary>
	///座標取得
	/// </summary>
	XMFLOAT2 GetPosition() { return position; }

	/// <summary>
	///角度取得
	/// </summary>
	float GetRotation() { return rotation; }

	/// <summary>
	///スケール取得
	/// </summary>
	XMFLOAT2 GetScale() { return scale; }

private:
	//デバイス
	static ID3D12Device* device;
	//スプライトマネージャー
	static TextureManager* spriteManager;
	//ルートシグネチャ
	static ComPtr<ID3D12RootSignature>rootsignature;
	//パイプラインステートオブジェクト
	static ComPtr<ID3D12PipelineState>pipelinestate;

private:	//メンバ変数
	//使用するテクスチャの番号
	int textureNum = 0;
	//頂点バッファビュー
	D3D12_VERTEX_BUFFER_VIEW vbView;
	//頂点データ
	Vertex vertices[6];
	Vertex* vertMap = nullptr;
	//定数バッファ マテリアル
	ComPtr<ID3D12Resource>constBuffMaterial;
	ConstBuffMaterial* constMapMaterial = nullptr;
	//定数バッファ 変形行列
	ComPtr<ID3D12Resource>constBuffTransform;
	ConstBuffTransform* constMapTransform = nullptr;
	//テクスチャの色
	XMFLOAT4 color = { 1,1,1,1 };

private:
	float rotation = 0;
	XMFLOAT2 position = { 0,0 };
	XMFLOAT2 scale = { 100.0f,100.0f };
};