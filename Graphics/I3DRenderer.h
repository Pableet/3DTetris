#pragma once

#include "DirectXMath.h"
#include <string>


struct Vec2
{
	float x;
	float y;

	Vec2() = default;

	Vec2(const Vec2&) = default;
	Vec2& operator=(const Vec2&) = default;

	Vec2(Vec2&&) = default;
	Vec2& operator=(Vec2&&) = default;

	constexpr Vec2(float _x, float _y) noexcept : x(_x), y(_y) {}
	Vec2(const float* pArray)  noexcept : x(pArray[0]), y(pArray[1]) {}
};

struct Vec3
{
	float x;
	float y;
	float z;

	Vec3() = default;

	Vec3(const Vec3&) = default;
	Vec3& operator=(const Vec3&) = default;

	Vec3(Vec3&&) = default;
	Vec3& operator=(Vec3&&) = default;

	constexpr Vec3(float _x, float _y, float _z) noexcept : x(_x), y(_y), z(_z) {}
	Vec3(const float* pArray) noexcept : x(pArray[0]), y(pArray[1]), z(pArray[2]) {}
};

struct Vec4
{
	float x;
	float y;
	float z;
	float w;

	Vec4() = default;

	Vec4(const Vec4&) = default;
	Vec4& operator=(const Vec4&) = default;

	Vec4(Vec4&&) = default;
	Vec4& operator=(Vec4&&) = default;

	constexpr Vec4(float _x, float _y, float _z, float _w) noexcept : x(_x), y(_y), z(_z), w(_w) {}
	Vec4(const float* pArray) noexcept : x(pArray[0]), y(pArray[1]), z(pArray[2]), w(pArray[3]) {}
};


class I3DRenderer abstract
{
public:
	static I3DRenderer* CreateRenderer();

	virtual bool Initialize(int hWnd, int hInstance, int screenWidth, int screenHeight) abstract;
	virtual void Update(float dTime) abstract;

	virtual void BeginRender() abstract;
	virtual void Render() abstract;
	virtual void LateRender() abstract;
	virtual void EndRender() abstract;

	virtual void Finalize() abstract;

	virtual void OnResize() abstract;
	virtual bool IsValidDevice() abstract;
	virtual void SetClientSize(int screenWidth, int screenHeight) abstract;
	virtual void SetWinMinMax(bool isMinimized, bool isMaxmized) abstract;

	virtual void AddBox(std::string name, int nowRS) abstract;
	virtual void AddBox(int id, int nowRS) abstract;
	virtual void SetBoxColor(std::string name, float r, float g, float b, float a) abstract;
	virtual void SetBoxColor(int id, float r, float g, float b, float a) abstract;
	virtual void AddGrid(std::string name, int gridSize_x, int gridSize_y) abstract;

	virtual void SetRenderState(std::string name, int nowRS) abstract;
	virtual void SetRenderState(int id, int nowRS) abstract;
	virtual void SetRectSize(std::string name, float scale) abstract;
	virtual void SetRectSize(int id, float scale) abstract;
	virtual void Rotate(std::string name, float x, float y, float z) abstract;
	virtual void TransformObjectFromName(std::string name, const DirectX::XMMATRIX& world) abstract;
	virtual void TransformObjectFromID(int id, const DirectX::XMMATRIX& world) abstract;
	virtual void DeleteObject(int id) abstract;
	virtual void DeleteObject(std::string name) abstract;

	virtual void DrawColoredText(int x, int y,  float r, float g, float b, float a, int id, const wchar_t* text) abstract;
};

