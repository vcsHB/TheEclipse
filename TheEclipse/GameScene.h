#pragma once
#include "Scene.h"
class GameScene :
    public Scene
{
public:
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Update() override;
};

