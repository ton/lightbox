#include "obj_reader.h"

#include "common/itf/exception.h"
#include "core/itf/errors.h"

#include <iostream>
#include <sstream>

using namespace lb;

enum class Token
{
    COMMENT,
    FACE,
    GROUP,
    MATERIAL_LIBRARY,
    USE_MATERIAL,
    VERTEX,
    VERTEX_NORMAL,
    VERTEX_TEXTURE,
    UNKNOWN
};

/// Conversion operator from stream data to a token type.
std::istream &operator >>(std::istream &in, Token &token)
{
    std::string keyword;
    in >> keyword;

    if (keyword == "g")
    {
        token = Token::GROUP;
    }
    else if (keyword == "usemtl")
    {
        token = Token::USE_MATERIAL;
    }
    else if (keyword == "v")
    {
        token = Token::VERTEX;
    }
    else if (keyword == "vn")
    {
        token = Token::VERTEX_NORMAL;
    }
    else if (keyword == "vt")
    {
        token = Token::VERTEX_TEXTURE;
    }
    else if (keyword == "f")
    {
        token = Token::FACE;
    }
    else if (keyword == "#")
    {
        token = Token::COMMENT;
    }
    else if (keyword == "mtllib")
    {
        token = Token::MATERIAL_LIBRARY;
    }
    else
    {
        token = Token::UNKNOWN;
    }

    return in;
}

/// Constructs an OBJ reader using the data from the given input stream \a
/// objFile.
///
/// \param objFile input stream containing OBJ data
/// \throw ParseException in case of a parse error
ObjReader::ObjReader(std::ifstream &objFile)
{
    // The list of vertices making up the mesh.
    std::vector<Vertex> vertices;

    unsigned int lineNumber = 0;

    while (objFile.good())
    {
        std::string line;
        std::getline(objFile, line);

        // In case the line starts with a 'v', a vertex is defined.
        if (!line.empty())
        {
            std::stringstream ss(line);

            // Each line in an OBJ file is prefixed by a identifier indicating
            // what kind of data is stored on the line.
            Token token;
            ss >> token;

            switch (token)
            {
                case Token::VERTEX:
                    {
                        Vertex v;
                        ss >> v.x >> v.y >> v.z;

                        vertices.push_back(v);
                    }
                    break;
                case Token::FACE:
                    {
                        int v0, vt0, vn0;
                        parseVertex(ss, v0, vt0, vn0);

                        int v1, vt1, vn1;
                        parseVertex(ss, v1, vt1, vn1);

                        int v2, vt2, vn2;
                        parseVertex(ss, v2, vt2, vn2);

                        // In case the vertex indices are negative, they refer
                        // to the latest vertices in the list of vertices.  Note
                        // that vertex indices in the OBJ format start counting
                        // at one.
                        if (v0 < 0)
                        {
                            v0 = vertices.size() + v0;
                        }
                        else
                        {
                            v0 = v0 - 1;
                        }

                        if (v1 < 0)
                        {
                            v1 = vertices.size() + v1;
                        }
                        else
                        {
                            v1 = v1 - 1;
                        }

                        if (v2 < 0)
                        {
                            v2 = vertices.size() + v2;
                        }
                        else
                        {
                            v2 = v2 - 1;
                        }

                        // TODO: Raise an exception in case a face contains more
                        // than three vertices.

                        mesh_.addTriangle(Triangle(vertices[v0], vertices[v1], vertices[v2]));
                    }
                    break;
                case Token::UNKNOWN:
                    {
                        // Retrieve the first token again.
                        std::stringstream in(line);

                        std::string token;
                        in >> token;

                        throw ParseException(ErrorCode::OBJ_READER_INVALID_TOKEN) % token % lineNumber;
                    }
                    break;
                case Token::COMMENT:
                default:
                    break;
            }
        }

        ++lineNumber;
    }
}

/// Reads in a vertex from an OBJ file. Note that a vertex definition in an OBJ
/// file can have four different forms:
///
///   - <index>
///   - <index>/<texture coordinate index>
///   - <index>/<texture coordinate index>/<normal index>
///   - <index>//<normal index>
///
/// \param in the input string stream
/// \param[out] v index of the vertex
/// \param[out] vt index of the vertex texture coordinate
/// \param[out] vn index of the vertex normal
void ObjReader::parseVertex(std::stringstream &in, int &v, int &vt, int &vn) const
{
    in >> v;

    // Check to see if a vertex texture coordinate is
    // present, and if one is, read it.
    if (in.peek() == '/')
    {
        in.get();
        in >> vt;
    }

    // Check to see if a vertex normal is present, and in
    // case one is, ignore it.
    if (in.peek() == '/')
    {
        in.get();
        in >> vn;
    }
}
