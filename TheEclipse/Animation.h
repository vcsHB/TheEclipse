#pragma once
class Animator;
class Texture;
struct tAnimFrame
{
	Vec2 vLT;
	Vec2 vSlice;
	float fDuration;
	Vec2 vOffset;
};
class Animation
{
public:
	Animation();
	~Animation();
public:
	void Update();
	void Render(HDC _hdc);
public:
	void Create(Texture* _pTex, Vec2 _vLT, Vec2 _vSliceSize,
		Vec2 _vStep, int _framecount, float _fDuration, bool _isRotate);
public:
	const wstring& GetName() const { return m_strName; }
	void SetName(wstring _name) { m_strName = _name; }
	void SetAnimator(Animator* _animator) { m_pAnimator = _animator; }
	void SetFrame(int _frame) { m_CurFrame = _frame; }
	void SetFrameOffset(int _index, Vec2 _offset) { m_vecAnimFrame[_index].vOffset = _offset; }
	const UINT GetCurFrame() const { return m_CurFrame; }
	const size_t& GetMaxFrame() { return m_vecAnimFrame.size(); }
private:
	UINT   m_CurFrame; // ���� ������
	float  m_fAccTime; // ���� �ð�
	int	   m_repeatcnt; // �ݺ� Ƚ��
	wstring m_strName;
	Animator* m_pAnimator;
	Texture* m_pTex; // �ִϸ��̼� �ؽ�ó
	vector<tAnimFrame> m_vecAnimFrame;
	bool m_IsRotate;
};

