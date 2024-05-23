//***************************************************************************************
// d3dUtil.h by Frank Luna (C) 2011 All Rights Reserved.
//***************************************************************************************

#ifndef D3DUTIL_H
#define D3DUTIL_H

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

///----------------------------------------
//#define _XM_NO_INTRINSICS_	// LEHIDE : �÷��� �� ���� �Լ��� ������� �ʰ� float�����. ���� ���带 ���ؼ� �߰���.

// LEHIDE : DirectX11�� Windows 8.0 SDK���� �ٲ�鼭 ���� ���̺귯���� �����ؾ� �� �ʿ伺�� �����.
// �� ó���� �� ���� ������ DX11��å�� �������� ���� �� �� ����.

/// �̰��� �����
//#include <d3dx11.h>
//#include "d3dx11Effect.h"
//#include <xnamath.h>
//#include <dxerr.h>

/// �̰͵��� �߰��Ѵ�.
#include <d3d11.h>
#include <dxgi.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include "dxerr.h"

#pragma comment( lib, "d3d11.lib" )
#pragma comment( lib, "dxgi.lib" )	// adapter info

using namespace DirectX;
using namespace DirectX::PackedVector;

#include <wrl/client.h>
using namespace Microsoft::WRL;

///----------------------------------------

#include <SimpleMath.h>

using namespace std;
using namespace DirectX;
using namespace SimpleMath;

#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <list>

#include <winerror.h> //

///#define TRACE __noop
#include <atltrace.h>
#define TRACE ATLTRACE

//---------------------------------------------------------------------------------------
// Simple d3d error checker for book demos.
//---------------------------------------------------------------------------------------

// LEHIDE
/*
#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif
*/

// LEHIDE
#if defined(DEBUG) | defined(_DEBUG)
#ifndef HR
#define HR(x)									\
	{									\
		HRESULT hr = (x);						\
		if(FAILED(hr))							\
		{								\
			LPWSTR output;                                    	\
			FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |		\
				FORMAT_MESSAGE_IGNORE_INSERTS 	 |		\
				FORMAT_MESSAGE_ALLOCATE_BUFFER,			\
				NULL,						\
				hr,						\
				MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),	\
				(LPTSTR) &output,				\
				0,						\
				NULL);					        \
			MessageBox(NULL, output, L"Error", MB_OK);		\
		}								\
	}
#endif
#else
#ifndef HR
#define HR(x) (x)
#endif
#endif 

#ifndef D3DX11INLINE
#ifdef _MSC_VER
#if (_MSC_VER >= 1200)
#define D3DX11INLINE __forceinline
#else
#define D3DX11INLINE __inline
#endif
#else
#ifdef __cplusplus
#define D3DX11INLINE inline
#else
#define D3DX11INLINE
#endif
#endif
#endif


//---------------------------------------------------------------------------------------
// Convenience macro for releasing COM objects.
//---------------------------------------------------------------------------------------

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }
#define SAFE_RELEASE(x) { if(x){ x->Release(); x = 0; } }	// ���� ��Ÿ��


//---------------------------------------------------------------------------------------
// Convenience macro for deleting objects.
//---------------------------------------------------------------------------------------

#define SafeDelete(x) { delete x; x = 0; }
#define SAFE_DELETE(x) { delete x; x = 0; }


//---------------------------------------------------------------------------------------
// Utility classes.
//---------------------------------------------------------------------------------------

// class d3dHelper
// {
// public:
// 	///<summary>
// 	/// 
// 	/// Does not work with compressed formats.
// 	///</summary>
// 	static ID3D11ShaderResourceView* CreateTexture2DArraySRV(
// 		ID3D11Device* device, ID3D11DeviceContext* context,
// 		std::vector<std::wstring>& filenames,
// 		DXGI_FORMAT format = DXGI_FORMAT_FROM_FILE,
// 		UINT filter = D3DX11_FILTER_NONE, 
// 		UINT mipFilter = D3DX11_FILTER_LINEAR);
// 
// 	static ID3D11ShaderResourceView* CreateRandomTexture1DSRV(ID3D11Device* device);
// };

class TextHelper
{
public:

	template<typename T>
	static D3DX11INLINE std::wstring ToString(const T& s)
	{
		std::wostringstream oss;
		oss << s;

		return oss.str();
	}

	template<typename T>
	static D3DX11INLINE T FromString(const std::wstring& s)
	{
		T x;
		std::wistringstream iss(s);
		iss >> x;

		return x;
	}
};

// Order: left, right, bottom, top, near, far.
void ExtractFrustumPlanes(XMFLOAT4 planes[6], CXMMATRIX M);


