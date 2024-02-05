#include "quaternion.h"

Quaternion::Quaternion()
{
    q[0] = 0.0f;
    q[1] = 0.0f;
    q[2] = 0.0f;
    q[3] = 1.0f;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    q[0] = x;
    q[1] = y;
    q[2] = z;
    q[3] = w;
}

Quaternion::Quaternion(const Quaternion& other)
{
    q[0] = other.q[0];
    q[1] = other.q[1];
    q[2] = other.q[2];
    q[3] = other.q[3];
}

float** Quaternion::Rwb()
{
    // Convert quaternion to rotation matrix.
    // INPUTS:
    //   q - (4x1) quaternion
    // OUTPUTS:
    //   R - (3x3) rotation matrix
    float qw = q[0];
    float qx = q[1];
    float qy = q[2];
    float qz = q[3];

    float** R = new float*[3];
    for (int i = 0; i < 3; i++)
        R[i] = new float[3];
    
    R[0][0] = 1 - 2*qy*qy - 2*qz*qz;
    R[0][1] = 2*(qx*qy - qz*qw);
    R[0][2] = 2*(qx*qz + qy*qw);

    R[1][0] = 2*(qx*qy + qz*qw);
    R[1][1] = 1 - 2*qx*qx - 2*qz*qz;
    R[1][2] = 2*(qy*qz - qx*qw);

    R[2][0] = 2*(qx*qz - qy*qw);
    R[2][1] = 2*(qy*qz + qx*qw);
    R[2][2] = 1 - 2*qx*qx - 2*qy*qy;
    return R;
}

float* Quaternion::rotate(const float* x)
{
    float** R = Rwb();
    float* z = new float[3];
    z[0] = R[0][0]*x[0] + R[0][1]*x[1] + R[0][2]*x[2];
    z[1] = R[1][0]*x[0] + R[1][1]*x[1] + R[1][2]*x[2];
    z[2] = R[2][0]*x[0] + R[2][1]*x[1] + R[2][2]*x[2];
    return z;
}