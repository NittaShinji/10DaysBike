#pragma once

//�O���錾
class Player;

//�v���C���[�X�e�[�g�̊��N���X
class IPlayerState
{
protected:
	Player* player_ = nullptr;
	bool isWaitingTurn_ = false;
	float dirY_ = 0;

protected:
	void SideMoveUpdate();
public:
	void SetPlayerPtr(Player* player) { player_ = player; }
public:
	virtual void Init() = 0;
	virtual void Update();
	virtual void Draw() = 0;
};


//------------------------------------------------------------------------------
//��������
class PlayerStateUp : public IPlayerState
{
private:


private:

public:
	void Init()override;
	void Update()override;
	void Draw()override;
};

//���������
class PlayerStateDown : public IPlayerState
{
private:


private:

public:
	void Init()override;
	void Update()override;
	void Draw()override;
};

