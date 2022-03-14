#pragma once

class CGameObject;
class CTexture;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,

	NONE
};

struct tCamEffect
{
	CAM_EFFECT m_eEffect;
	float fDuration;
	float fCurTime;
};

class CCameraManager
{
	SINGLETON(CCameraManager);

private:
	fPoint m_fptLookAt;			// ���� �ִ� ��ġ
	fPoint m_fptCurLookAt;		// ī�޶� ���� ���� ��ġ
	fPoint m_fptPrevLookAt;		// ī�޶� ������ ���� ��ġ
	CGameObject* m_pTargetObj;	// Ʈ��ŷ �� ������Ʈ

	fPoint m_fptDiff;			// �ػ� �߽ɰ� ī�޶� LookAt ������ ����

	float m_fTime = 1;			// Ÿ���� ���󰡴� �ѽð�
	float m_fAccTime;			// Ÿ���� ���� �ҿ�ð�
	float m_fSpeed;				// Ÿ���� ���󰡴� �ӵ�

	list<tCamEffect> m_listCamEffect;
	CTexture* m_pImg;

public:
	void init();
	void update();
	void render(HDC hDC);

	void SetLookAt(fPoint lookAt);
	void SetTargetObj(CGameObject* target);

	fPoint GetLookAt();			// ���� ī�޶� ��ġ ��ȯ
	fPoint GetRenderPos(fPoint objPos);
	fPoint GetRealPos(fPoint renderPos);

	void FadeIn(float duration);
	void FadeOut(float duration);

	void Scroll(fVec2 vec, float velocity);

private:
	void CalDiff();
};

