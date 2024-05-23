#pragma once
#include "Component.h"
#include "I3DRenderer.h"

class Renderer : public Component
{
public:
	Renderer();
	~Renderer();

	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update(float dTime) override;
	virtual void LateUpdate(float dTime) override;
	
	void AddBox();
	void AddGrid(int gridSize_x, int gridSize_y);
	void SetBoxColor(float r, float g, float b, float a);
	void SetBoxColor(float* rgba);
	void SetRS(int nowRS);
	void SetRectSize(float scale);
	void AddText(int x, int y, float r, float g, float b, float a, const wchar_t* text, ...);

	void DeleteRenderer();


};

