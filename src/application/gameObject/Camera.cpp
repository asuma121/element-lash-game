/**
 * @file Camera.cpp
 * @brief カメラ ゲームで使うビュー行列を管理
 * @author Asuma Syota
 * @date 2023/4
 */

#include "Camera.h"
#include "Math.h"
#include "mathOriginal.h"
#define PI 3.14159265359

Input* Camera::input = nullptr;
DXInput* Camera::dxInput = nullptr;

Camera* Camera::GetInstance()
{
	static Camera instance;
	return &instance;
}

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Initialize()
{
	//射影変換
	matProjection_ = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0f),			//上下画角45度
		(float)window_width / window_height,//アスペクト比(画面横幅/画面立幅)
		0.1f, 1000.0f						//前端、奥端
	);

	//行列計算
	matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
}


void Camera::Update()
{
	BillboardUpdate();

	//角度更新
	//視点から注視点のベクトル取得
	XMFLOAT3 vec = target_ - eye_;

	//XMFLOAT3 rot(0.0f, 0.0f, 0.0f);
	////正面向いてる時の角度
	//XMFLOAT3 oriRot = { 1.0f,0.0f,1.0f };
	/*rot.y = vec.x * PI / 2;*/
	/*rot.y = (vec.x * oriRot.x) + (vec.z * oriRot.z) / 
		(length(XMFLOAT2(vec.x, vec.z)) * length(XMFLOAT2(oriRot.x, oriRot.z))) * (PI / 2);
	rot.y *= (float(PI) / 90.0f);*/
	rotation = getVectorRotation(vec);

	//デバッグでないとき普通の射影変換
	if (debugFlag == false)
	{
		matView_ = XMMatrixLookAtLH(XMLoadFloat3(&eye_), XMLoadFloat3(&target_), XMLoadFloat3(&up_));
	}
	//デバッグのときの射影変換
	if (debugFlag == true)
	{
		matView_ = XMMatrixLookAtLH(XMLoadFloat3(&debugEye_), XMLoadFloat3(&debugTarget_), XMLoadFloat3(&debugUp_));
	}
}

void Camera::TitleUpdate(XMFLOAT3 playerPos, XMFLOAT3 playerRot, float timer)
{
	float distance = 60.0f;
	//シーン遷移タイマーが動いていない時
	if (timer < 119)
	{
		eye_.x = playerPos.x + (cos(-playerRot.y - (PI / 2)) * distance);
		eye_.y = playerPos.y + (cos(-playerRot.x + (PI * 15 / 40)) * distance);
		eye_.z = playerPos.z + (sin(-playerRot.y + (PI / 2)) * distance);
		originalPlayerPos = playerPos;
		originalPlayerRot = playerRot;
		target_ = { playerPos.x,5.0f,playerPos.z };
	}
	//シーン遷移タイマーが動いているとき
	if (timer > 120)
	{
		eye_.x = originalPlayerPos.x + (cos(-originalPlayerRot.y - (PI / 2)) * distance);
		eye_.y = originalPlayerPos.y + (cos(-originalPlayerRot.x + (PI * 15 / 40)) * distance);
		eye_.z = originalPlayerPos.z + (sin(-originalPlayerRot.y + (PI / 2)) * distance);
		target_ = { originalPlayerPos.x,5.0f,originalPlayerPos.z };
	}

}

void Camera::BillboardUpdate()
{
	XMFLOAT3 eye = eye_;
	XMFLOAT3 target = target_;
	XMFLOAT3 up = up_;
	//視点座標
	XMVECTOR eyePosition = XMLoadFloat3(&eye);
	//注視点座標
	XMVECTOR targetPosition = XMLoadFloat3(&target);
	//(仮の)上方向
	XMVECTOR upVector = XMLoadFloat3(&up);

	//カメラZ軸
	XMVECTOR cameraAxisZ = XMVectorSubtract(targetPosition, eyePosition);
	//0ベクトルだと向きが定まらないので除外
	assert(!XMVector3Equal(cameraAxisZ, XMVectorZero()));
	assert(!XMVector3IsInfinite(cameraAxisZ));
	assert(!XMVector3Equal(upVector, XMVectorZero()));
	assert(!XMVector3IsInfinite(upVector));
	//ベクトルを正規化
	cameraAxisZ = XMVector3Normalize(cameraAxisZ);

	//カメラのX軸(右方向)
	XMVECTOR cameraAxisX;
	//X軸は上方向→Z軸の外積で決まる
	cameraAxisX = XMVector3Cross(upVector, cameraAxisZ);
	//ベクトルを正規化
	cameraAxisX = XMVector3Normalize(cameraAxisX);

	//カメラのY軸
	XMVECTOR cameraAxisY;
	//Y軸はZ軸→X軸の外積で求まる
	cameraAxisY = XMVector3Cross(cameraAxisZ, cameraAxisX);
	/*cameraAxisY = XMVector3Normalize(cameraAxisY);*/

	//全方向ビルボード行列の計算
	//ビルボード行列
	matBillboard_.r[0] = cameraAxisX;
	matBillboard_.r[1] = cameraAxisY;
	matBillboard_.r[2] = cameraAxisZ;
	matBillboard_.r[3] = XMVectorSet(0, 0, 0, 1);
}

