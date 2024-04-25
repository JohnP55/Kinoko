#pragma once

#include "game/kart/KartObjectProxy.hh"
#include "game/system/KPADController.hh"

namespace Kart {

/// @brief Manages trick inputs and state.
class KartJump : protected KartObjectProxy {
public:
    KartJump();
    virtual ~KartJump();

    void reset();
    void tryStart(const EGG::Vector3f &left);
    void calc();
    bool someFlagCheck();
    void calcInput();

    void setKartMove(KartMove *move);
    void setAngle(const EGG::Vector3f &left);

    bool isBoostRampEnabled() const;
    void setBoostRampEnabled(bool isSet);

protected:
    s16 m_cooldown;
    KartMove *m_move;

private:
    virtual void start(const EGG::Vector3f & /*left*/) {}
    virtual void init() {}

    System::Trick m_nextTrick;
    s16 m_nextAllowTimer;
    bool m_boostRampEnabled; // TODO: This is used in KartMove::calcRotation
};

class KartJumpBike : public KartJump {
public:
    KartJumpBike();
    ~KartJumpBike();

private:
    void start(const EGG::Vector3f &left) override;
    void init() override;
};

} // namespace Kart