/// CustomColor
namespace DRColors
{
	XMGLOBALCONST XMVECTORF32 DeepDarkGray = { { { 0.1f, 0.1f, 0.1f, 1.0f } } };
	XMGLOBALCONST XMVECTORF32 Crimson = { { { 0.6f, 0.1f, 0.1f, 1.0f } } };
}

/// DirectXColors�� ����.
// #define XMGLOBALCONST extern CONST __declspec(selectany)
//   1. extern so there is only one copy of the variable, and not a separate
//      private copy in each .obj.
//   2. __declspec(selectany) so that the compiler does not complain about
//      multiple definitions in a .cpp file (it can pick anyone and discard 
//      the rest because they are constant--all the same).

// namespace Colors
// {
// 	XMGLOBALCONST XMVECTORF32 White = { 1.0f, 1.0f, 1.0f, 1.0f };
// 	XMGLOBALCONST XMVECTORF32 Black = { 0.0f, 0.0f, 0.0f, 1.0f };
// 	XMGLOBALCONST XMVECTORF32 Red = { 1.0f, 0.0f, 0.0f, 1.0f };
// 	XMGLOBALCONST XMVECTORF32 Green = { 0.0f, 1.0f, 0.0f, 1.0f };
// 	XMGLOBALCONST XMVECTORF32 Blue = { 0.0f, 0.0f, 1.0f, 1.0f };
// 	XMGLOBALCONST XMVECTORF32 Yellow = { 1.0f, 1.0f, 0.0f, 1.0f };
// 	XMGLOBALCONST XMVECTORF32 Cyan = { 0.0f, 1.0f, 1.0f, 1.0f };
// 	XMGLOBALCONST XMVECTORF32 Magenta = { 1.0f, 0.0f, 1.0f, 1.0f };
// 
// 	XMGLOBALCONST XMVECTORF32 Silver = { 0.75f, 0.75f, 0.75f, 1.0f };
// 	XMGLOBALCONST XMVECTORF32 LightSteelBlue = { 0.69f, 0.77f, 0.87f, 1.0f };
// }

///<summary>
/// Utility class for converting between types and formats.
///</summary>
class Convert
{
public:
	///<summary>
	/// Converts XMVECTOR to XMCOLOR, where XMVECTOR represents a color.
	///</summary>
	static D3DX11INLINE XMCOLOR ToXmColor(FXMVECTOR v)
	{
		XMCOLOR dest;
		XMStoreColor(&dest, v);
		return dest;
	}

	///<summary>
	/// Converts XMVECTOR to XMFLOAT4, where XMVECTOR represents a color.
	///</summary>
	static D3DX11INLINE XMFLOAT4 ToXmFloat4(FXMVECTOR v)
	{
		XMFLOAT4 dest;
		XMStoreFloat4(&dest, v);
		return dest;
	}

	static D3DX11INLINE UINT ArgbToAbgr(UINT argb)
	{
		BYTE A = (argb >> 24) & 0xff;
		BYTE R = (argb >> 16) & 0xff;
		BYTE G = (argb >> 8) & 0xff;
		BYTE B = (argb >> 0) & 0xff;

		return (A << 24) | (B << 16) | (G << 8) | (R << 0);
	}

};

//#define ____error __noop

inline void ____error(LPCWSTR message)
{
	MessageBox(NULL, message, L"����!", MB_OK);
}
/*
/// �ӽ÷� ���� ���� ó�� �ڵ�
void ____error(int errorcode)
{
	TCHAR temptext[255];
	_itow_s(errorcode, temptext, 10);
	MessageBox(NULL, temptext, L"�����Դϴ�!", MB_OK);

}


void ____error(int errorcode, LPCWSTR message)
{
	TCHAR temptext[255];
	_itow_s(errorcode, temptext, 10);
	MessageBox(NULL, temptext, message, MB_OK);

}
*/


/// <summary>
/// 16����Ʈ ���� ����
/// ���Ǹ� ���� ���ø� Ŭ����. �ʿ��� Ŭ���� �� ����ü�� ��ӽ�Ű�� �ȴ�.
/// </summary>
template<size_t Aligment>
class AlignedAllocationPolicy
{
public:
	static void* operator new(size_t size)
	{
		return _aligned_malloc(size, Aligment);
	}

	static void operator delete(void* memory)
	{
		_aligned_free(memory);
	}
};


struct Vertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


/// ������ ���� ���� ����� �� ��
enum class eRenderingSystem
{
	Forward, Deferred,
};

#endif // D3DUTIL_H