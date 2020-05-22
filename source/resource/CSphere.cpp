#include "resource/CSphere.h"
#include "math/CVector3.h"
#include "math/CVector2.h"

#include <string.h>

namespace magic
{
CSphere::CSphere(float fRadius, int iSlices, int iStacks)
{
    m_VerticesCount = iStacks * iSlices * 6;
    float drho = (float)(3.141592653589) / (float)iStacks;
    float dtheta = 2.0f * (float)(3.141592653589) / (float)iSlices;
    float ds = 1.0f / (float)iSlices;
    float dt = 1.0f / (float)iStacks;
    float t = 1.0f;
    float s = 0.0f;
    int i, j;     // Looping variables

    CVector3 *positions = new CVector3[m_VerticesCount];
    CVector3 *normals = new CVector3[m_VerticesCount];
    CVector2 *uvs = new CVector2[m_VerticesCount];
    int curCount = 0;

    for (i = 0; i < iStacks; i++)
    {
        float rho = (float)i * drho;
        float srho = (float)(sin(rho));
        float crho = (float)(cos(rho));
        float srhodrho = (float)(sin(rho + drho));
        float crhodrho = (float)(cos(rho + drho));

        s = 0.0f;
        CVector3 vVertex[4];
        CVector3 vNormal[4];
        CVector2 vTexture[4];

        for (j = 0; j < iSlices; j++)
        {
            float theta = (j == iSlices) ? 0.0f : j * dtheta;
            float stheta = (float)(-sin(theta));
            float ctheta = (float)(cos(theta));

            float x = stheta * srho;
            float y = ctheta * srho;
            float z = crho;

            vTexture[0].x = s;
            vTexture[0].y = t;
            vNormal[0].x = x;
            vNormal[0].y = y;
            vNormal[0].z = z;
            vVertex[0].x = x * fRadius;
            vVertex[0].y = y * fRadius;
            vVertex[0].z = z * fRadius;

            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;

            vTexture[1].x = s;
            vTexture[1].y = t - dt;
            vNormal[1].x = x;
            vNormal[1].y = y;
            vNormal[1].z = z;
            vVertex[1].x = x * fRadius;
            vVertex[1].y = y * fRadius;
            vVertex[1].z = z * fRadius;


            theta = ((j + 1) == iSlices) ? 0.0f : (j + 1) * dtheta;
            stheta = (float)(-sin(theta));
            ctheta = (float)(cos(theta));

            x = stheta * srho;
            y = ctheta * srho;
            z = crho;

            s += ds;
            vTexture[2].x = s;
            vTexture[2].y = t;
            vNormal[2].x = x;
            vNormal[2].y = y;
            vNormal[2].z = z;
            vVertex[2].x = x * fRadius;
            vVertex[2].y = y * fRadius;
            vVertex[2].z = z * fRadius;

            x = stheta * srhodrho;
            y = ctheta * srhodrho;
            z = crhodrho;

            vTexture[3].x = s;
            vTexture[3].y = t - dt;
            vNormal[3].x = x;
            vNormal[3].y = y;
            vNormal[3].z = z;
            vVertex[3].x = x * fRadius;
            vVertex[3].y = y * fRadius;
            vVertex[3].z = z * fRadius;

            for (int i = 0; i < 3; ++i)
            {
                positions[curCount] = vVertex[i];
                normals[curCount] = vNormal[i].normalize();
                uvs[curCount] = vTexture[i];
                ++curCount;
            }

            // Rearrange for next triangle
            memcpy(vVertex[0].v, vVertex[1].v, sizeof(CVector3));
            memcpy(vNormal[0].v, vNormal[1].v, sizeof(CVector3));
            memcpy(vTexture[0].v, vTexture[1].v, sizeof(CVector2));

            memcpy(vVertex[1].v, vVertex[3].v, sizeof(CVector3));
            memcpy(vNormal[1].v, vNormal[3].v, sizeof(CVector3));
            memcpy(vTexture[1].v, vTexture[3].v, sizeof(CVector2));

            for (int i = 0; i < 3; ++i)
            {
                positions[curCount] = vVertex[i];
                normals[curCount] = vNormal[i].normalize();
                uvs[curCount] = vTexture[i];
                ++curCount;
            }

        }
        t -= dt;
    }
    
    SetPositions((float (*)[3])positions[0].v, sizeof(CVector3) * m_VerticesCount);
    SetNormals((float (*)[3])normals[0].v, sizeof(CVector3) * m_VerticesCount);
    SetUVs((float (*)[2])uvs, sizeof(CVector2) * m_VerticesCount);
    float *colors = new float[m_VerticesCount * 4];
    memset(colors, 0, sizeof(float) * m_VerticesCount * 4);
    for (int i = 0; i<m_VerticesCount * 4; i += 4)
        colors[i] = 1.f;
    SetColors((float (*)[4])colors, sizeof(float) * m_VerticesCount * 4);
    
    SAFE_DEL_ARRAY(positions);
    SAFE_DEL_ARRAY(normals);
    SAFE_DEL_ARRAY(uvs);
    SAFE_DEL_ARRAY(colors);
}

CSphere::~CSphere()
{

}
}
