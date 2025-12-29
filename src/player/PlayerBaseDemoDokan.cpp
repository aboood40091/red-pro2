#include <player/PlayerBase.h>

static const sead::Vector3f unused(0.0f, 0.0f, 0.0f);

#define GLOBAL_FLOAT_TYPE(NAME, VALUE)  \
    namespace {                         \
                                        \
    struct NAME                         \
    {                                   \
        f32 value;                      \
                                        \
        NAME()                          \
            : value(VALUE)              \
        {                               \
        }                               \
    };                                  \
                                        \
    }                                   \
    static const NAME c##NAME;

GLOBAL_FLOAT_TYPE(DokanUDCheckMaxDistance, 12.0f)
GLOBAL_FLOAT_TYPE(DokanUDMameCheckMinDistance, 6.0f);
