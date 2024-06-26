/**
 * @file Player.h
 * @brief ゲームオブジェクト プレイヤー
 * @author Asuma Syota
 * @date 2023/4
 */

#pragma once
#include "DirectXMath.h"
#include "FbxObject3D.h"
#include "PlayerBullet.h"
#include "JSONLoader.h"
#include "Sprite.h"
#include "LockOn.h"
#include "ElecParticle.h"
#include "EnemyBulletParticle.h"

//クラスの前方宣言
class PlayerState;
class Player
{
private:	//エイリアス
	//Microsoft::WRL::を省略
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public:

	enum Form	//プレイヤーのフォルム
	{
		Fire,	//炎
		Elec,	//電気
	};

	//メンバ関数
public:

	//インストラクタ コンストラクタ
	Player();
	~Player();

	//静的メンバ関数

	/// <summary>
	///カメラセット
	/// </summary>
	static void SetCamera(Camera* camera) { Player::camera = camera; }

	/// <summary>
	///キーマネージャーセット
	/// </summary>
	static void SetKeyManager(KeyManager* keyManager) { Player::keyManager = keyManager; }

	/// <summary>
	///ロックオンセット
	/// </summary>
	static void SetLockOn(LockOn* lockOn) { Player::lockOn = lockOn; }

	/// <summary>
	///初期化
	/// </summary>
	void Initialize();

	/// <summary>
	///更新
	/// </summary>
	void Update();

	/// <summary>
	///更新 コライダー
	/// </summary>
	void UpdateCollider();

	/// <summary>
	///描画
	/// </summary>
	void Draw(ID3D12GraphicsCommandList* cmdList);
	
