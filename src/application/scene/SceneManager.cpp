#include "SceneManager.h"
#include <iostream>
#include "TitleScene.h"
#include "GameScene.h"
#include "TutorialScene.h"
#include "ClearScene.h"
#include "DevelopScene.h"

Scene::Scene()
{
	sceneState = new TitleScene();
}

Scene::~Scene()
{
	delete sceneState;
}
 
void Scene::Initialize()
{
	sceneState->Initialize();
}

void Scene::Update()
{
	sceneState->Update();
}

void Scene::Draw()
{
	sceneState->Draw();
}

void Scene::DrawFBXLightView()
{
	sceneState->DrawFBXLightView();
}

void Scene::NextScene(Scene* pState)
{
	sceneState->NextScene(pState);
}

void Scene::ChangeScene(SceneState* newState)
{
	delete sceneState;
	sceneState = newState;
}