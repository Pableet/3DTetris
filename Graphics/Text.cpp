#include "Text.h"
#include "DX11Define.h"

#include "../DXTK/Inc/SimpleMath.h"

Text::Text()
	: m_spriteBatch(nullptr), m_spriteFont(m_spriteFont), m_rasterizerState(nullptr), m_depthStencilState(nullptr)
{

}

Text::~Text()
{
	SafeDelete(m_spriteFont);
	SafeDelete(m_spriteBatch);
}

void Text::Create(ID3D11Device* device, ID3D11RasterizerState* rs, ID3D11DepthStencilState* ds)
{
	ID3D11DeviceContext* deviceContext = nullptr;
	device->GetImmediateContext(&deviceContext);

	m_spriteBatch = new DirectX::SpriteBatch(deviceContext);

	TCHAR* fileName = (TCHAR*)L"../Resource/Font/gulim9k.spritefont";

	m_spriteFont = new DirectX::SpriteFont(device, fileName);
	m_spriteFont->SetLineSpacing(14.0f);
	//m_spriteFont->SetDefaultCharacter(' ');          

	SAFE_RELEASE(deviceContext);

	m_rasterizerState = rs;
	m_depthStencilState = ds;
}

void Text::DrawColorText(int x, int y, DirectX::XMFLOAT4 color, const wchar_t* text)
{
	// 	TCHAR _buffer[1024] = L"";
	// 	va_list vl;
	// 	va_start(vl, text);
	// 	_vstprintf(_buffer, 1024, text, vl);
	// 	va_end(vl);

	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch, text, DirectX::XMFLOAT2((float)x, (float)y), DirectX::SimpleMath::Vector4(color), /*rotation*/0,
		/*origin*/DirectX::XMFLOAT2(0, 0), /*scale*/DirectX::XMFLOAT2(2, 2));
	m_spriteBatch->End();
}
