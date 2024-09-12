#pragma once
#include<functional>
#include<string>

//前方宣言
class Player;

//プレイヤーステートの基底クラス
class IPlayerState
{
protected:
	Player* player_ = nullptr;
	bool isWaitingTurn_ = false;
	bool isWaitingBurst_ = false;
	float dirY_ = 0;

	int animeTimer_ = 0;
	bool isUsingCurveImage_ = false;
	bool isSideTurnImage_ = false;
	std::string useImageName_ = "";

protected:
	void AnimationUpdate(bool isUp);
	void TurnProcces();
protected:
	void SideMoveUpdate();
	void TurnPlayerUpdate(bool isTurn = false);
	void BurstPlayerUpdate();
	void UpDraw();
	void DownDraw();
public:
	void SetPlayerPtr(Player* player) { player_ = player; }
public:
	virtual void Init() = 0;
	virtual void Update(std::function<bool(float thickRate, float costRate,int32_t continueNum, const std::string& trajName)> shootFunc);
	void Update(std::function<bool(float thickRate, float costRate,int32_t continueNum, const std::string& trajName)> shootFunc, bool isUp);
	virtual void Draw() = 0;
};

//------------------------------------------------------------------------------
//上向き状態
class PlayerStateUp : public IPlayerState
{
private:


private:

public:
	void Init()override;
	void Update(std::function<bool(float thickRate, float costRate,int32_t continueNum, const std::string& trajName)> shootFunc)override;
	void Draw()override;
};

//---------------------------------------------
//下向き状態
class PlayerStateDown : public IPlayerState
{
private:


private:

public:
	void Init()override;
	void Update(std::function<bool(float thickRate, float costRate,int32_t continueNum, const std::string& trajName)> shootFunc)override;
	void Draw()override;
};


//----------------------------------------------------------------------------------------------
//バーストステート
class IBurstState : public IPlayerState
{
public:
	static const float BURST_THICK_RATE;
	static const float BURST_COST_RATE;
	static const float BURST_SPEED_RATE;
protected:
	uint16_t timer_ = 0;
	uint16_t timerMax_ = 0;
	bool isEnd_ = false;

public:
	virtual void Init()override = 0;
	virtual void Update(std::function<bool(float thickRate, float costRate,int32_t continueNum, const std::string& trajName)> shootFunc)override;
	virtual void Draw()override = 0;
};

//-----------------------------------------------
//上向きバースト状態
class PlayerStateBurstUp : public IBurstState
{
private:
	static const uint16_t STATE_TIME = 21;

private:

public:
	void Init()override;
	void Update(std::function<bool(float thickRate, float costRate,int32_t continueNum, const std::string& trajName)> shootFunc)override;
	void Draw()override;
};

//下向きバースト状態
class PlayerStateBurstDown : public IBurstState
{
private:
	static const uint16_t STATE_TIME = 21;

private:

public:
	void Init()override;
	void Update(std::function<bool(float thickRate, float costRate,int32_t continueNum, const std::string& trajName)> shootFunc)override;
	void Draw()override;
};