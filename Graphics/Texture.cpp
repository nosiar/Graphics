#include "Texture.h"
#include "lodepng.h"
#include <fstream>
#include <iostream>
#include <iterator>

namespace nosiar
{
    struct Texture::data_
    {
        std::vector<unsigned char> color, displacement, normal;
    };

    Texture::Texture(const char* color_file, const char* displacement_file,
        const char* normal_file, double displacement_scale/*=1*/)
        : displacement_scale(displacement_scale), _data(new data_)
    {
        if (color_file)
            init_texture(&color_map, _data->color, color_file);
        if (displacement_file)
            init_texture(&displacement_map, _data->displacement, displacement_file);
        if (normal_file)
            init_texture(&normal_map, _data->normal, normal_file);
    }

    Texture::~Texture()
    {
        delete _data;
    }

    void Texture::init_texture(GLuint *tex, std::vector<unsigned char>& data, const char* filename)
    {
        std::string temp = filename;
        auto extension = temp.substr(temp.find_last_of(".") + 1);

        if (extension == "png")
            init_PNG(tex, data, filename);
        else if (extension == "tga")
            init_TGA(tex, data, filename);
    }

    std::vector<unsigned char> Texture::load_TGA(const char* filepath)
    {
        std::ifstream fin(filepath, std::ios::binary);

        unsigned char header[12];
        unsigned char info[6];
        // read header/info from file
        fin.read((char*)header, 12);
        fin.read((char*)info, 6);
        // translate header/info
        width = info[0] | (info[1] << 8);
        height = info[2] | (info[3] << 8);
        int depth = info[4] / 8;

        // read data
        std::vector<unsigned char> data(width*height * 4);
        std::vector<unsigned char> temp(width*height*depth);
        fin.read((char*)&temp[0], width*height*depth);
        for (unsigned int j = 0; j < height; ++j)
        {
            for (unsigned int i = 0; i < width; ++i)
            {
                data[4 * (j*width + i)] = temp[depth*(j*width + i) + 2];
                data[4 * (j*width + i) + 1] = temp[depth*(j*width + i) + 1];
                data[4 * (j*width + i) + 2] = temp[depth*(j*width + i)];
                data[4 * (j*width + i) + 3] = depth == 4 ? temp[depth*(j*width + i) + 3] : 255;
            }
        }
        fin.close();

        return data;
    }

    void Texture::init_TGA(GLuint *tex, std::vector<unsigned char>& data, const char* filename)
    {
        data = load_TGA(filename);
        glDeleteTextures(1, tex);
        glGenTextures(1, tex);
        glBindTexture(GL_TEXTURE_2D, *tex);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
    }

    void Texture::init_PNG(GLuint *tex, std::vector<unsigned char>& data, const char* filename)
    {
        std::vector<unsigned char> temp;
        unsigned error = lodepng::decode(temp, width, height, filename);

        if (error) std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;

        data.reserve(temp.size());

        int size = static_cast<int>(temp.size()) / height;

        auto b = temp.end() - size;
        auto e = temp.end();
        auto dest = std::back_inserter(data);

        for (unsigned int i = 0; i < height - 1; ++i)
        {
            std::copy(b, e, dest);

            e -= size;
            b -= size;
        }
        std::copy(b, e, dest);

        glDeleteTextures(1, tex);
        glGenTextures(1, tex);
        glBindTexture(GL_TEXTURE_2D, *tex);
        glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &data[0]);
    }

    double Texture::Displacement(double u, double v) const
    {
        double px = u * (width - 1);
        double py = v * (height - 1);

        unsigned int x = static_cast<unsigned int>(px);
        unsigned int y = static_cast<unsigned int>(py);
        unsigned int xn = x < (width - 1) ? x + 1 : x;
        unsigned int yn = y < (height - 1) ? y + 1 : y;

        double d00 = static_cast<double>(_data->displacement[4 * (width*y + x)]) / 255;
        double d01 = static_cast<double>(_data->displacement[4 * (width*y + xn)]) / 255;
        double d10 = static_cast<double>(_data->displacement[4 * (width*yn + x)]) / 255;
        double d11 = static_cast<double>(_data->displacement[4 * (width*yn + xn)]) / 255;

        double xFractionalPart = px - x;
        double yFractionalPart = py - y;

        double d0 = (1.0 - xFractionalPart) * d00 + xFractionalPart * d01;
        double d1 = (1.0 - xFractionalPart) * d10 + xFractionalPart * d11;

        return ((1.0 - yFractionalPart) * d0 + yFractionalPart * d1) * displacement_scale;
    }
}