void Camera::DebugUpdate()
{
	//1フレームあたりの移動量
	float rot = (float)PI / 120.0f;

	//視点座標を変更
	if (input->PushKey(DIK_LEFT))
	{
		DebugChangeRot -= (float)rot;
	}
	if (input->PushKey(DIK_RIGHT))
	{
		DebugChangeRot += (float)rot;
	}
	if (input->PushKey(DIK_UP))
	{
		DebugChangeRot2 -= (float)rot;
	}
	if (input->PushKey(DIK_DOWN))
	{
		DebugChangeRot2 += (float)rot;
	}

	//ターゲットまでの距離を変更
	if (input->PushKey(DIK_O))
	{
		DebugTargetDistance -= 0.2f;
	}
	if (input->PushKey(DIK_P))
	{
		DebugTargetDistance += 0.2f;
	}

	//視点座標に代入
	eye_.x = sin(DebugChangeRot) * DebugTargetDistance + target_.x;
	eye_.y = sin(DebugChangeRot2) * DebugTargetDistance + target_.y;
	eye_.z = cos(DebugChangeRot) * DebugTargetDistance + target_.z;
}

void Camera::UpdatePlayer(XMFLOAT3 playerPos, XMFLOAT3 playerRot)
{
	target_ = { playerPos.x,5.0f,playerPos.z };

	/*eye_.x = sin(playerChangeRot) * playerTargetDistance + target_.x;
	eye_.y = sin(playerChangeRot2) * playerTargetDistance;
	eye_.z = cos(playerChangeRot) * playerTargetDistance + target_.z;*/

	//1フレームあたりの移動量
	float rot = ((float)PI / 120.0f) * (-dxInput->GetStick(DXInput::RStickY));

	//視点座標を変更
	if (input->PushKey(DIK_UP))
	{
		DebugChangeRot2 -= (float)rot;
	}
	if (input->PushKey(DIK_DOWN))
	{
		DebugChangeRot2 += (float)rot;
	}
	if (DebugChangeRot2 < maxDebugChangeRot2 && DebugChangeRot2 > minDebugChangeRot2)
	{
		DebugChangeRot2 += (float)rot;
	}
	if (DebugChangeRot2 > maxDebugChangeRot2)DebugChangeRot2 = maxDebugChangeRot2 - 0.001f;
	if (DebugChangeRot2 < minDebugChangeRot2)DebugChangeRot2 = minDebugChangeRot2 + 0.001f;

	eye_.x = playerPos.x + (cos(-playerRot.y - (PI / 2)) * playerTargetDistance);
	eye_.y = playerPos.y + (cos(-playerRot.x + DebugChangeRot2) * playerTargetDistance);
	eye_.z = playerPos.z + (sin(-playerRot.y - (PI / 2)) * playerTargetDistance);

	////1フレームあたりの移動量
	//float rot = (float)PI / 120.0f;

	////視点座標を変更
	//if (dxInput->GetStick(DXInput::RStickX) <= -0.1)
	//{
	//	DebugChangeRot -= (float)rot;
	//}
	//if (dxInput->GetStick(DXInput::RStickX) >= +0.1)
	//{
	//	DebugChangeRot += (float)rot;
	//}
	//if (dxInput->GetStick(DXInput::RStickY) <= -0.1)
	//{
	//	DebugChangeRot2 -= (float)rot;
	//}
	//if (dxInput->GetStick(DXInput::RStickY) >= +0.1)
	//{
	//	DebugChangeRot2 += (float)rot;
	//}

	//eye_.x = playerPos.x + (cos(DebugChangeRot) * playerTargetDistance);
	//eye_.y = playerPos.y + (cos(DebugChangeRot2) * playerTargetDistance);
	//eye_.z = playerPos.z + (sin(DebugChangeRot) * playerTargetDistance);
}

void Camera::UpdateTutorial(int tutorialTimer)
{
	int n = 60;
	if (tutorialTimer < n)
	{
		eye_.x = -10.0f + (n - tutorialTimer) * 2.0f;
	}
	eye_.y = 85.0f;
	eye_.z = 80.0f;

	if (tutorialTimer < n)
	{
		target_ = { (n - tutorialTimer) * 2.0f,65.0f,0.0f };
	}
}

void Camera::UpdateClear(XMFLOAT3 enemyPos, float timer)
{
	target_ = { enemyPos.x,enemyPos.y,enemyPos.z };

	float addRot = PI / 640.0f * timer;

	eye_.x = enemyPos.x + (- addRot * playerTargetDistance);
	eye_.y = enemyPos.y + (+ (PI * 15 / 40) * playerTargetDistance);
	eye_.z = enemyPos.z + (- (PI / 2) * playerTargetDistance);
}

void Camera::SetTarget(XMFLOAT3 pos)
{
	target_ = pos;
}

void Camera::SetEye(XMFLOAT3 pos)
{
	eye_ = pos;
}