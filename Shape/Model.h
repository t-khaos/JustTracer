#pragma once


#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <assert.h>
#include "../Tool/Vector.h"

struct Vertex {
    Point3f position;
    Vector3f normal;
    Vector2f textureCoords;
};

enum class TextureType {

};

struct Texture {
    int id;
    TextureType type;
};



struct Mesh {

    std::vector<std::vector<Vector3i>> faces;

    void LoadObj(const std::string &fileName) {

        std::vector<Vector3f> positions;
        std::vector<Vector3f> normals;
        std::vector<Vector2f> uvs;

        std::ifstream fileStream(fileName);

        std::string line;


        while (std::getline(fileStream, line)) {
            std::istringstream strStream(line.c_str());
            char trash;
            if (!line.compare(0, 2, "v ")) {
                strStream >> trash;
                Vector3f position;
                for (int i = 0; i < 3; ++i) {
                    strStream >> position[i];
                }
                positions.push_back(position);
            } else if (!line.compare(0, 3, "vn ")) {
                Vector3f normal;
                for (int i = 0; i < 3; ++i) {
                    strStream >> normal[i];
                }
                normals.push_back(normal);
            } else if (!line.compare(0, 3, "vt ")) {
                Vector2f uv;
                for (int i = 0; i < 2; ++i) {
                    strStream >> uv[i];
                }
                uvs.push_back(uv);
            } else if (!line.compare(0, 2, "f ")) {
                std::vector<Vector3i> face;
                Vector3i index;
                strStream>>trash;
                while(strStream >> index[0] >> trash >> index[1] >> trash >> index[2]){
                    for (int i = 0; i < 3; ++i) {
                        index[i]--;//wavefront obj 文件索引从1开始
                    }
                    face.push_back(index);
                }
                faces.push_back(face);
            }
        }


    }

};

struct Model{
    std::vector<Mesh> meshes;
    std::vector<Texture> textures;
};




