#pragma once
#include "IObject2D.h"
#include "CollisionInfo.h"
#include "CollisionTypes.h"

class CollisionManager;

/// <summary>
/// ��b�R���C�_�[
/// </summary>
class BaseCollider
{
public:
	//�f�t�H���g�R���X�g���N�^
	BaseCollider() = default;
	//���z�f�X�g���N�^
	virtual ~BaseCollider() = default;

	friend class CollisionManager;

	//�I�u�W�F�N�g�������o�ϐ��̃I�u�W�F�N�g�ɑ��
	inline void SetObject(IObject2D* objcet)
	{
		this->objcet2d_ = objcet;
	}

	//�����o�ϐ��̃I�u�W�F�N�g�̒l��Ԃ�
	inline IObject2D* GetObject2d()
	{
		return objcet2d_;
	}

	//�����������o�ϐ��̑����ɑ��
	inline void SetAttribute(unsigned short attribute)
	{
		attribute_ = attribute;
	}

	//�����o�ϐ��ɑ�����ǉ�
	inline void AddAttribute(unsigned short attribute)
	{
		attribute_ |= attribute;
	}

	//�����o�ϐ��̑������폜
	inline void RemoveAttribute(unsigned short attribute)
	{
		attribute_ &= !attribute;
	}

	/// <summary>
	/// �X�V
	/// </summary>
	virtual void Update() = 0;

	//�`��^�C�v�擾
	inline CollisionShapeType GetShapeType() { return shapeType_; }

	//�Փˎ��Ăяo���֐�
	inline void OnCollison(const CollisionInfo& info)
	{
		objcet2d_->OnCollision(info);
	}

protected:

	//�I�u�W�F�N�g
	IObject2D* objcet2d_ = nullptr;
	//�`��^�C�v
	CollisionShapeType shapeType_ = SHAPE_UNKNOWN;
	//�����蔻�葮��
	unsigned short attribute_ = 0b1111111111111111;
};
