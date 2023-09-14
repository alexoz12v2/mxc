#include "mmath/vec.h"
#include "mmath/constants.h"

#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

TEST_CASE("vector class should behave as a mathematical vector", "[Vector]")
{
    using mmath::Vec2f;
    using mmath::Vec3f;

    Vec3f v{mmath::pi, mmath::e, 0.24f};

    SECTION("testing assignment from swizzled proxy")
    {
        float x = v.x;
        REQUIRE_THAT(x, Catch::Matchers::WithinRel(v.x, 0.f) && Catch::Matchers::WithinRel(mmath::pi, 0.f));

        Vec2f newVal{2.f, 1.f};
        v.xy = newVal;
        REQUIRE_THAT(v.x, Catch::Matchers::WithinRel(2.f, 0.f));
    }

    SECTION("testing assignment to swizzled proxy")
    {
        Vec3f newVal{2.f, 1.f, 4.f};
        newVal.yx = {mmath::pi, mmath::e};

        REQUIRE_THAT(newVal.y, Catch::Matchers::WithinRel(mmath::pi, 0.f));
        REQUIRE_THAT(newVal.x, Catch::Matchers::WithinRel(mmath::e, 0.f));
    }

    SECTION("testing arithmetic operators")
    {
        Vec3f v1{0.f, 12.f, 0x1.bp-1f /*0.84375*/};
        Vec3f v2{-1.f, 0x1.0f8p0f /*1.060546875*/, 4.f};

        Vec3f vsum{v1 + v2};
        [[maybe_unused]] Vec3f vdiff{v1 - v2};
        REQUIRE_THAT(vsum.x, Catch::Matchers::WithinRel(-1.f, 0.f));
        REQUIRE_THAT(vsum.y, Catch::Matchers::WithinRel(0x1.a1fp3f, 0.f));
        REQUIRE_THAT(vsum.z, Catch::Matchers::WithinRel(0x1.36p2f, 0.f));
        REQUIRE(v1.x * 2 == 2 * v1.x);
    }
}
