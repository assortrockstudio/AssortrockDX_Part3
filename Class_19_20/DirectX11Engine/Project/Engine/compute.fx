#ifndef _COMPUTE
#define _COMPUTE

// hlsl 5.0 ���� �ִ� �׷�� ���������� ������ ������ 1024���̴�.
[numthreads(32, 32, 1)]
void CS_Test(int3 _ThreadID : SV_DispatchThreadID)
{
    
}

#endif