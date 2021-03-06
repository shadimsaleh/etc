#ifndef __CD_SHAPE_H__
#define __CD_SHAPE_H__

#include <hrpUtil/Eigen3d.h>

namespace hrp
{
    class Link;
};

class CdShape
{
public:
    typedef enum{SPHERE, CAPSULE} ShapeType;
    CdShape(hrp::Link *i_link, const hrp::Vector3 &i_p, double i_r);
    CdShape(hrp::Link *i_link, 
            const hrp::Vector3 &i_p1, 
            const hrp::Vector3 &i_p2, double i_r);
    ShapeType type() const { return m_type; };
    hrp::Vector3 center(int i=0) const { return m_absP[i]; }
    double radius() const { return m_radius; }
    bool isColliding(const CdShape *i_shape) const;
    void updatePosition();
    hrp::Link *link() const { return m_link; }
private:
    hrp::Link *m_link;
    ShapeType m_type;
    hrp::Vector3 m_relP[2], m_absP[2];
    double m_radius;
};

#endif
