#ifndef _COMPUTE
#define _COMPUTE

// hlsl 5.0 기준 최대 그룹당 지정가능한 스레드 개수는 1024개이다.
[numthreads(32, 32, 1)]
void CS_Test(int3 _ThreadID : SV_DispatchThreadID)
{
    
}

#endif