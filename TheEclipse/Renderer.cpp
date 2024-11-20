#include "pch.h"
#include "Renderer.h"
#include "Object.h"

void Renderer::Render(HDC _hdc)
{


	Object* pObj = m_pOwner;
	Vec2 vPos = pObj->GetPos();

	// 오프셋 적용
	vPos = vPos + _currentSprite.offset;
	TransparentBlt(_hdc
		, (int)(vPos.x - _currentSprite.sliceSize.x / 2.f)
		, (int)(vPos.y - _currentSprite.sliceSize.y / 2.f)
		, (int)(_currentSprite.sliceSize.x)
		, (int)(_currentSprite.sliceSize.y)
		, m_pTex->GetTexDC()
		, (int)(m_vecAnimFrame[m_CurFrame].vLT.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vLT.y)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.x)
		, (int)(m_vecAnimFrame[m_CurFrame].vSlice.y)
		, RGB(255, 0, 255));
}
