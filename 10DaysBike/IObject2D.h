#pragma once
#include"Vec2.h"
#include"Inform.h"
#include "CollisionInfo.h"
#include<DxLib.h>


//2D�I�u�W�F�N�g�̊��N���X
class IObject2D
{
protected:
	Vec2 pos_ = { 0,0 };
	Vec2 vec_ = { 0,0 };
	Vec2 coliderPos_ = { 0.0f,0.0f };
	float radius_ = 1.0f;
	ColorDxLib color_ = { 255,255,255 };
	std::string name_ = "";
	bool isAlive_ = true;
	BaseCollider* collider_ = nullptr;
	//�R���C�_�[���폜����
	bool isDeleteCollider_ = false;

protected:

public:
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
public:
	//vec_���g����pos_��ω�
	void Move();
public:
	void SetPos(const Vec2& pos) { pos_ = pos; }
	void SetVec(const Vec2& vec) { vec_ = vec; }
	void SetRadius(const float radius) { radius_ = radius; }
	void SetName(const std::string& name) { name_ = name; }

	void SetColor(const ColorDxLib& color) { color_ = color; }
	/// �R���C�_�[�̃Z�b�g
	void SetCollider(BaseCollider* collider);

	const Vec2& GetPos() { return pos_; }
	const Vec2& GetVec() { return vec_; }
	const Vec2& GetColliderPos() { return coliderPos_; }
	const float GetRadius() { return radius_; }

	//Object�̐F���擾(�v���W�F�N�g�p�ɍ�����\���̂��Ԃ�)
	const ColorDxLib& GetIObjectColor() { return color_; }
	//DXLib�̕`��ɂ��̂܂܎g����F��Ԃ�
	unsigned int GetColorUsedForDrawing() { return GetColor(color_.r, color_.g, color_.b); }
	bool GetIsAlive() { return isAlive_; }
	const std::string& GetName() { return name_; }
	const bool GetIsDeleteCollider() { return isDeleteCollider_; };

public:
	//��ʊO�ɂ��邩
	bool GetIsOffingGameScreen();
	bool GetIsOffingGameScreen(const Vec2& pos);
	bool GetIsOffingGameScreen(const Vec2& pos, const Vec2& pos2);
	bool GetIsOffingGameScreen(const Vec2& pos, const Vec2& pos2, const Vec2& pos3);
	//��ʓ��Ɏ��߂�
	void FitTheScreen(float radius);
public:

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	/// <param name="info">�Փˏ��</param>
	virtual void OnCollision(const CollisionInfo& info);

	//�R���C�_�[���폜����
	void RemoveCollider();
};

