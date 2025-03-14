#pragma once

#include <Common.hh>

namespace Field {

enum class ObjectId {
    DummyPole = 0x066,
    DokanSFC = 0x12e,
    OilSFC = 0x15d,
    TwistedWay = 0x1fe,
    Turibashi = 0x202,
    Aurora = 0x204,
    Ami = 0x20e,
};

enum class BlacklistedObjectId {
    Itembox = 0x65,
    Hanabi = 0x16a,
};

static constexpr bool IsObjectBlacklisted(u16 id) {
    BlacklistedObjectId objectId = static_cast<BlacklistedObjectId>(id);
    switch (objectId) {
    // Disabled collision
    case BlacklistedObjectId::Itembox:
        return true;

    // No collision
    case BlacklistedObjectId::Hanabi:
        return true;

    default:
        return false;
    }
}

} // namespace Field
