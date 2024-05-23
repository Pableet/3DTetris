#pragma once

#include "../DXTK/Inc/SpriteFont.h"
#include "../DXTK/Inc/SpriteBatch.h"

class Text
{
public:
	Text();
	~Text();

	void Create(ID3D11Device* pDevice, ID3D11RasterizerState* rs, ID3D11DepthStencilState* ds);
	void DrawColorText(int x, int y, DirectX::XMFLOAT4 color, const wchar_t* text);

private:
	DirectX::SpriteBatch* m_spriteBatch;
	DirectX::SpriteFont* m_spriteFont;


	ID3D11RasterizerState* m_rasterizerState;
	ID3D11DepthStencilState* m_depthStencilState;
};