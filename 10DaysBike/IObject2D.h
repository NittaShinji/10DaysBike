#pragma once
#include"Vec2.h"
#include"Inform.h"
#include<DxLib.h>


//2Dオブジェクトの基底クラス
class IObject2D
{
protected:
	Vec2 pos_ = { 0,0 };
	Vec2 vec_ = { 0,0 };
	ColorDxLib color_ = { 255,255,255 };
	std::string name_ = "";
	bool isAlive_ = true;


protected:

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
public:
	void SetPos(const Vec2& pos) { pos_ = pos; }
	void SetVec(const Vec2& vec) { vec_ = vec; }
	void SetColor(const ColorDxLib& color) { color_ = color; }

	const Vec2& GetPos() { return pos_; }
	const Vec2& GetVec() { return vec_; }
	//Objectの色を取得(プロジェクト用に作った構造体が返る)
	const ColorDxLib& GetIObjectColor() { return color_; }
	//DXLibの描画にそのまま使える色を返す
	unsigned int GetColorUsedForDrawing() { return GetColor(color_.r, color_.g, color_.b); }
	bool GetIsAlive() { return isAlive_; }
	const std::string& GetName() { return name_; }

public:
	//画面外にあるか
	bool GetIsOffingScreen();
	bool GetIsOffingScreen(const Vec2& pos);
	bool GetIsOffingScreen(const Vec2& pos, const Vec2& pos2);
	bool GetIsOffingScreen(const Vec2& pos, const Vec2& pos2, const Vec2& pos3);
};

