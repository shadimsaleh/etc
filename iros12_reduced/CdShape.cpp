#include <iostream>
#include "CdShape.h"
#include "DistUtil.h"
#include <hrpModel/Link.h>

CdShape::CdShape(hrp::Link *i_link, const hrp::Vector3 &i_p, double i_r) 
    : m_link(i_link), m_type(SPHERE), m_radius(i_r)
{
    m_relP[0] = i_p;
}

CdShape::CdShape(hrp::Link *i_link,
                 const hrp::Vector3 &i_p1, 
                 const hrp::Vector3 &i_p2, double i_r)
    : m_link(i_link), m_type(CAPSULE), m_radius(i_r)
{
    m_relP[0] = i_p1;
    m_relP[1] = i_p2;
}


bool CdShape::isColliding(const CdShape *i_shape) const
{
    double d=0;
    if (m_type == SPHERE && i_shape->type() == SPHERE){
        d = (m_absP[0]-i_shape->center()).norm();
    }else if (m_type == CAPSULE && i_shape->type() == SPHERE){
        d = pointLineSegmentDistance(i_shape->center(), m_absP[0], m_absP[1]);
    }else if (m_type == SPHERE && i_shape->type() == CAPSULE){
        d = pointLineSegmentDistance(m_absP[0], i_shape->center(0), i_shape->center(1));
    }else if (m_type == CAPSULE && i_shape->type() == CAPSULE){
        d = SegSegDist(m_absP[0], m_absP[1], i_shape->center(0), i_shape->center(1));
    }else{
        std::cerr << "unknown type of pair:" << m_type << "," 
                  << i_shape->type() << std::endl;
    }
    return d < m_radius + i_shape->radius();
}

void CdShape::updatePosition()
{
    m_absP[0] = m_link->p + m_link->R*m_relP[0];
    if (m_type == CAPSULE) m_absP[1] = m_link->p + m_link->R*m_relP[1]; 
}
