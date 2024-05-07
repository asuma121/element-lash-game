#include "TitleScene.h"
#include "mathOriginal.h"
#include "imgui.h"
#include "TutorialScene.h"

DXInput* TitleScene::dxInput = nullptr;
Input* TitleScene::input = nullptr;
DirectXCommon* TitleScene::dxCommon = nullptr;
Camera* TitleScene::camera = nullptr;
Light* TitleScene::light = nullptr;
Player* TitleScene::player = nullptr;
UI* TitleScene::ui = nullptr;

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Initialize()
{
	//�V�[���J�ڎ��ɏ�����
	if (sceneTimer == 0)
	{
		//�����X�v���C�g1
		Sprite* newBlackSprite1 = new Sprite();
		newBlackSprite1->Initialize();
		blackSprite1.reset(newBlackSprite1);
		blackSprite1->SetTextureNum(14);
		blackSprite1->SetScale(black1Scale);
	}
}

void TitleScene::Update()
{
	//�^�C�g���ɖ߂������Ƀt���O���Z�b�g
	if (sceneTimer == 0)
	{
		moveTutorialFlag1 = false;
	}

	//�^�C�}�[�X�V
	sceneTimer++;

	//�I�u�W�F�N�g�X�V
	UpdateObject();

	//�X�v���C�g�X�V
	UpdateSprite();

	//�V�[���J�ڍX�V
	UpdateMoveScene();
}

void TitleScene::NextScene(Scene* pScene)
{
	if (moveTutorialFlag1)
	{
		pScene->ChangeScene(new TutorialScene());
	}
}

void TitleScene::UpdateObject()
{
	//�J����
	camera->TitleUpdate(player->GetPosition(), player->GetRotation0(), moveTutorialTimer);
	camera->Update();

	//���C�g
	lightTarget[0] = player->GetPosition().x + 25;
	lightTarget[1] = player->GetPosition().y + 25;
	lightTarget[2] = player->GetPosition().z + 25;
	lightPos[0] = player->GetPosition().x;
	lightPos[1] = player->GetPosition().y;
	lightPos[2] = player->GetPosition().z;
	light->SetEye(XMFLOAT3(lightPos));
	light->SetTarget(XMFLOAT3(lightTarget));
	light->SetDir(XMFLOAT3(lightDir));
	light->Update();

	//UI�̍X�V
	ui->SetTitleTimer(moveTutorialTimer, titleMoveTime);
	ui->UpdateTitle();

	//�v���C���[
	player->UpdateTitle(moveTutorialTimer);
}

void TitleScene::UpdateSprite()
{
	//���� �V�[���J�ڎ�
	if (moveTutorialTimer > blackSpriteTime)
	{
		blackSprite1->SetAlpha(((float)moveTutorialTimer - (float)blackSpriteTime) 
			/ ((float)moveTutorialTime - (float)blackSpriteTime));
	}
	//���� �ʏ펞
	else
	{
		blackSprite1->SetAlpha(0.0f);
	}
	//�X�v���C�g�̍X�V
	blackSprite1->Update();
}

void TitleScene::UpdateMoveScene()
{
	//�X�y�[�X��A�{�^�������ꂽ��
	if (input->TriggerKey(DIK_SPACE) || dxInput->TriggerKey(DXInput::PAD_A))
	{
		//�V�[���J�ڃt���O�I��
		moveTutorialFlag2 = true;
	}
	//�V�[���J�ڃt���O����������
	if (moveTutorialFlag2)
	{
		//�^�C�}�[���Z
		moveTutorialTimer++;
		//�^�C�}�[���K��̃^�C���ɒB������
		if (moveTutorialTimer >= moveTutorialTime)
		{
			//���Z�b�g
			Reset();
			//���[�h���Q�[����
			moveTutorialFlag1 = true;
		}
	}
}

void TitleScene::Reset()
{
	//�^�C�}�[�����ɖ߂�
	moveTutorialTimer = 0;
	sceneTimer = 0;
	//�t���O�����ɖ߂�
	moveTutorialFlag2 = false;
}

void TitleScene::Draw()
{
	//FBX�`��
	DrawFBX();

	//�p�[�e�B�N���`��
	DrawParticle();

	//�X�v���C�g�`��
	DrawSprite();
}

void TitleScene::DrawFBX()
{
	player->Draw(dxCommon->GetCommandList());
}

void TitleScene::DrawSprite()
{
	//UI�`��
	ui->DrawTitle(dxCommon->GetCommandList());
	//�����`��
	blackSprite1->Draw(dxCommon->GetCommandList());
}

void TitleScene::DrawParticle()
{
	//�v���C���[�̃p�[�e�B�N���`��
	player->DrawParticle(dxCommon->GetCommandList());
}

void TitleScene::DrawFBXLightView()
{
	player->DrawLightView(dxCommon->GetCommandList());
}

void TitleScene::SetSRV(ID3D12DescriptorHeap* SRV)
{
	player->SetSRV(SRV);
}

void TitleScene::SetDevice(DirectXCommon* dxCommon, Input* input, DXInput* dxInput)
{
	//����������
	TitleScene::dxCommon = dxCommon;
	TitleScene::input = input;
	TitleScene::dxInput = dxInput;
}

void TitleScene::SetGameObject(Player* player, Camera* camera, Light* light, UI* ui)
{
	TitleScene::player = player;
	TitleScene::camera = camera;
	TitleScene::light = light;
	TitleScene::ui = ui;
}

DirectX::XMMATRIX TitleScene::GetLightViewProjection()
{
	return light->GetMatViewProjection();
}