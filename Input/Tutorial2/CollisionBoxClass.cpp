#include "CollisionBoxClass.h"

CollisionBoxClass::CollisionBoxClass() {
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	m_dist = m_pos;
	isTrigger = false;
}
CollisionBoxClass::CollisionBoxClass(const CollisionBoxClass&) {}
CollisionBoxClass::~CollisionBoxClass(){}

bool CollisionBoxClass::Initialize() {
	SetMinMax();
	return true;
}
bool CollisionBoxClass::Initialize(D3DXVECTOR3 pos, D3DXVECTOR3 scale, D3DXVECTOR3 dist) {
	m_pos = pos;
	m_scale = scale;
	m_dist = dist;

	m_maxPos = pos + m_scale;
	m_minPos = pos - m_scale;
	return true;
}

void CollisionBoxClass::Shutdown() {
	return;
}


void CollisionBoxClass::SetPos(D3DXVECTOR3 pos) {
	m_pos = pos;
	return;
}

void CollisionBoxClass::SetScale(D3DXVECTOR3 scale) {
	m_scale = scale;
	return;
}
void CollisionBoxClass::SetDist(D3DXVECTOR3 dist) {
	m_dist = dist;
	return;
}

void CollisionBoxClass::SetMinMax() {
	m_minPos = m_pos - m_scale/2.0f; //cube의 정점들이 0.5, -0.5로 되어있기 때문에 중심부터의 거리는 0.5이다.
	m_maxPos = m_pos + m_scale/2.0f;
	return;
}

void CollisionBoxClass::Render(D3DXMATRIX* world, D3DXMATRIX* translate) {
	D3DXMatrixScaling(translate, m_scale.x, m_scale.y, m_scale.z);
	D3DXMatrixMultiply(world, world, translate);
	D3DXVECTOR3 pos = m_pos + m_dist;
	D3DXMatrixTranslation(translate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(world, world, translate);

	return;
}

D3DXVECTOR3 CollisionBoxClass::GetPos() {
	return m_pos;
}
D3DXVECTOR3 CollisionBoxClass::GetScale() {
	return m_scale;
}

D3DXVECTOR3 CollisionBoxClass::GetDist() {
	return m_dist;
}

bool CollisionBoxClass::Collision(CollisionBoxClass* other) {
	
	D3DXVECTOR3 otherMin, otherMax;
	other->GetMinMax(otherMin, otherMax);
	SetMinMax();

	bool bCheck = true;
	bCheck &= m_minPos.x <= otherMax.x;
	bCheck &= m_minPos.y <= otherMax.y;
	bCheck &= m_minPos.z <= otherMax.z;
	bCheck &= m_maxPos.x >= otherMin.x;
	bCheck &= m_maxPos.y >= otherMin.y;
	bCheck &= m_maxPos.z >= otherMin.z;

	return bCheck;

	return true;
}

void CollisionBoxClass::GetMinMax(D3DXVECTOR3& min, D3DXVECTOR3& max) {
	SetMinMax();
	min = m_minPos;
	max = m_maxPos;

	return;
}
void CollisionBoxClass::SetTrigger(bool value){
	isTrigger = value;
	return;
}
