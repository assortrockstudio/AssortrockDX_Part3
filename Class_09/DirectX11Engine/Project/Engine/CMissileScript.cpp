#include "pch.h"
#include "CMissileScript.h"

CMissileScript::CMissileScript()
	: m_Speed(500.f)
{
}

CMissileScript::~CMissileScript()
{
}

void CMissileScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();

	vPos.y += m_Speed * DT;

	Transform()->SetRelativePos(vPos);
}

