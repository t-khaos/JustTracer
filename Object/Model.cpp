
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "../Math/Vector.h"

struct Vertex {
    Point3 position;
    Vector3 normal;
    Vector2 textureCoords;
};

enum class TextureType {

};

struct Texture {
    int id;
    TextureType type;
};



struct ModelMesh {

    std::vector<std::vector<Int3>> faces;

    void LoadObj(const std::string &fileName) {

        std::vector<Vector3> positions;
        std::vector<Vector3> normals;
        std::vector<Vector2> uvs;

        std::ifstream fileStream(fileName);

        std::string line;


        while (std::getline(fileStream, line)) {
            std::istringstream strStream(line.c_str());
            char trash;
            if (!line.compare(0, 2, "v ")) {
                strStream >> trash;
                Vector3 position;
                for (int i = 0; i < 3; ++i) {
                    strStream >> position[i];
                }
                positions.push_back(position);
            } else if (!line.compare(0, 3, "vn ")) {
                Vector3 normal;
                for (int i = 0; i < 3; ++i) {
                    strStream >> normal[i];
                }
                normals.push_back(normal);
            } else if (!line.compare(0, 3, "vt ")) {
                Vector2 uv;
                for (int i = 0; i < 2; ++i) {
                    strStream >> uv[i];
                }
                uvs.push_back(uv);
            } else if (!line.compare(0, 2, "f ")) {
                std::vector<Int3> face;
                Int3 index;
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




