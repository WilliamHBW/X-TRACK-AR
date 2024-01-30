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

float* Quaternion::vec2world(const float* x)
{
    // Rotate (3x1 vector) by quaternion from body to world.
    // INPUTS:
    //   x - (3x1) input vector
    //   q - (4x1) quaternion by which to rotate vector
    // OUTPUTS:
    //   y - (3x1) rotated vector

    float** R = Rbw();
    float* y = new float[3];
    y[0] = R[0][0] * x[0] + R[0][1] * x[1] + R[0][2] * x[2];
    y[1] = R[1][0] * x[0] + R[1][1] * x[1] + R[1][2] * x[2];
    y[2] = R[2][0] * x[0] + R[2][1] * x[1] + R[2][2] * x[2];
    return y;
}

float* Quaternion::vec2local(const float* x)
{
    // Rotate (3x1 vector) by quaternion from world to body.
    // INPUTS:
    //   x - (3x1) input vector
    //   q - (4x1) quaternion by which to rotate vector
    // OUTPUTS:
    //   y - (3x1) rotated vector

    float** R = Rwb();
    float* y = new float[3];
    y[0] = R[0][0] * x[0] + R[0][1] * x[1] + R[0][2] * x[2];
    y[1] = R[1][0] * x[0] + R[1][1] * x[1] + R[1][2] * x[2];
    y[2] = R[2][0] * x[0] + R[2][1] * x[1] + R[2][2] * x[2];
    return y;
}

float** Quaternion::Rbw()
{
    // Convert quaternion to rotation matrix from body to world.
    // INPUTS:
    //   q - (4x1) quaternion
    // OUTPUTS:
    //   R - (3x3) rotation matrix from body to world
    float q0 = q[0];
    float q1 = q[1];
    float q2 = q[2];
    float q3 = q[3];

    float** R = new float*[3];
    for (int i = 0; i < 3; i++)
        R[i] = new float[3];
    
    R[0][0] = q0*q0 + q1*q1 - q2*q2 - q3*q3;
    R[1][0] = 2*(q1*q2 + q0*q3);
    R[2][0] = 2*(q1*q3 - q0*q2);

    R[0][1] = 2*(q1*q2 - q0*q3);
    R[1][1] = q0*q0 - q1*q1 + q2*q2 - q3*q3;
    R[2][1] = 2*(q2*q3 + q0*q1);

    R[0][2] = 2*(q1*q3 + q0*q2);
    R[1][2] = 2*(q2*q3 - q0*q1);
    R[2][2] = q0*q0 - q1*q1 - q2*q2 + q3*q3;

    return R;
}   

float** Quaternion::Rwb()
{
    // Convert quaternion to rotation matrix from world to body.
    // INPUTS:
    //   q - (4x1) quaternion
    // OUTPUTS:
    //   R - (3x3) rotation matrix from world to body

    float q0 = q[0];
    float q1 = q[1];
    float q2 = q[2];
    float q3 = q[3];

    float** R = new float*[3];
    for (int i = 0; i < 3; i++)
        R[i] = new float[3];
    
    R[0][0] = q0*q0 + q1*q1 - q2*q2 - q3*q3;
    R[0][1] = 2*(q1*q2 + q0*q3);
    R[0][2] = 2*(q1*q3 - q0*q2);

    R[1][0] = 2*(q1*q2 - q0*q3);
    R[1][1] = q0*q0 - q1*q1 + q2*q2 - q3*q3;
    R[1][2] = 2*(q2*q3 + q0*q1);

    R[2][0] = 2*(q1*q3 + q0*q2);
    R[2][1] = 2*(q2*q3 - q0*q1);
    R[2][2] = q0*q0 - q1*q1 - q2*q2 + q3*q3;
    return R;
}

float* Quaternion::rotate(const float* x)
{
    float* y = vec2world(x);
    float* z = vec2local(y);
    return z;
}