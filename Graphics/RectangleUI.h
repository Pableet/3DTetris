#pragma once
#include "IObject.h"

class RectangleUI : public IObject
{
public:
	RectangleUI();
	virtual ~RectangleUI();

	virtual void Initialize(ID3D11Device* device) override;
	virtual void Update() override;


private:
};

