#pragma once
#include "CShader.h"

class CComputeShader :
    public CShader
{
private:
    ComPtr<ID3DBlob>                m_CSBlob;
    ComPtr<ID3D11ComputeShader>     m_CS;

public:
    virtual void Binding();

public:
    void Execute();

public:    
    int CreateComputeShader(const wstring& _strFilePath, const string& _CSFuncName);

public:
    CComputeShader();
    ~CComputeShader();
};

