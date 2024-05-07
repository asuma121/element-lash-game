/**
 * @file PlayerBullet.h
 * @brief �Q�[���I�u�W�F�N�g ���@�̒e
 * @author Asuma Syota
 * @date 2023/12
 */

#pragma once
#include "DirectXMath.h"
#include "Camera.h"
#include "JSONLoader.h"
#include "PlayerBulletParticle.h"

class PlayerBullet
{
private:	//�G�C���A�X
	//Microsoft::WRL::���ȗ�
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	//DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private:	//�T�u�N���X
	struct Bullet
	{
		//���W
		XMFLOAT3 position1;
		//�ŏ��̃X�P�[��
		XMFLOAT3 scale;
		//�i�s�x�N�g��
		XMFLOAT3 velocity;
		//�^�C�}�[
		float timer;
		//�e�������鑬�x
		float destoryTime;
		//�t���O
		bool hitFlag;
		//�R���C�_�[�̃f�[�^
		JSONLoader::ColliderData colliderData;
	};

public://�ÓI�����o�֐�

	/// <summary>
	///�J�����Z�b�g
	/// </summary>
	static void SetCamera(Camera* camera) { PlayerBullet::camera = camera; }

public:

	//�����o�֐�

	/// <summary>
	///������
	/// </summary>
	void Initialize();

	/// <summary>
	///�X�V
	/// </summary>
	void Update();

	/// <summary>
	///�R���C�_�[�X�V
	/// </summary>
	void UpdateCollider();

	/// <summary>
	///�p�[�e�B�N���X�V
	/// </summary>
	void UpdateParticle();

	/// <summary>
	///�p�[�e�B�N���`��
	/// </summary>
	void DrawParticle(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	///�ړ�
	/// </summary>
	void Move();

	/// <summary>
	///�V���b�g�t���O���^�Ȃ�Βe����
	/// </summary>
	void CreateBullet();

	/// <summary>
	///�e���폜���鏈��
	/// </summary>
	void DeleteBullet();

	/// <summary>
	///�V���b�g����t���O���󂯎��
	/// </summary>
	void SetShotFlag(bool shotFlag) { PlayerBullet::shotFlag = shotFlag; };

	/// <summary>
	///�e�ɕK�v�ȏ����Z�b�g����
	/// </summary>
	void SetBullet(XMFLOAT3 position,XMFLOAT3 velocity,float timer,float destoryTime);

	/// <summary>
	///�q�b�g�t���O���Z�b�g����
	/// </summary>
	//void SetHitFlag(bool hitFlag, int num) { bullet[num].hitFlag = hitFlag; };
	void SetHitFlag(int num);

	/// <summary>
	///�R���C�_�[�f�[�^�擾
	/// </summary>
	//JSONLoader::ColliderData GetColliderData(int num) { return bullet[num].colliderData; }
	JSONLoader::ColliderData GetColliderData(int num);

	/// <summary>
	///�e�̐��擾
	/// </summary>
	size_t GetBulletNum() { return std::distance(bullet.begin(), bullet.end()); }

	/// <summary>
	///���W�擾
	/// </summary>
	//XMFLOAT3 GetPosition(int num) { return bullet[num].position1; }
	XMFLOAT3 GetPosition(int num);

	//�ÓI�����o�ϐ�
private:
	//�J����
	static Camera* camera;

	//�����o�ϐ�
private:

	//�I�u�W�F�N�g
	/*std::list<std::unique_ptr<FbxObject3D>>object;*/

	////���W
	//std::vector<XMFLOAT3> position;
	////��]
	//std::vector<XMFLOAT3> rotation;
	////�T�C�Y
	//std::vector<XMFLOAT3> scale;
	////�i�s�x�N�g��
	//std::vector<XMFLOAT3> velocity;
	////�^�C�}�[
	//std::vector<float>timer;
	////�t���O
	//std::vector<bool>hitFlag;
	//�p�[�e�B�N��
	std::unique_ptr<PlayerBulletParticle>particle;
	//�e�̏��
	std::forward_list<Bullet> bullet;

	XMFLOAT3 baseRotation = { 0.0f,0.0f,0.0f };
	XMFLOAT3 baseScale = { 1.0f,1.0f,1.0f };
	//�e�������鑬�x
	/*float destoryTime = 120.0f;*/

	//�e�ɂ���ԍ�
	int number = 0;
	//�V���b�g�t���O
	bool shotFlag = false;

	//�X�s�[�h
	float speed = 1.5f;

	//�f�o�b�O�p
	float bulletPos[3] = { 0.0f,0.0f,0.0f };

	//�e�̑傫���Ȃ�g�嗦
	float scaleAcc = 0.05f;
};
