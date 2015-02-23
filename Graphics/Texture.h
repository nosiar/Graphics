#pragma once

#include <memory>
#include <vector>
#include <GLFW/glfw3.h>


#ifdef GRAPHICS_EXPORTS
#define GRAPHICS_API __declspec(dllexport) 
#else
#define GRAPHICS_API __declspec(dllimport) 
#endif

namespace nosiar
{
    class GRAPHICS_API Texture final
    {
    public:
        Texture(const char* color_file,
            const char* displacement_file,
            const char* normal_file,
            double displacement_scale = 1);
        ~Texture();

        double Displacement(double u, double v) const;

        GLuint ColorMap() const { return color_map; }
        GLuint DisplacementMap() const { return displacement_map; }
        GLuint NormalMap() const { return normal_map; }

    private:
        void init_texture(GLuint *tex, std::vector<unsigned char>& data, const char* filename);
        void init_PNG(GLuint *tex, std::vector<unsigned char>& data, const char* filename);
        void init_TGA(GLuint *tex, std::vector<unsigned char>& data, const char* filename);
        std::vector<unsigned char> load_TGA(const char* filepath);

    private:
        double displacement_scale;
        unsigned width, height;
        GLuint color_map, displacement_map, normal_map;
        struct data_;
        data_* data;
    };
}