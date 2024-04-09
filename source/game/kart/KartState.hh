#pragma once

#include "game/kart/KartObjectProxy.hh"

namespace Kart {

class KartState : KartObjectProxy {
public:
    KartState();

    void init();
    void reset();

    void calcInput();
    void calc();
    void calcCollisions();
    void calcStartBoost();
    void calcHandleStartBoost();
    void handleStartBoost(size_t idx);

    bool isDrifting() const;

    bool isAccelerate() const;
    bool isHopStart() const;
    bool isAllWheelsCollision() const;
    bool isTouchingGround() const;
    bool isHop() const;
    bool isChargeStartBoost() const;
    bool isBoost() const;
    bool isWheelie() const;
    bool isWheelieRot() const;
    bool isAutoDrift() const;
    f32 stickX() const;
    f32 stickY() const;
    u32 airtime() const;
    const EGG::Vector3f &top() const;
    f32 startBoostCharge() const;

    void setAccelerate(bool isSet);
    void setDriftManual(bool isSet);
    void setAllWheelsCollision(bool isSet);
    void setTouchingGround(bool isSet);
    void setHop(bool isSet);
    void setBoost(bool isSet);
    void setWheelie(bool isSet);
    void setWheelieRot(bool isSet);

private:
    // Bits from the base game's bitfields are marked with prefix 'b'
    bool m_bAccelerate;
    bool m_bBrake;
    bool m_bDriftInput;
    bool m_bDriftManual;
    bool m_bHopStart;
    bool m_bAccelerateStart;
    bool m_bAllWheelsCollision;
    bool m_bStickLeft;
    bool m_bTouchingGround;
    bool m_bHop;
    bool m_bBoost;
    bool m_bStickRight;
    bool m_bDriftAuto;
    bool m_bWheelie;

    bool m_bWheelieRot;

    bool m_bChargeStartBoost;

    bool m_bAutoDrift;

    u32 m_airtime;
    EGG::Vector3f m_top;
    f32 m_stickX;
    f32 m_stickY;
    f32 m_startBoostCharge;
    size_t m_startBoostIdx;
};

} // namespace Kart
