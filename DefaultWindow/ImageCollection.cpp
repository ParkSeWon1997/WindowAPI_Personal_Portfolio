#include "stdafx.h"
#include "ImageCollection.h"
#include "BmpMgr.h"
#include "PngMrg.h"

ImageCollection::ImageCollection()
{
	//���� ��׶��� �̹���
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/World/BossMap/Tile/BGLayer_0-sharedassets10.assets-1031.bmp", L"MapBack");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/World/BossMap/Tile/NewBackLayer.bmp", L"NewBackLayer");


	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/World/BossMap/Tile/NewDefalutMap.bmp", L"Map_Layer_Bmp");



	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/World/BossMap/Tile/NewBGLayer.bmp", L"NewMap_Layer_Bmp");



	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/World/BossMap/Tile/Map.bmp", L"AllMap_tile");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/Village/sactx-0-2048x2048-Uncompressed-Atlas_Backgrounds-15187a57.bmp", L"Village_Tile");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World/BossMap/Tile/BGLayer_1 #2319581.png", L"Map_Layer");
	//�÷��̾� Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/Bear_New.png", L"Player");
	//��
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Gun/RussianRoulette_New.png", L"Player_Gun_Rusiian");
	//��
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Sword/FireDragonKiller.png", L"Player_Sword_FireDragon");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Sword/DragonHammer-resources.assets-82.png", L"Player_Hammer");
	//Cosmos ��
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Sword/CosmosSword_New.png", L"Player_Sword_Cosmos");
	// 
	//�� ����Ʈ
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Sword/FireGreatSwingFX00.png", L"Player_Sword_Effect");

	
	//�Ѿ�
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Gun/Bullet/DogSkill.png", L"Player_Bullet");
	//�÷��̾� Hit
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/UI/RedWarningOnHit.png", L"Player_Hit");
	//�÷��̾� HP UI
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/HP/PlayerLifeBase 1-sharedassets2.assets-123.png", L"Player_HP_UI");
	//�÷��̾� ���� â UI
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/EquippedWeaponBase.png", L"Player_Weapon_UI");


	//�������� Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Boss/Boss_New.png", L"Boss_Monster");
	//���� ���� HP UI
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/UI/BossLife_1.png", L"Boss_UI");

	//�Ϲ� ����(����) Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Default/Bat_Ice_Defalut.png", L"Defalut_Ice");

	//���� �Ա� Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World/Entry/DungeonEntry.png", L"Dungeon_Entry");

	//�������� �Ա� Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World/Stele.png", L"World_Stage_Entry");
	//���� �� ������ ���
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/Snow.png", L"Snow");



	//���� ��׶��� �̹���
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/1_0_1_TownSky_Xmas.bmp", L"Ground");

	//���� Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TownBG_Day.png", L"BackLayer1");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/Village/NewTownBG_Day.bmp",L"NewTownBGbmp");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TownBG.bmp",L"TownBGbmp");


	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Temple.png", L"Temple");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TempleFront.png", L"Temple_front");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Tree0.png", L"Tree0");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Tree1.png", L"Tree1");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/SecondFloor3.png", L"SecondFloor3");
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/Village/SecondFloor3.bmp", L"Map_LayerFloor_Bmp");

	//CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/Village/SecondFloor3.bmp", L"Map_LayerFloor_Bmp");

	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/SecondFloor_Broken0.png", L"SecondFloor_Broken0");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TownLayer_Day.png", L"BackLayer2");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/BGLayer_3-sharedassets19.assets-112.png", L"BackLayer3");



	//�޴� �̹���
	//�޴� ��׶���
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Exit.png", L"Exit");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Option.png", L"Edit");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Play.png", L"Start");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/BackCloud.png", L"BackCloud");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/FrontCloud.png", L"FrontCloud");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/Sky_Day.png", L"Sky_Day");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/MainLogo01.png", L"MainLogo");


	//BossMonset â
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Boss/Bullet/IceSpear12.png", L"BossMonset_Spear");
	//BossMonset ��帧
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Boss/Bullet/Icicle9-sharedassets12.assets-102.png", L"BossMonset_Icicle");


	//SubMonster
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Sub/IcePillar12.png", L"SubMonster");
	
	//SubMonster �Ѿ�
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Boss/Bullet/IceBullet.png", L"SubMonster_Bullet");


	//GameEnding
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/GameEnd/Fail_End.png", L"Fail_Ending");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/GameEnd/Success.png", L"Success_Ending");

	//EndButton
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/GameEnd/EndButton.png", L"EndButton");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/GameEnd/EndEntry.png", L"EndEntry");


	//Item
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/Hp/AED_Motion.png", L"Item_HP");
	//item Box
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Item/BigBox0-sharedassets7.assets-144.png", L"Item_Box");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Item/BigBoxParticle0-sharedassets5.assets-9.png", L"Item_Box_broken");
	

	//HitEffect(player Hit)
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Effect/SummonBallFX05_Size_12.png", L"Hit_Effect");
	//HitEffect(Monster Hit)
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Effect/HitFX1.png", L"Monster_Hit_Effect");


	//NPC
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/NPC/NPC_1.0.0.png", L"NPC_Giant");

	//F ��ư
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/Keyboard_F.png", L"F_Button");
}

ImageCollection::~ImageCollection()
{
}
