#pragma once

template<typename T>
void SAFE_DELETE(T& Pointer)
{
	if(Pointer)
	{
		delete Pointer;
		Pointer = NULL;
	}
} 

template<typename T>
void SAFE_DELETE_ARRAY(T& Pointer)
{
	if(Pointer)
	{
		delete[] Pointer;
		Pointer = NULL;
	}
}

#define DECLARE_SINGLETON(type)\
	static type** GetInstance(void)\
	{\
	static type*	pInstance = new type;\
	if(pInstance == NULL)\
	pInstance = new type;\
	return &pInstance;\
	}\
	static void DestroyInstance(void)\
	{\
	type**	ppInstance = GetInstance();\
	if(*ppInstance != NULL)\
		{\
		delete *ppInstance;\
		*ppInstance = NULL;\
		}\
	}

#define GET_SINGLE(type) (*type::GetInstance())
#define DESTROY_SINGLE(type) (*type::GetInstance())->DestroyInstance()

#define ERR_MGS(hWnd,sz) MessageBox(hWnd,sz,L"Sysytem err",MB_OK);

class CKeyMgr;
#define PUSH_KEY(key) GET_SINGLE(CKeyMgr)->GetKey() & key ? true : false
#define UP_KEY(key) GET_SINGLE(CKeyMgr)->GetKey() & key ? false : true