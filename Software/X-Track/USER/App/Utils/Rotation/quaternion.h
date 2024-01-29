#ifndef _QUATERNION_H
#define _QUATERNION_H

class Quaternion
{
    public:
        float q[4];
        Quaternion();
        Quaternion(float x, float y, float z, float w);
        Quaternion(const Quaternion& other);

        float* vec2world(const float*& x); // Convert vector from local to world
        float* vec2local(const float*& x); // Convert vector from world to local
        float** Rbw(); // Get rotation matrix from body to world
        float** Rwb(); // Get rotation matrix from world to body
};

#endif