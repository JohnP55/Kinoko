#pragma once

#include "game/kart/KartObjectProxy.hh"

namespace Kart {

class PlayerModel : public KartObjectProxy {
public:
    PlayerModel();

    // TODO: Should have pure virtual
    virtual void vf_1c();

    void init();
    void calc();

    void FUN_807CB198();
    void FUN_807CB530();
    void FUN_807C7828(u8 playerIdx, bool isBike);

private:
    bool m_somethingLeft;
    bool m_somethingRight;
    f32 _54;
    f32 _58;
    f32 _5c;
    f32 _64;
    bool m_isInsideDrift;
};

class PlayerModelKart : public PlayerModel {
public:
    PlayerModelKart();
};

class PlayerModelBike : public PlayerModel {
public:
    PlayerModelBike();
};

} // namespace Kart
