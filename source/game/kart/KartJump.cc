#include "KartJump.hh"

#include "game/kart/KartCollide.hh"
#include "game/kart/KartMove.hh"
#include "game/kart/KartParam.hh"
#include "game/kart/KartState.hh"

#include "game/system/KPadController.hh"

#include <egg/math/Math.hh>

namespace Kart {

KartJump::KartJump() {
    m_cooldown = 0;
}

KartJump::~KartJump() = default;

void KartJump::reset() {
    m_cooldown = 0;
}

void KartJump::tryStart(const EGG::Vector3f &left) {
    if (!state()->isTrickStart()) {
        return;
    }

    if (m_move->speedRatioCapped() > 0.5f) {
        start(left);
        state()->setTrickStart(false);
    }
}

void KartJump::calc() {
    --m_cooldown;
    m_cooldown = std::max(0, static_cast<s32>(m_cooldown));
    calcInput();
}

bool KartJump::someFlagCheck() {
    return state()->isTrickStart() || state()->isInATrick();
}
void KartJump::calcInput() {
    constexpr s16 TRICK_ALLOW_TIMER = 14;

    System::Trick trick = inputs()->currentState().trick;

    if (!someFlagCheck() && trick != System::Trick::None) {
        m_nextTrick = trick;
        m_nextAllowTimer = TRICK_ALLOW_TIMER;
    }

    u32 airtime = state()->airtime();
    if (airtime == 0 || m_nextAllowTimer < 1 || airtime > 10 || (!state()->isTrickable() && state()->boostRampType() < 0) || someFlagCheck()) {
        --m_nextAllowTimer;
        m_nextAllowTimer = std::max(0, static_cast<s32>(m_nextAllowTimer));
    } else {
        if (airtime > 2) {
            state()->setTrickStart(true);
        }
        if (state()->isRampBoost()) {
            m_boostRampEnabled = true;
        }
    }
    if (state()->isTouchingGround() && !collide()->isRampBoost()) {
        m_boostRampEnabled = false;
    }
}

void KartJump::setKartMove(KartMove *move) {
    m_move = move;
}

void KartJump::setAngle(const EGG::Vector3f &left) {
    static constexpr std::array<std::array<std::array<f32, 2>, 3>, 3> ANGLE_PROPERTIES = {
            {{{{{40.0f, 15.0f}}, {{45.0f, 20.0f}}, {{45.0f, 20.0f}}}},
                    {{{{36.0f, 13.0f}}, {{42.0f, 18.0f}}, {{42.0f, 18.0f}}}},
                    {{{{32.0f, 11.0f}}, {{39.0f, 16.0f}}, {{16.0f, 1.0f}}}}}};

    f32 vel1YDot = m_move->vel1Dir().dot(EGG::Vector3f::ey);
    EGG::Vector3f vel1YCross = m_move->vel1Dir().cross(EGG::Vector3f::ey);
    f32 vel1YCrossMag = EGG::Mathf::sqrt(vel1YCross.dot());
    f32 askDerekTheMathGuyForABetterVarName = EGG::Mathf::atan2(vel1YCrossMag, vel1YDot);
    askDerekTheMathGuyForABetterVarName = EGG::Mathf::abs(askDerekTheMathGuyForABetterVarName);
    f32 angle = 90.0f - (askDerekTheMathGuyForABetterVarName * RAD2DEG);
    u32 weightClass = static_cast<u32>(param()->stats().weightClass);
    f32 targetAngle = ANGLE_PROPERTIES[weightClass][1][0];

    if (angle > targetAngle) {
        return;
    }

    f32 rotAngle = ANGLE_PROPERTIES[weightClass][1][1];

    if (angle + rotAngle > targetAngle) {
        rotAngle = targetAngle - angle;
    }

    EGG::Matrix34f nextDir;
    nextDir.setAxisRotation(-rotAngle * DEG2RAD, left);
    m_move->setDir(nextDir.ps_multVector(m_move->dir()));
    m_move->setVel1Dir(m_move->dir());
}

bool KartJump::isBoostRampEnabled() const {
    return m_boostRampEnabled;
}

void KartJump::setBoostRampEnabled(bool isSet) {
    m_boostRampEnabled = isSet;
}

KartJumpBike::KartJumpBike() = default;

KartJumpBike::~KartJumpBike() = default;

void KartJumpBike::start(const EGG::Vector3f &left) {
    init();
    setAngle(left);
    state()->setInATrick(true);
    m_cooldown = 5;
    KartMoveBike *moveBike = reinterpret_cast<KartMoveBike *>(m_move);
    moveBike->cancelWheelie();
}

void KartJumpBike::init() {
    ;
}

} // namespace Kart
