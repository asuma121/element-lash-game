#include "Terrain.h"
#include "ColliderManager.h"

Camera* Terrain::camera = nullptr;

Terrain::~Terrain()
{
	delete skySphereModel;
	delete skySphereObject;
	delete coliseumModel;
	delete pillerModel;
}

void Terrain::Initialize(ID3D12Device* device)
{
	//�V��
	skySphereModel = new ObjModel();
	skySphereModel->Initialize(device, "skyBox", "Resources/pictures/skyBox.png");
	skySphereObject = new ObjObject3D();
	skySphereObject->Initialize(device, skySphereModel, camera);
	skySphereObject->setScale(skySphereScale);
	skySphereObject->setRotation(skySpherePos);
	skySphereObject->setPosition(skySphereRotation);

	//�R���V�A���̃��f��
	coliseumModel = new ObjModel();
	coliseumModel->Initialize(device, "coliseum", "Resources/pictures/coliseum.png");
	coliseumObject = new ObjObject3D();
	coliseumObject->Initialize(device, coliseumModel, camera);
	coliseumObject->setScale(coliseumScale);
	coliseumObject->setRotation(coliseumPos);
	coliseumObject->setPosition(coliseumRotation);

	//���̃��f��
	pillerModel = new ObjModel();
	pillerModel->Initialize(device, "piller", "Resources/pictures/piller.png");

	//�V���ȊO�̃I�u�W�F�N�g�ǂݍ���
	objectData = JSONLoader::LoadTerrainObject("Resources/json/stage.json");

	for (int i = 0; i < objectData.size(); i++)
	{
		//�I�u�W�F�N�g����
		ObjObject3D* newObject = new ObjObject3D();
		//���f���ǂݍ���
		newObject->Initialize(device, pillerModel, camera);
		//���W�A�X�P�[���A�p�x�ݒ�
		newObject->setScale(objectData[i].scale);
		newObject->setRotation(objectData[i].rotation);
		newObject->setPosition(objectData[i].position);
		//�I�u�W�F�N�g�̖����ɒǉ�
		objects.emplace_back(newObject);
	}

	//�R���C�_�[
	colliderData = JSONLoader::LoadTerrainCollider("Resources/json/stage.json");
	colliderNum = colliderData.size();
	for (int i = 0; i < colliderData.size(); i++)
	{
		ColliderManager::SetCollider(colliderData[i]);
	}
}

void Terrain::Update()
{
	//�I�u�W�F�N�g�X�V
	skySphereObject->Update();
	coliseumObject->Update();
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Update();
	}
}

void Terrain::Draw(ID3D12GraphicsCommandList* cmdList)
{
	//�I�u�W�F�N�g�`��
	skySphereObject->Draw(cmdList, skySphereModel->vbView, skySphereModel->ibView);
	coliseumObject->Draw(cmdList, coliseumModel->vbView, coliseumModel->ibView);
	for (int i = 0; i < objects.size(); i++)
	{
		objects[i]->Draw(cmdList, pillerModel->vbView, pillerModel->ibView);
	}
}