#pragma once

#include <container/seadTList.h>
#include <heap/seadDisposer.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>

namespace sead {

class ReadStream;

}

class DistantViewMgr;

class DistantViewMgrCameraParam : public sead::IDisposer
{
private:
    // These are actually in a different file

    class ParamBase;

    class ParamList : public sead::TList<ParamBase*>
    {
    public:
        ParamBase* getParam(const sead::SafeString& name) const;

        virtual void read(const void* file, u32 size);
        void read(sead::ReadStream& stream);
    };

    class ParamBase : public sead::IDisposer
    {
    public:
        ParamBase(ParamList* p_list, const char* name);
        virtual ~ParamBase();

        virtual void read(sead::ReadStream& stream);

        const char* getName() const { return mName; }

    protected:
        const char* mName;
        sead::TListNode<ParamBase*> mListNode;
    };

    template <typename T>
    class Param : public ParamBase
    {
    public:
        Param(const T& default_value);
        virtual ~Param();

        void read(sead::ReadStream& stream) override;

        const T& getValue() const { return mValue; }

    private:
        T mValue;
    };

    typedef Param<s32> ParamS32;
    typedef Param<f32> ParamF32;
    typedef Param<sead::Vector2f> ParamVec2f;

public:
    DistantViewMgrCameraParam(DistantViewMgr* dv_mgr, const sead::Vector3f* p_bg_pos, const sead::SafeString& dv_name);

    const sead::Vector2f& getProjOffset() const { return mProjOffset.getValue(); }
    s32 getTypeDirY() const { return mTypeDirY.getValue(); }
    f32 getMagnifProjOffsetY() const { return mMagnifProjOffsetY.getValue(); }
    f32 getMagnifCameraPosY() const { return mMagnifCameraPosY.getValue(); }
    const sead::Vector2f& getIndirectScrollSpd() const { return mIndirectScrollSpd.getValue(); }

    void getModelMtx(sead::Matrix34f* p_model_mtx) const;

private:
    ParamList mParamList;
    ParamVec2f mProjOffset;
    ParamS32 mTypeDirY;
    ParamF32 mMagnifProjOffsetY;
    ParamF32 mMagnifCameraPosY;
    ParamF32 mModelOffsetX;
    ParamF32 mModelOffsetY;
    ParamF32 mModelOffsetZ;
    ParamVec2f mIndirectScrollSpd;
    const sead::Vector3f* mpBgPos;
};
