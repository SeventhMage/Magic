#ifndef _C_GAME_UNIT_H_
#define _C_GAME_UNIT_H_

namespace magic
{
class CGameUnit
{
public:
    CGameUnit();
private:
    IMesh *m_pMesh;
    IMaterial *m_pMaterial;
    IShader *m_pVertShader;
    IShader *m_pFragShader;
    CGameObject *m_pGameObject;
};
}

#endif
