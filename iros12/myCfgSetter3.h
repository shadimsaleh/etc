/*
  ランダムサンプリングした胴体の高さ、回転、手先の回転から全関節角度を決定する
  コンフィギュレーションの長さは4+3
 */
#include <Math/MathFunction.h>
#include "cfgSetterBase.h"

class myCfgSetter3 : public cfgSetterBase
{
public:
    myCfgSetter3(motion_generator::HumanoidBodyPtr i_body,
                 const hrp::Vector3 &i_goalP)
        : cfgSetterBase(i_body), m_goalP(i_goalP){
        for (int i=0; i<2; i++){
            m_arm[i] = m_body->getJointPath(m_body->chestLink,
                                            m_body->wristLink[i]);
            if (m_arm[i]->numJoints() ==7){
                m_arm[i] = m_body->getJointPath(m_body->chestLink,
                                                m_body->wristLink[i]->parent);
            }
        }
        m_trunk = m_body->getJointPath(m_body->rootLink(), m_body->chestLink);

        for (int i=0; i<4; i++){
            m_ikFailCount[i] = 0;
        }
    }
    bool set(PathEngine::PathPlanner *i_planner,
             const PathEngine::Configuration &i_cfg){
        m_nCalls++;
        // compute trunk horizontal position
        setBase(i_cfg[0], i_cfg[1], i_cfg[2], i_cfg[3]);
        m_trunk->calcForwardKinematics();

        hrp::Matrix33 bulbR = hrp::rotFromPitch(-M_PI/2);
        hrp::Matrix33 R = hrp::rotFromRpy(i_cfg[4], i_cfg[5], i_cfg[6]); 
        hrp::Matrix33 wristR(bulbR*R);
        // assuming getGraspLocalPosition(0) and (1) are same
        hrp::Vector3 wristP(m_goalP - wristR*m_body->getGraspLocalPosition(0));
        if (i_cfg.size() == 8){
            wristR = wristR*hrp::rotFromPitch(-i_cfg[7]);
        }

        m_reachedArm=0;
        if (!calcIKwithLimitCheck(m_arm[0],wristP, wristR)) {
            m_ikFailCount[0]++;
            m_reachedArm = 1;
            if (!calcIKwithLimitCheck(m_arm[1], wristP, wristR)){
                m_ikFailCount[1]++;
                return false;
            }
        }
        for (int i=0; i<2; i++){ 
            if (!calcIKwithLimitCheck(m_leg[i], m_footP[i], m_footR[i])){
                m_ikFailCount[i+2]++; 
                return false;
            }
        }
        int freeArm = m_reachedArm == 0 ? 1 : 0;
        hrp::JointPathPtr path = m_arm[freeArm];
        for (int i=0; i<path->numJoints(); i++){
            hrp::Link *j = path->joint(i);
            j->q = j->defaultJointValue;
        }
        if (i_cfg.size() == 8){
            m_body->wristLink[freeArm]->q 
                = m_body->wristLink[freeArm]->defaultJointValue;
            m_body->wristLink[m_reachedArm]->q = i_cfg[7];
        }
        m_body->calcForwardKinematics();
        return true;
    }
    void profile(){
        std::cout << m_nCalls << " calls,";
        for (int i=0; i<4; i++) std::cout << m_ikFailCount[i] << " ";
        std::cout << std::endl;
    }
    int reachedArm(){ return m_reachedArm; }
private:
    int m_ikFailCount[4];
    hrp::JointPathPtr m_arm[2], m_trunk;
    hrp::Vector3 m_goalP;
    int m_reachedArm;
};
