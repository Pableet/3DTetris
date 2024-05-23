
#include "GameProcess.h"

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// ���� ���� Ŭ����
	// ���ο��� ���� ������ �޽��� �ݹ��� ó���Ѵ�.
	// ���� �׷��Ƚ� ���� ���� �����Ѵ�.
	GameProcess* pGameProcess = new GameProcess();

	pGameProcess->Initialize(hInstance);
	pGameProcess->Loop();
	pGameProcess->Finalize();

	delete pGameProcess;
}
