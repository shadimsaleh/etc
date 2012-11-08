#include <hrpPlanner/CollisionDetector.h>
#include <hrpModel/Body.h>
#include "CdShape.h"

class SphereTree;

class CustomCD : public PathEngine::CollisionDetector
{
public:
    CustomCD(hrp::BodyPtr i_robot, 
             const char *i_shapefile, const char *i_pairfile,
             hrp::BodyPtr i_env,
             const char *i_envpcfile);
    ~CustomCD();
    bool loadPointCloud(hrp::BodyPtr i_env, const char *i_envpcfile);
    void updatePositions();
    bool checkCollision();
private:
    std::vector<CdShape> m_shapes; ///< shapes of the robot
    /// self-collision check pairs
    std::vector<std::pair<const CdShape *, const CdShape *> > m_pairs;
    SphereTree *m_stree; ///< sphere tree of the environment 
};
