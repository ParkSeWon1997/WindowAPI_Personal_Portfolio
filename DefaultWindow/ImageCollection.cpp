#include "stdafx.h"
#include "ImageCollection.h"
#include "BmpMgr.h"
#include "PngMrg.h"

ImageCollection::ImageCollection()
{
	//던전 백그라운드 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Dun/World/BossMap/Tile/BGLayer_0-sharedassets10.assets-1031.bmp", L"MapBack");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World/BossMap/Tile/BGLayer_1 #2319581.png", L"Map_Layer");
	//플레이어 Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Player/Bear1.png", L"Player");
	//총
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Gun/RussianRoulette.png", L"Player_Gun_Rusiian");
	//총알
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Weapon/Gun/Bullet/DogSkill.png", L"Player_Bullet");


	//보스몬스터 Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Boss/Boss_Nifl1.png", L"Boss_Monster");
	//일반 몬스터(박쥐) Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Monster/Default/Bat_Ice_Defalut.png", L"Defalut_Ice");

	//던전 입구 Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World/Entry/DungeonEntry.png", L"Dungeon_Entry");

	//스테이지 입구 Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/World/Stele.png", L"World_Stage_Entry");



	//마을 백그라운드 이미지
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/TownSky_Xmas.bmp", L"Ground");

	//마을 Image
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TownBG_Day.png", L"BackLayer1");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Temple.png", L"Temple");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TempleFront.png", L"Temple_front");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Tree0.png", L"Tree0");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/Tree1.png", L"Tree1");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/SecondFloor3.png", L"SecondFloor3");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/SecondFloor_Broken0.png", L"SecondFloor_Broken0");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/TownLayer_Day.png", L"BackLayer2");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Village/BGLayer_3-sharedassets19.assets-112.png", L"BackLayer3");



	//메뉴 이미지
	//메뉴 백그라운드
	CBmpMgr::Get_Instance()->Insert_Bmp(L"../Image/Menu/Menu.bmp", L"Menu");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Exit.png", L"Exit");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Option.png", L"Edit");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Button/new/Play.png", L"Start");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/BackCloud.png", L"BackCloud");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/FrontCloud.png", L"FrontCloud");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/Sky_Day.png", L"Sky_Day");
	PngMrg::Get_Instance()->Insert_Png(L"../Image/Dun/Map/MainLogo01.png", L"MainLogo");
}

ImageCollection::~ImageCollection()
{
}
