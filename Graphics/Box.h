#pragma once

#include "IObject.h"


class Box : public IObject
{
public:
	Box();
	virtual ~Box();
	
	virtual void Initialize(ID3D11Device* device) override;
	virtual void Update() override;


private:

};