	/// <summary>
	///ライト視点描画
	/// </summary>
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///パーティクル描画
	/// </summary>
	void DrawParticle(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///スプライト描画
	/// </summary>
	void DrawSpriteGame(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///スプライト描画
	/// </summary>
	void DrawSpriteTutorial(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///更新 フォルム
	/// </summary>
	void UpdateForm();

	/// <summary>
	///更新 ステート
	/// </summary>
	void UpdateState();

	/// <summary>
	///座標セット
	/// </summary>
	void SetPosition(XMFLOAT3 pos) {};

	/// <summary>
	///オブジェクトの当たり判定セット
	/// </summary>
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData);

	/// <summary>
	///敵の座標取得
	/// </summary>
	void SetEnemyPos(XMFLOAT3 position, XMFLOAT3 addPos) { enemyPos.emplace_back(position); enemyAddPos.emplace_back(addPos); }

	/// <summary>
	///プレイヤーの弾命中時
	/// </summary>
	void HitBullet1(int num);

	/// <summary>
	///敵の弾命中時
	/// </summary>
	void HitEnemy();

	/// <summary>
	///リセット
	/// </summary>
	void Reset();

	/// <summary>
	///タイトルシーンに移る際に呼び出す
	/// </summary>
	void SetTitle();

	/// <summary>
	///チュートリアルシーンに移る際に呼び出す
	/// </summary>
	void SetTutorial();

	/// <summary>
	///ゲームシーンに移る際に呼び出す
	/// </summary>
	void SetGameScene();

	/// <summary>
	///フェーズ移動に移る際に呼び出す
	/// </summary>
	void SetMovePhase();

	/// <summary>
	///クリアに移る際に呼び出す
	/// </summary>
	void SetClear();

	/// <summary>
	///チュートリアルのフェーズセット
	/// </summary>
	void SetTutorialFlag(int tutorialFlag) { this->tutorialFlag = tutorialFlag; }

	/// <summary>
	///座標取得
	/// </summary>
	XMFLOAT3 GetPosition();

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation0();

	/// <summary>
	///角度取得
	/// </summary>
	XMFLOAT3 GetRotation1();

	/// <summary>
	///スケール取得
	/// </summary>
	XMFLOAT3 GetScale();

	/// <summary>
	///コライダー取得 
	/// </summary>
	JSONLoader::ColliderData GetColliderData();

	/// <summary>
	///弾のコライダー取得
	/// </summary>
	JSONLoader::ColliderData GetBullet1ColliderData(int num);

	/// <summary>
	///弾のコライダー取得
	/// </summary>
	size_t GetBullet1Num();

	/// <summary>
	///プレイヤーが無敵状態か取得
	/// </summary>
	bool GetInvincibleFlag();

	/// <summary> 
	///死亡フラグ取得
	/// </summary>
	bool GetIsDead() { return isDead; }

	/// <summary>
	///死亡フラグ取得
	/// </summary>
	bool GetHitElec();

	/// <summary>
	///属性チェンジフラグ取得
	/// </summary>
	int GetFormChangeFlag() { return formChangeFlag; }

	/// <summary>
	///属性取得
	/// </summary>
	int GetPlayerForm() { return form; }

	// <summary>
	///HP取得
	/// </summary>
	int GetHP() { return (int)HP; };

	// <summary>
	///最大HP取得
	/// </summary>
	int GetMaxHP() { return (int)MaxHP; };

	/// <summary>
	///プレイヤーの状態変更
	/// </summary>
	void ChangeState(PlayerState* playerState);

	//静的メンバ変数
private:
	//カメラ
	static Camera* camera;
	//キーマネージャー
	static KeyManager* keyManager;
	//ロックオン
	static LockOn* lockOn;

	//メンバ変数
private:

	//プレイヤー
	PlayerState* playerState = nullptr;

	//チュートリアルのフェーズ
	int tutorialFlag = 0;

	float debugPos[2] = {320.0f,120.0f};

	//ステータス関連
	//プレイヤーのHP
	float MaxHP = 5;
	float HP = MaxHP;

	//フォルム
	Form form = Fire;
	Form preForm = Fire;
	//フォルムチェンジに使うタイマー
	int formTimer = 0;
	int formMaxTime = 120;
	//フォルムチェンジに使うフラグ
	bool formChangeFlag = false;

	//走ってるアニメーションに無理やりするフラグ
	bool runAnimationFlag = false;

	//敵の座標
	std::vector<XMFLOAT3>enemyPos;
	std::vector<XMFLOAT3>enemyAddPos;

	//死亡フラグ
	bool isDead = false;

	//フェーズ移動中のフラグ
	bool movePhaseFlag = false;

	//デバッグ用
	float debugTimer[1] = { 0 };
	float debugNum[1] = { 0 };
};

class PlayerState
{
public:	//メンバ関数

	//コンストラクタ デストラクタ
	PlayerState() {};
	~PlayerState() {};

	//仮想関数
	//各ステート初期化
	virtual void InitializeState() = 0;
	//攻撃処理
	virtual void UpdateAttack() {};
	//移動処理
	virtual void Move();
	//ステートの変更
	virtual void UpdateState(Player* player) = 0;


	//通常関数
	//初期化
	void Initialize();
	//終了時処理
	void Finalize();
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList);
	//ライト目線描画
	void DrawLightView(ID3D12GraphicsCommandList* cmdList);
	//オブジェクトの更新
	void UpdateObject();
	//パーティクル描画
	void DrawParticle(ID3D12GraphicsCommandList* cmdList);
	//更新
	void Update();
	//判定更新
	void UpdateCollider();
	//ダウン状態更新
	void UpdateDown();
	//壁との当たり判定処理
	void UpdateHitWall(JSONLoader::ColliderData objectColliderData);
	//柱との当たり判定処理
	void UpdateHitPiller(JSONLoader::ColliderData objectColliderData);
	//オブジェクトの当たり判定セット
	void SetObjectCollider(std::vector<JSONLoader::ColliderData> colliderData) { objectColliderData = colliderData; };

	//座標取得
	XMFLOAT3 GetPosition() { return position; }
	//角度取得
	XMFLOAT3 GetRotation0() { return rotation0; }
	//角度取得
	XMFLOAT3 GetRotation1() { return rotation1; }
	//スケール取得
	XMFLOAT3 GetScale() { return scale; }
	//プレイヤーの弾命中時
	void HitBullet1(int num) { bullet->SetHitFlag(num); };
	//コライダー取得
	JSONLoader::ColliderData GetColliderData() { return colliderData; }
	//弾のコライダー取得
	JSONLoader::ColliderData GetBullet1ColliderData(int num) { return bullet->GetColliderData(num); }
	//弾のコライダー取得
	size_t GetBullet1Num() { return  bullet->GetBulletNum(); }
	//プレイヤーが無敵状態か取得
	bool GetInvincibleFlag() { return invincibleFlag; }
	//ヒットフラグ取得
	bool GetHitElec() { return hitElecFlag; }
	//雷攻撃中のフラグ
	bool GetElecAttackFlag() { return elecAttackFlag; }
	//リセット
	void Reset();
	//タイトルシーンに移る際に呼び出す
	void SetTitle(Player* player);
	//チュートリアルシーンに移る際に呼び出す
	void SetTutorial();
	//ゲームシーンに移る際に呼び出す
	void SetGameScene();
	//フェーズ移動に移る際に呼び出す
	void SetMovePhase(Player* player);
	//クリアに移る際に呼び出す
	void SetClear(Player* player);
	//フェーズ移動のフラグ
	void SetMovePhaseFlag(bool flag) { movePhaseFlag = flag; }

	//プレイヤー本体からセットする系
	void SetLockOn(bool lockOnFlag, XMFLOAT3 lockOnPos);
	void SetKeyManager(KeyManager* keyManager) { this->keyManager = keyManager; };
	void SetPlayerForm(Player::Form form) { this->form = form; }
	void HitEnemy();
	void SetHP(int HP) { this->HP = HP; }

protected:	//静的メンバ変数

	//モデル
	static FbxModel* modelWait;
	static FbxModel* modelRun;
	static FbxModel* modelAttack1;
	static FbxModel* modelAttack2;
	static FbxModel* modelAttack3;
	static FbxModel* modelDown;

	//オブジェクト
	static FbxObject3D* object;
	//コライダーデータ
	static JSONLoader::ColliderData colliderData;
	//シェーダのデータ
	static JSONLoader::TextureData textureData;

	//平行移動
	static XMFLOAT3 position;
	//回転
	static XMFLOAT3 rotation0;
	static XMFLOAT3 rotation1;
	//サイズ
	static XMFLOAT3 scale;
	//弾 炎
	static PlayerBullet* bullet;
	//雷パーティクル
	static ElecParticle* elecParticle1;
	//雷パーティクルに使うパーティクル 敵の弾のもので代用
	static EnemyBulletParticle* elecParticle2;
	//被ダメージ時の無敵時間
	static bool invincibleFlag;
	static float hitTimer;

protected:	//メンバ変数

	//キーマネージャー
	KeyManager* keyManager = nullptr;

	//HP
	int HP;

	//オブジェクトごとのタイマー
	int objectTimer = 0;
	//オブジェクトに時間の設定がある場合
	int objectTime = 0;
	//オブジェクトごとに時間の設定があるか
	bool objectTimeFlag = false;

	//雷を発生させる場所
	XMFLOAT3 addElecPos2;

	//ロックオン
	bool lockOnFlag = false;
	XMFLOAT3 lockOnPos = {0.0f,0.0f,0.0f};

	//フォルム
	Player::Form form;

	//回転の速度
	float rot0Speed = (float)PI * 1.5f / 180.0f;

	//移動スピード
	float posSpeed = 1.0f;

	//当たりフラグ
	bool hitFlag = false;
	bool hitElecFlag = false;

	//被ダメージアニメーションのフレーム数
	float frameDown = 138.0f;
	//進行ベクトル
	XMFLOAT3 posVelocity = { 0.0f,0.0f,0.0f };
	//角度ベクトル
	XMFLOAT3 rotVelocity = { 0.0f,0.0f,0.0f };

	//オブジェクトのコライダーデータ
	std::vector<JSONLoader::ColliderData> objectColliderData;
	//オブジェクト衝突時の押し戻し
	float knockBackSpeed = 0.001f;

	//シーン遷移に使う角度
	float addRot = 0.0f;
	float originalRot = 0.0f;

	//チュートリアルのフェーズ
	int tutorialFlag = 0;

	//フェーズ移動のフラグ
	bool movePhaseFlag = false;

	//雷攻撃中のフラグ ロックオンの更新に使用
	bool elecAttackFlag = false;

	//フェーズ移動の時の座標
	XMFLOAT3 movePhasePos = { 0.0f, 0.0f, -50.0f };
	//ゲームシーンに移る時の座標
	XMFLOAT3 gameScenePos = { 0.0f, 0.0f, -200.0f };
	//ゲームシーンに移る時の座標
	XMFLOAT3 clearPos = { 0.0f, 500.0f, 500.0f };

	//タイトルシーンの座標
	XMFLOAT3 titlePos = { 40.0f,0.0f,120.0f };
	//タイトルシーンの角度
	XMFLOAT3 titleRotation = { 0.0f,(float)PI,0.0f };
};