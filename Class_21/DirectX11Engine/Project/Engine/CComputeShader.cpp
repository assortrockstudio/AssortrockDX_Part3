#include "pch.h"
#include "CComputeShader.h"

#include "CDevice.h"

CComputeShader::CComputeShader()
	: CShader(ASSET_TYPE::COMPUTE_SHADER)
{
}

CComputeShader::~CComputeShader()
{
}

int CComputeShader::CreateComputeShader(const wstring& _strFilePath, const string& _CSFuncName)
{
	if (FAILED(D3DCompileFromFile(_strFilePath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE
		, _CSFuncName.c_str(), "cs_5_0", D3DCOMPILE_DEBUG, 0
		, m_CSBlob.GetAddressOf()
		, m_ErrBlob.GetAddressOf())))
	{
		if (nullptr != m_ErrBlob)
		{
			MessageBoxA(nullptr
				, (char*)m_ErrBlob->GetBufferPointer()
				, "��ǻƮ ���̴� ������ ����", MB_OK);
		}
		else
		{
			MessageBox(nullptr
				, L"������ ã�� �� �����ϴ�."
				, L"��ǻƮ ���̴� ������ ����", MB_OK);
		}

		return E_FAIL;
	}
		

	// ComputeShader ��ü ����ä�
	if (FAILED(DEVICE->CreateComputeShader(m_CSBlob->GetBufferPointer()
		, m_CSBlob->GetBufferSize(), nullptr, m_CS.GetAddressOf())))
	{
		return E_FAIL;
	}

	return S_OK;
}

void CComputeShader::Binding()
{
}

void CComputeShader::Execute()
{
	CONTEXT->CSSetShader(m_CS.Get(), nullptr, 0);
	CONTEXT->Dispatch(1, 1, 1); // Group Count
}

