#ifndef ATLAS_H
#define ATLAS_H
#include "graphics.h"

class Atlas
{
private:
    /* data */
public:
    Atlas(/* args */);
    ~Atlas();
    void load(const LPTCH path, const int num_frame);
    IMAGE *get_image(const int index);
};

#endif