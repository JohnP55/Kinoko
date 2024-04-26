#pragma once

#include "game/kart/KartObjectProxy.hh"
#include "game/system/KPADController.hh"

namespace Kart {

enum class BoostRampVariant {
    DoubleFlipTrick = 0,
    SingleFlipTrick = 1,
    StuntTrick = 2,
};

enum class TrickType {
    StuntTrickBasic = 0,
    BikeFlipTrickNose = 1,
    BikeFlipTrickTail = 2,
    FlipTrickYLeft = 3,
    FlipTrickYRight = 4,
    KartFlipTrickZ = 5,
    BikeSideStuntTrick = 6,
};

/// @brief Manages trick inputs and state.
class KartJump : protected KartObjectProxy {
public:
    struct TrickProperties {
        f32 initialAngleDiff;
        f32 angleDeltaMin;
        f32 angleDeltaFactorMin;
        f32 angleDiffMulDec;
    };

    KartJump();
    virtual ~KartJump();

    virtual void calcRot() {}

    void setupProperties();
    void reset();
    void tryStart(const EGG::Vector3f &left);
    void calc();
    bool someFlagCheck();
    void calcInput();
    void end();

    void setKartMove(KartMove *move);
    void setAngle(const EGG::Vector3f &left);

    bool isBoostRampEnabled() const;

    TrickType type() const;
    BoostRampVariant variant() const;
    s16 cooldown() const;

    void setBoostRampEnabled(bool isSet);

protected:
    TrickType m_type;
    BoostRampVariant m_variant;
    System::Trick m_nextTrick;
    f32 m_rotSign;
    TrickProperties m_properties;
    f32 m_angle;
    f32 m_angleDelta;
    f32 m_angleDeltaFactor;
    f32 m_angleDeltaFactorDec;
    f32 m_finalAngle;
    s16 m_cooldown;
    EGG::Quatf m_rot;
    KartMove *m_move;

private:
    virtual void start(const EGG::Vector3f & /*left*/) {}
    virtual void init() {}

    s16 m_nextAllowTimer;
    bool m_boostRampEnabled;
};

class KartJumpBike : public KartJump {
public:
    KartJumpBike();
    ~KartJumpBike();

    void calcRot() override;

private:
    void start(const EGG::Vector3f &left) override;
    void init() override;
};

} // namespace Kart
