#include "PlayerModel.hh"

#include "game/kart/KartBody.hh"
#include "game/kart/KartMove.hh"
#include "game/kart/KartParam.hh"
#include "game/kart/KartState.hh"

#include <egg/math/Math.hh>

namespace Kart {

PlayerModel::PlayerModel() {
    m_somethingLeft = false;
    m_somethingRight = false;
    _58 = 0.0f;
    _54 = 1.0f;
    _5c = 0.0f;
    _64 = 0.0f;
}

void PlayerModel::vf_1c() { // FUN_807CD32C
    _58 *= 0.9f;
    f32 xStick = inputs()->currentState().stick.x;
    f32 fVar2 = 0.1f;

    if (xStick <= 0.2f) {
        if (xStick < -0.2f) {
            _58 -= fVar2;
        }
    } else {
        _58 += fVar2;
    }

    xStick = EGG::Mathf::abs(xStick);

    _54 += fVar2 * (xStick - _54);

    if (_58 < -_54 || _54 < _58) {
        if (-_54 <= _58) {
            if (_54 < _58) {
                _58 -= 0.1f;
            }
        } else {
            _58 += 0.1f;
        }
    } else if (-_54 <= _58) {
        _58 = std::min(_54, _58);
    } else {
        _58 = -_54;
    }

    f32 dVar13 = _58;

    if (isBike()) {
        if (state()->isDrifting()) {
            dVar13 = m_isInsideDrift ? 5.0f : 20.0f;
        }
    } else {
        K_PANIC("NOT IMPLEMENTED FOR KARTS YET");
    }

    f32 dVar12 = 0.0f;
    _64 = dVar13 * 0.1f;

    if (isBike()) {
        dVar12 = -_58 * dVar13;

        if (m_somethingLeft) {
            if (m_isInsideDrift) {
                dVar12 += 5.0f;
            } else {
                dVar12 += 10.0f;
            }
        } else {
            if (m_somethingRight) {
                if (m_isInsideDrift) {
                    dVar12 -= 5.0f;
                } else {
                    dVar12 -= 10.0f;
                }
            }
        }
    } else {
        K_PANIC("NOT IMPLEMENTED FOR KARTS YET");
    }

    if (dVar12 <= _5c) {
        _5c -= _64;
        _5c = std::max(_5c, dVar12);
    } else {
        _5c += _64;
        _5c = std::min(_5c, dVar12);
    }

    body()->setAngle(_5c);
}

void PlayerModel::init() {
    FUN_807C7828(param()->playerIdx(), isBike());
}

void PlayerModel::calc() {
    FUN_807CB530();
}

void PlayerModel::FUN_807CB198() {
    m_somethingRight = false;
    m_somethingLeft = false;

    if (!state()->isDrifting()) {
        // Unimplemented kart-related stuff
        if (state()->isStickLeft() || state()->isStickRight()) {
            if (move()->hopStickX() == 1) {
                m_somethingLeft = true;
            } else {
                if (move()->hopStickX() == -1) {
                    m_somethingRight = true;
                } else if (!state()->isStickLeft()) {
                    m_somethingRight = true;
                } else {
                    m_somethingLeft = true;
                }
            }
        }
    }
}

void PlayerModel::FUN_807CB530() {
    FUN_807CB198();
    vf_1c();
}

void PlayerModel::FUN_807C7828(u8 /*playerIdx*/, bool /*isBike*/) {
    m_isInsideDrift = param()->stats().driftType == KartParam::Stats::DriftType::Inside_Drift_Bike;
}

PlayerModelKart::PlayerModelKart() = default;

PlayerModelBike::PlayerModelBike() = default;

} // namespace Kart
