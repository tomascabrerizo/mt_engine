#ifndef TM_MATH_H
#define TM_MATH_H

namespace mt {

    struct vec4
    {
        union
        {
            struct
            {
                float r;
                float g;
                float b;
                float a;
            };

            struct
            {
                float x;
                float y;
                float z;
                float w;
            };
        };
    };

    static vec4
    operator*(vec4& A, float B)
    {
        vec4 Result;
        Result = vec4{A.x*B, A.y*B, A.z*B, A.w*B};
        return Result;
    }

    static vec4
    operator*(float B, vec4& A)
    {
        vec4 Result;
        Result = vec4{A.x*B, A.y*B, A.z*B, A.w*B};
        return Result;
    }

    static vec4&
    operator*=(vec4& A, float B)
    {
        A = A*B;
        return A;
    }

    struct vec2
    {
            float x;
            float y;
    };

    inline vec2
    operator-(vec2& A)
    {
        vec2 Result;
        Result = vec2{-A.x, -A.y};
        return Result;
    }

    static vec2
    operator+(vec2& A, vec2& B)
    {
        vec2 Result;
        Result = vec2{A.x+B.x, A.y+B.y};
        return Result;
    }

    static vec2&
    operator+=(vec2& A, vec2& B)
    {
        A = A+B;
        return A;
    }

    static vec2
    operator-(vec2& A, vec2& B)
    {
        vec2 Result;
        Result = vec2{A.x-B.x, A.y-B.y};
        return Result;
    }

    static vec2&
    operator-=(vec2& A, vec2& B)
    {
        A = A-B;
        return A;
    }

    static vec2
    operator*(vec2& A, float B)
    {
        vec2 Result;
        Result = vec2{A.x*B, A.y*B};
        return Result;
    }

    static vec2
    operator*(float B, vec2& A)
    {
        vec2 Result;
        Result = vec2{A.x*B, A.y*B};
        return Result;
    }

    static vec2&
    operator*=(vec2& A, float B)
    {
        A = A*B;
        return A;
    }

    static float
    Dot(vec2& A, vec2& B)
    {
        float Result = (A.x*B.x+A.y*B.y);
        return Result;
    }

    static float
    LengthSqr(vec2& A)
    {
        float Result;
        Result = (A.x*A.x)+(A.y*A.y);
        return Result;
    }

    static float
    DistanceSqr(vec2& B, vec2& A)
    {
        return (A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);
    }

}
#endif
