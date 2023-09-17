#pragma once

GLuint texground;
std::vector<glm::vec4> vertsground;      //for models ground
std::vector<glm::vec4> normsground;
std::vector<glm::vec2> texcoordsground;
std::vector<unsigned int>indicesground;

GLuint texcannon;
std::vector<glm::vec4> vertscannon;      //for models cannon
std::vector<glm::vec4> normscannon;
std::vector<glm::vec2> texcoordscannon;
std::vector<unsigned int>indicescannon;

GLuint texbase;
std::vector<glm::vec4> vertsbase;      //for models cannon
std::vector<glm::vec4> normsbase;
std::vector<glm::vec2> texcoordsbase;
std::vector<unsigned int>indicesbase;

GLuint texbullet;
std::vector<glm::vec4> vertsbullet;      //for models cannon
std::vector<glm::vec4> normsbullet;
std::vector<glm::vec2> texcoordsbullet;
std::vector<unsigned int>indicesbullet;

GLuint texghost;
std::vector<glm::vec4> vertsghost;      //for models ghost
std::vector<glm::vec4> normsghost;
std::vector<glm::vec2> texcoordsghost;
std::vector<unsigned int>indicesghost;

GLuint texshop;
std::vector<glm::vec4> vertsshop;      //for models shop
std::vector<glm::vec4> normsshop;
std::vector<glm::vec2> texcoordsshop;
std::vector<unsigned int>indicesshop;

std::vector<glm::vec4> vertsshoptop;      //for models top shop
std::vector<glm::vec4> normsshoptop;
std::vector<glm::vec2> texcoordsshoptop;
std::vector<unsigned int>indicesshoptop;

GLuint texrobot;
std::vector<glm::vec4> vertsrobot;      //for models robot
std::vector<glm::vec4> normsrobot;
std::vector<glm::vec2> texcoordsrobot;
std::vector<unsigned int>indicesrobot;

GLuint texwheel;
std::vector<glm::vec4> vertswheel;      //for models wheels
std::vector<glm::vec4> normswheel;
std::vector<glm::vec2> texcoordswheel;
std::vector<unsigned int>indiceswheel;



//Loading model:
//ground
void LoadModelground(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertsground.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normsground.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordsground.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indicesground.push_back(face.mIndices[j]);
        }
    }
}
//cannon
void LoadModelcannon(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertscannon.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normscannon.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordscannon.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indicescannon.push_back(face.mIndices[j]);
        }
    }
}

//base
void LoadModelbase(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertsbase.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normsbase.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordsbase.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indicesbase.push_back(face.mIndices[j]);
        }
    }
}

//bullet
void LoadModelbullet(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertsbullet.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normsbullet.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordsbullet.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indicesbullet.push_back(face.mIndices[j]);
        }
    }
}

void LoadModelghost(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertsghost.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normsghost.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordsghost.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indicesghost.push_back(face.mIndices[j]);
        }
    }
}

void LoadModelshop(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertsshop.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normsshop.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordsshop.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indicesshop.push_back(face.mIndices[j]);
        }
    }
}

void LoadModelshoptop(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertsshoptop.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normsshoptop.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordsshoptop.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indicesshoptop.push_back(face.mIndices[j]);
        }
    }
}

//Loading texture:
GLuint readTexture(const char* filename) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);

    std::vector<unsigned char> image;
    unsigned width, height;
    unsigned error = lodepng::decode(image, width, height, filename);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
        GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    return tex;
}

void LoadModelrobot(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertsrobot.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normsrobot.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordsrobot.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indicesrobot.push_back(face.mIndices[j]);
        }
    }
}

void LoadModelwheel(std::string plik)
{
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(plik,
        aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals);

    auto mesh = scene->mMeshes[0];
    for (int i = 0; i < mesh->mNumVertices; i++) {
        aiVector3D vertex = mesh->mVertices[i];

        vertswheel.push_back(glm::vec4(vertex.x, vertex.y, vertex.z, 1));

        aiVector3D normal = mesh->mNormals[i];

        normswheel.push_back(glm::vec4(normal.x, normal.y, normal.z, 0));

        aiVector3D texcoord = mesh->mTextureCoords[0][i];

        texcoordswheel.push_back(glm::vec2(texcoord.x, texcoord.y));
    }

    for (int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace& face = mesh->mFaces[i];
        for (int j = 0; j < face.mNumIndices; j++)
        {
            indiceswheel.push_back(face.mIndices[j]);
        }
    }
}