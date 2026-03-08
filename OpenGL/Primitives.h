#pragma once

#include "Model.h"

class Sphere : public Model
{
	public:
    Sphere(float radius, int stacks, int sectors) {
		generateVertices(radius, stacks, sectors);
        loadModel();
    }

    virtual void generateVertices(float radius, int stacks, int sectors) {
        std::cout << "Sphere constructor";
        float PI = 3.14159265359f;

        for (int i = 0; i < stacks; ++i)
        {
            float stackAngle1 = PI / 2 - i * PI / stacks;
            float stackAngle2 = PI / 2 - (i + 1) * PI / stacks;

            float xy1 = radius * cosf(stackAngle1);
            float z1 = radius * sinf(stackAngle1);

            float xy2 = radius * cosf(stackAngle2);
            float z2 = radius * sinf(stackAngle2);

            for (int j = 0; j < sectors; ++j)
            {
                float sectorAngle1 = j * 2 * PI / sectors;
                float sectorAngle2 = (j + 1) * 2 * PI / sectors;

                float x1 = xy1 * cosf(sectorAngle1);
                float y1 = xy1 * sinf(sectorAngle1);

                float x2 = xy2 * cosf(sectorAngle1);
                float y2 = xy2 * sinf(sectorAngle1);

                float x3 = xy2 * cosf(sectorAngle2);
                float y3 = xy2 * sinf(sectorAngle2);

                float x4 = xy1 * cosf(sectorAngle2);
                float y4 = xy1 * sinf(sectorAngle2);

                float u1 = (float)j / sectors;
                float v1 = (float)i / stacks;

                float u2 = (float)j / sectors;
                float v2 = (float)(i + 1) / stacks;

                float u3 = (float)(j + 1) / sectors;
                float v3 = (float)(i + 1) / stacks;

                float u4 = (float)(j + 1) / sectors;
                float v4 = (float)i / stacks;

                float r = 1.0f, g = 1.0f, b = 1.0f;

                auto push = [&](float x, float y, float z, float u, float v)
                    {
                        float nx = x / radius;
                        float ny = y / radius;
                        float nz = z / radius;

                        vertices.push_back(x);
                        vertices.push_back(y);
                        vertices.push_back(z);

                        vertices.push_back(nx);
                        vertices.push_back(ny);
                        vertices.push_back(nz);

                        vertices.push_back(r);
                        vertices.push_back(g);
                        vertices.push_back(b);

                        vertices.push_back(u);
                        vertices.push_back(v);
                    };

                // triangle 1
                push(x1, y1, z1, u1, v1);
                push(x2, y2, z2, u2, v2);
                push(x3, y3, z2, u3, v3);

                // triangle 2
                push(x1, y1, z1, u1, v1);
                push(x3, y3, z2, u3, v3);
                push(x4, y4, z1, u4, v4);
            }
        }
    };

    virtual ~Sphere() {
        vertices.clear();
	}
};

class Plane : public Model
{
public:
    Plane(float size) {
        Plane::generateVertices(size);
        loadModel();
    }

    virtual void generateVertices(float size) {
        float s = size * 0.5f;
        vertices = {
              -s, 0,-s, 0,1,0, 1,1,1, 0,1,
              -s, 0, s, 0,1,0, 1,1,1, 0,0,
               s, 0, s, 0,1,0, 1,1,1, 1,0,

              -s, 0,-s, 0,1,0, 1,1,1, 0,1,
               s, 0, s, 0,1,0, 1,1,1, 1,0,
               s, 0,-s, 0,1,0, 1,1,1, 1,1,
        };
	}
};

class Cube : public Model
{
public:
    Cube(float size) {
        Cube::generateVertices(size);
        loadModel();
    }
    virtual void generateVertices(float size) {
        float s = size * 0.5f;

        vertices = {
            // FRONT
            -s,-s, s,  0,0,1,  1,1,1,  0,0,
             s,-s, s,  0,0,1,  1,1,1,  1,0,
             s, s, s,  0,0,1,  1,1,1,  1,1,

            -s,-s, s,  0,0,1,  1,1,1,  0,0,
             s, s, s,  0,0,1,  1,1,1,  1,1,
            -s, s, s,  0,0,1,  1,1,1,  0,1,


            // BACK
            -s,-s,-s,  0,0,-1, 1,1,1,  1,0,
            -s, s,-s,  0,0,-1, 1,1,1,  1,1,
             s, s,-s,  0,0,-1, 1,1,1,  0,1,

            -s,-s,-s,  0,0,-1, 1,1,1,  1,0,
             s, s,-s,  0,0,-1, 1,1,1,  0,1,
             s,-s,-s,  0,0,-1, 1,1,1,  0,0,


             // LEFT
             -s,-s,-s, -1,0,0, 1,1,1, 0,0,
             -s,-s, s, -1,0,0, 1,1,1, 1,0,
             -s, s, s, -1,0,0, 1,1,1, 1,1,

             -s,-s,-s, -1,0,0, 1,1,1, 0,0,
             -s, s, s, -1,0,0, 1,1,1, 1,1,
             -s, s,-s, -1,0,0, 1,1,1, 0,1,


             // RIGHT
              s,-s,-s, 1,0,0, 1,1,1, 1,0,
              s, s, s, 1,0,0, 1,1,1, 0,1,
              s,-s, s, 1,0,0, 1,1,1, 0,0,

              s,-s,-s, 1,0,0, 1,1,1, 1,0,
              s, s,-s, 1,0,0, 1,1,1, 1,1,
              s, s, s, 1,0,0, 1,1,1, 0,1,


              // TOP
              -s, s,-s, 0,1,0, 1,1,1, 0,1,
              -s, s, s, 0,1,0, 1,1,1, 0,0,
               s, s, s, 0,1,0, 1,1,1, 1,0,

              -s, s,-s, 0,1,0, 1,1,1, 0,1,
               s, s, s, 0,1,0, 1,1,1, 1,0,
               s, s,-s, 0,1,0, 1,1,1, 1,1,


               // BOTTOM
               -s,-s,-s, 0,-1,0, 1,1,1, 1,1,
                s,-s, s, 0,-1,0, 1,1,1, 0,0,
               -s,-s, s, 0,-1,0, 1,1,1, 1,0,

               -s,-s,-s, 0,-1,0, 1,1,1, 1,1,
                s,-s,-s, 0,-1,0, 1,1,1, 0,1,
                s,-s, s, 0,-1,0, 1,1,1, 0,0
        };
    }

    virtual ~Cube() {
        vertices.clear();
    }
};