#pragma once
#include <Common.hh>
#include "game/system/map/MapdataGeoObj.hh"
#include <egg/math/Matrix.hh>
#include <egg/math/Vector.hh>
#include "game/field/CourseColMgr.hh"
#include "game/field/KCollisionTypes.hh"

namespace Field {

class GeoObject {
public:
    GeoObject(System::MapdataGeoObj* pMapDataGeoObj);
    virtual ~GeoObject();

    virtual void setup();
    virtual void update();
    virtual void init();
    virtual u16 id() const;
    virtual const char* name() const;
    virtual const char* resources() const;
    virtual u32 directorIndex() const;
    virtual void setDirectorIndex(s32 val);
    virtual void loadCollision();
    virtual void updateCollision();
    virtual void unregisterCollision();
    virtual void disableCollision();
    virtual void enableCollision();
    virtual EGG::Vector3f* getPosition() const;
    virtual f32 calcCollisionRadius();
private:
    u16 m_type;
    u16 m_flags;
    EGG::Vector3f m_pos;
    EGG::Vector3f m_scale;
    EGG::Vector3f m_rot;
    const char* m_modelName;
    EGG::Matrix34f m_transformationMatrix;
    u16 m_id;

    System::MapdataGeoObj* m_globalObj;
    u32 m_directorIndex;
};

struct GeoObjectArray {
    u16 m_count;
    GeoObject** m_array;
};

class GeoObjectDrivable : public GeoObject {
public:
    void init() override;

    virtual void initCollision();
    virtual void registerBoxColUnit(f32 radius);
    
    virtual bool checkPointPartial(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut);
    virtual bool checkPointPartialPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut);
    virtual bool checkPointFull(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut);
    virtual bool checkPointFullPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut);
    
    virtual bool checkSpherePartial(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius);
    virtual bool checkSpherePartialPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius);
    virtual bool checkSphereFull(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius);
    virtual bool checkSphereFullPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius);

    virtual void narrowScopeLocal(EGG::Vector3f* pos, f32 radius, KCLTypeMask);

    virtual bool checkPointCachedPartial(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut);
    virtual bool checkPointCachedPartialPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut);
    virtual bool checkPointCachedFull(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut);
    virtual bool checkPointCachedFullPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut);
    
    virtual bool checkSphereCachedPartial(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius);
    virtual bool checkSphereCachedPartialPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius);
    virtual bool checkSphereCachedFull(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius);
    virtual bool checkSphereCachedFullPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius);
private:
};

class GeoObjectKCL : public GeoObjectDrivable {
public:
    void loadCollision() override;

    void initCollision() override;
    bool checkPointPartial(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut) override;
    bool checkPointPartialPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut) override;
    bool checkPointFull(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut) override;
    bool checkPointFullPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut) override;
    bool checkSpherePartial(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius) override;
    bool checkSpherePartialPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius) override;
    bool checkSphereFull(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius) override;
    bool checkSphereFullPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius) override;
    void narrowScopeLocal(EGG::Vector3f* pos, f32 radius, KCLTypeMask) override;
    bool checkPointCachedPartial(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut) override;
    bool checkPointCachedPartialPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut) override;
    bool checkPointCachedFull(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut) override;
    bool checkPointCachedFullPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut) override;
    bool checkSphereCachedPartial(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius) override;
    bool checkSphereCachedPartialPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius) override;
    bool checkSphereCachedFull(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius) override;
    bool checkSphereCachedFullPush(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask* colMaskOut, u32 param_7, f32 radius) override;

    virtual void update(s32 timerRelated);
    virtual EGG::Matrix34f* getUpdatedMatrix();
    virtual EGG::Matrix34f* getScaleY() const;
    virtual EGG::Matrix34f* colRadiusAdditionalLength() const;
    virtual bool shouldCheckColNoPush() const;
    virtual bool shouldCheckColPush() const;
    virtual bool checkCollision(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask *colMaskOut, u32 param_7, f32 scale, f32 radius);
    virtual bool checkCollisionCached(EGG::Vector3f* pos, EGG::Vector3f* prevPos, KCLTypeMask flags, CourseColMgr::CollisionInfo* colInfo, KCLTypeMask *colMaskOut, u32 param_7, f32 scale, f32 radius);
};

} // namespace Field
