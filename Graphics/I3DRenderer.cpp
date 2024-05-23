#include "I3DRenderer.h"
#include "D3DRenderer.h"

I3DRenderer* I3DRenderer::CreateRenderer()
{
	D3DRenderer* renderer = new D3DRenderer;
	return renderer;
}
