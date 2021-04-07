#ifndef VECTOR_MODEL_H
#define VECTOR_MODEL_H

class Vector {
    private:
        float x;
        float y;
        float z;
    public:
        float get_x();
        float get_y();
        float get_z();
        void set_x(float x);
        void set_y(float y);
        void set_z(float z);
};

#endif