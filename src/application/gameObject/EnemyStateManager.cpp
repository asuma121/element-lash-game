#include "EnemyStateManager.h"
#include "mathOriginal.h"
#include "ColliderManager.h"

void Stand::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectStand->StopAnimation();
	objectStand->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Stand::Move()
{
}

void Stand::UpdateState(Enemy* enemy)
{
}

void Stand::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectStand->Draw(cmdList);
}

void Stand::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectStand->DrawLightView(cmdList);
}

void Stand::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectStand->SetSRV(SRV);
}

void Stand::UpdateObject()
{
	objectStand->SetPosition(position);
	objectStand->SetRotation(rotation);
	objectStand->SetScale(scale);
	objectStand->Update();
}

void Walk::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectWalk->StopAnimation();
	objectWalk->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Walk::Move()
{
	//�v���C���[�ƓG�̃x�N�g���擾
	XMFLOAT3 velo = playerPos - position;
	//�G���v���C���[�̌����������悤�ɂ���
	rotation.y = getVectorRotation(velo).y;

	//�v���C���[�ɋ߂Â�
	position = position + normalize(velo) * walkSpeed;
}

void Walk::UpdateState(Enemy* enemy)
{
}

void Walk::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectWalk->Draw(cmdList);
}

void Walk::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectWalk->DrawLightView(cmdList);
}

void Walk::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectWalk->SetSRV(SRV);
}

void Walk::UpdateObject()
{
	objectWalk->SetPosition(position);
	objectWalk->SetRotation(rotation);
	objectWalk->SetScale(scale);
	objectWalk->Update();
}

void Attack01::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectAttack1->StopAnimation();
	objectAttack1->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Attack01::Move()
{
}

void Attack01::UpdateState(Enemy* enemy)
{
}

void Attack01::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack1->Draw(cmdList);
}

void Attack01::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttack1->DrawLightView(cmdList);
}

void Attack01::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttack1->SetSRV(SRV);
}

void Attack01::UpdateObject()
{
	objectAttack1->SetPosition(position);
	objectAttack1->SetRotation(rotation);
	objectAttack1->SetScale(scale);
	objectAttack1->Update();
}

void AttackOmen1::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectAttackOmen1->StopAnimation();
	objectAttackOmen1->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void AttackOmen1::Move()
{
}

void AttackOmen1::UpdateState(Enemy* enemy)
{
}

void AttackOmen1::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectAttackOmen1->Draw(cmdList);
}

void AttackOmen1::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectAttackOmen1->DrawLightView(cmdList);
}

void AttackOmen1::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectAttackOmen1->SetSRV(SRV);
}

void AttackOmen1::UpdateObject()
{
	objectAttackOmen1->SetPosition(position);
	objectAttackOmen1->SetRotation(rotation);
	objectAttackOmen1->SetScale(scale);
	objectAttackOmen1->Update();
}

void Dash::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectDash->StopAnimation();
	objectDash->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void Dash::Move()
{
	//�v���C���[�ƓG�̃x�N�g���擾
	XMFLOAT3 velo = playerPos - position;

	velo = normalize(velo);

	//�G���v���C���[�̌����������悤�ɂ���
	rotation.y = getVectorRotation(velo).y;

	//�v���C���[�ɋ߂Â�
	position = position + velo * dashSpeed;
}

void Dash::UpdateState(Enemy* enemy)
{
	//�I�u�W�F�N�g�ɏՓ˂�����|��郂�[�V������
	if (hitObjectFlag == true)
	{
		enemy->ChangeState(new Stand());
		return;
	}
}

void Dash::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectDash->Draw(cmdList);
}

void Dash::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectDash->DrawLightView(cmdList);
}

void Dash::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectDash->SetSRV(SRV);
}

void Dash::UpdateObject()
{
	objectDash->SetPosition(position);
	objectDash->SetRotation(rotation);
	objectDash->SetScale(scale);
	objectDash->Update();
}

void Dash::UpdateHitWall(JSONLoader::ColliderData objectColliderData)
{
	//�ǂ̒��ɂ����珈���I��
	if (ColliderManager::CheckCollider(colliderData, objectColliderData) == true)return;

	//�ǂ̊O�ɂ��鎞�̂�
	while (ColliderManager::CheckCollider(colliderData, objectColliderData) == false)
	{
		//�v���C���[���猴�_�̃x�N�g��
		XMFLOAT3 vec = XMFLOAT3(0.0f, 0.0f, 0.0f) - position;
		//�v���C���[���猴�_�̃x�N�g���𐳋K��
		vec = normalize(vec);
		//�ǂ̒��ɖ߂�܂ŉ��Z
		position = position + (vec * knockBackSpeed);
		//�R���C�_�[�f�[�^�̍��W�X�V
		colliderData.center = position;
	}
	//�t���O�𗧂Ă�
	hitObjectFlag = true;
}

void Dash::UpdateHitPiller(JSONLoader::ColliderData objectColliderData)
{
	//���ɏՓ˂��ĂȂ������珈���I��
	if(ColliderManager::CheckCollider(colliderData, objectColliderData) == false)return;

	//���ɂ߂荞��ł����
	while (ColliderManager::CheckCollider(colliderData, objectColliderData) == true)
	{
		//������v���C���[�̃x�N�g��
		XMFLOAT3 vec = objectColliderData.center - colliderData.center;
		//�v���C���[���猴�_�̃x�N�g���𐳋K��
		vec = normalize(vec);
		//�ǂ̒��ɖ߂�܂ŉ��Z
		position = position - (vec * knockBackSpeed);
		//�R���C�_�[�f�[�^�̍��W�X�V
		colliderData.center = position;
	}
	//�t���O�𗧂Ă�
	hitObjectFlag = true;
}

void CallMiniEnemy::Initialize()
{
	//�A�j���[�V�����̐ݒ�
	objectCallMiniEnemy->StopAnimation();
	objectCallMiniEnemy->PlayAnimation();

	//�^�C�}�[�̐ݒ�
	objectTimer = 0;
	objectTimeFlag = false;
}

void CallMiniEnemy::Move()
{
}

void CallMiniEnemy::UpdateState(Enemy* enemy)
{
}

void CallMiniEnemy::Draw(ID3D12GraphicsCommandList* cmdList)
{
	objectCallMiniEnemy->Draw(cmdList);
}

void CallMiniEnemy::DrawLightView(ID3D12GraphicsCommandList* cmdList)
{
	objectCallMiniEnemy->DrawLightView(cmdList);
}

void CallMiniEnemy::SetSRV(ID3D12DescriptorHeap* SRV)
{
	objectCallMiniEnemy->SetSRV(SRV);
}

void CallMiniEnemy::UpdateObject()
{
	objectCallMiniEnemy->SetPosition(position);
	objectCallMiniEnemy->SetRotation(rotation);
	objectCallMiniEnemy->SetScale(scale);
	objectCallMiniEnemy->Update();
}
