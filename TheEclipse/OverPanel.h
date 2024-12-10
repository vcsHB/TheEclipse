#pragma once
#include "IControlablePanel.h"
#include "CanvasComponent.h"


class TextPro;
class Image;
class OverPanel : public CanvasComponent, public IControlable
{

public:

	void OnEnable() override;
	void Initialize() override;


public:

	// IControlable��(��) ���� ��ӵ�
	virtual void Open() override;
	virtual void Close() override;

private:

	TextPro* _textCompo;
	Image* _panelImage;

};

