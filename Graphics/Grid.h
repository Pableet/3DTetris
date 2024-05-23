#pragma once

#include "IObject.h"


class Grid : public IObject
{
public:
	Grid();
	virtual ~Grid();

	virtual void Initialize(ID3D11Device* device) override;
	virtual void Update() override;

	
	
};

