//Simon Pena Pereira  [5391210]
//Joppe van Veghel [5199115]

#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <assert.h>
#include <stack>
#include <list>
#include "DCEL.hpp"
#include "Point.h"

typedef std::pair<int, int> pair;

struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};


// forward declarations; these functions are given below main()
void DemoDCEL();
void printDCEL(DCEL& D);


// 1.

void importOBJ(DCEL& D, const char* file_in) {

    std::unordered_map<int, Vertex*> vmap;
    std::unordered_map<pair, HalfEdge*, pair_hash> emap;
    std::vector<Point> point_vertices;
    std::vector<std::vector<unsigned int>> or_faces;
    std::string line;
    std::ifstream in(file_in, std::ios::in);
    const auto& vertices = D.vertices();

    while (std::getline(in, line))
    {
        std::istringstream vert(line);
        vert >> line;
        if (line == "v") {
            float x, y, z;
            vert >> x >> y >> z;
            point_vertices.emplace_back(x, y, z);
        }
        if (line == "f") {
            unsigned int f1, f2, f3;
            vert >> f1 >> f2 >> f3;
            std::vector<unsigned int> temp = { f1, f2, f3 };
            or_faces.push_back(temp);
        }
    }

    for (int i = 0; i < point_vertices.size(); i++) {
        Point p = point_vertices[i];
        Vertex* v = D.createVertex(p.x, p.y, p.z);
        vmap[i + 1] = v;
    }


    for (int i = 0; i < or_faces.size(); i++) {

        int a0 = or_faces[i][0];
        int b0 = or_faces[i][1];
        pair pair0;
        pair0.first = a0;
        pair0.second = b0;

        int a1 = or_faces[i][1];
        int b1 = or_faces[i][2];
        pair pair1;
        pair1.first = a1;
        pair1.second = b1;

        int a2 = or_faces[i][2];
        int b2 = or_faces[i][0];
        pair pair2;
        pair2.first = a2;
        pair2.second = b2;

        int a3 = or_faces[i][1];
        int b3 = or_faces[i][0];
        pair pair3;
        pair3.first = a3;
        pair3.second = b3;

        int a4 = or_faces[i][2];
        int b4 = or_faces[i][1];
        pair pair4;
        pair4.first = a4;
        pair4.second = b4;

        int a5 = or_faces[i][0];
        int b5 = or_faces[i][2];
        pair pair5;
        pair5.first = a5;
        pair5.second = b5;

        Face* f = D.createFace();

        if (emap[pair0] == NULL) {
            HalfEdge* e0 = D.createHalfEdge();
            e0->origin = vmap[or_faces[i][0]];
            e0->destination = vmap[or_faces[i][1]];
            if (emap[pair3] == NULL) {
                HalfEdge* e0twin = D.createHalfEdge();
                e0->twin = e0twin;
                emap[pair3] = e0twin;
            }
            else {
                e0->twin = emap[pair3];
            }
            if (emap[pair1] == NULL) {
                HalfEdge* e0next = D.createHalfEdge();
                e0->next = e0next;
                emap[pair1] = e0next;
            }
            else {
                e0->next = emap[pair1];
            }
            if (emap[pair2] == NULL) {
                HalfEdge* e0prev = D.createHalfEdge();
                e0->prev = e0prev;
                emap[pair2] = e0prev;
            }
            else {
                e0->prev = emap[pair2];
            }
            e0->incidentFace = f;
            //std::cout << '\n' << "Before emap[pair0] = e0: " << emap[pair0];
            emap[pair0] = e0;
            //std::cout << '\n' << "After emap[pair0] = e0: " << emap[pair0];

            //std::cout << '\n' << "FACE: " << f;
            //std::cout << '\n' << "for face: " << i << ", e0: " << emap[pair0];
            std::cout << '\n' << "for face: " << i << ", e0: " << e0;
        }
        else {
            HalfEdge* e0 = emap[pair0];
            e0->origin = vmap[or_faces[i][0]];
            e0->destination = vmap[or_faces[i][1]];
            if (emap[pair3] == NULL) {
                HalfEdge* e0twin = D.createHalfEdge();
                e0->twin = e0twin;
                emap[pair3] = e0twin;
            }
            else {
                e0->twin = emap[pair3];
            }
            if (emap[pair1] == NULL) {
                HalfEdge* e0next = D.createHalfEdge();
                e0->next = e0next;
                emap[pair1] = e0next;
            }
            else {
                e0->next = emap[pair1];
            }
            if (emap[pair2] == NULL) {
                HalfEdge* e0prev = D.createHalfEdge();
                e0->prev = e0prev;
                emap[pair2] = e0prev;
            }
            else {
                e0->prev = emap[pair2];
            }
            e0->incidentFace = f;
            //std::cout << '\n' << "Before emap[pair0] = e0: " << emap[pair0];
            emap[pair0] = e0;
            //std::cout << '\n' << "After emap[pair0] = e0: " << emap[pair0];

            //std::cout << '\n' << "FACE: " << f;
            //std::cout << '\n' << "for face: " << i << ", e0: " << emap[pair0];
            std::cout << '\n' << "for face: " << i << ", e0: " << e0;

        }


        if (emap[pair1] == NULL) {
            HalfEdge* e1 = D.createHalfEdge();
            e1->origin = vmap[or_faces[i][1]];
            e1->destination = vmap[or_faces[i][2]];
            if (emap[pair4] == NULL) {
                HalfEdge* e1twin = D.createHalfEdge();
                e1->twin = e1twin;
                emap[pair4] = e1twin;
            }
            else {
                e1->twin = emap[pair4];
            }
            if (emap[pair2] == NULL) {
                HalfEdge* e1next = D.createHalfEdge();
                e1->next = e1next;
                emap[pair2] = e1next;
            }
            else {
                e1->next = emap[pair2];
            }
            if (emap[pair0] == NULL) {
                HalfEdge* e1prev = D.createHalfEdge();
                e1->prev = e1prev;
                emap[pair0] = e1prev;
            }
            else {
                e1->prev = emap[pair0];
            }
            e1->incidentFace = f;
            emap[pair1] = e1;


            //std::cout << '\n' << "for face: " << i << ", e1: " << emap[pair1];
            std::cout << '\n' << "for face: " << i << ", e1: " << e1;
        }
        else {
            HalfEdge* e1 = emap[pair1];
            e1->origin = vmap[or_faces[i][1]];
            e1->destination = vmap[or_faces[i][2]];
            if (emap[pair4] == NULL) {
                HalfEdge* e1twin = D.createHalfEdge();
                e1->twin = e1twin;
                emap[pair4] = e1twin;
            }
            else {
                e1->twin = emap[pair4];
            }
            if (emap[pair2] == NULL) {
                HalfEdge* e1next = D.createHalfEdge();
                e1->next = e1next;
                emap[pair2] = e1next;
            }
            else {
                e1->next = emap[pair2];
            }
            if (emap[pair0] == NULL) {
                HalfEdge* e1prev = D.createHalfEdge();
                e1->prev = e1prev;
                emap[pair0] = e1prev;
            }
            else {
                e1->prev = emap[pair0];
            }
            e1->incidentFace = f;
            emap[pair1] = e1;


            //std::cout << '\n' << "for face: " << i << ", e1: " << emap[pair1];
            std::cout << '\n' << "for face: " << i << ", e1: " << e1;
        }

        if (emap[pair2] == NULL) {
            HalfEdge* e2 = D.createHalfEdge();
            e2->origin = vmap[or_faces[i][2]];
            e2->destination = vmap[or_faces[i][0]];
            if (emap[pair5] == NULL) {
                HalfEdge* e2twin = D.createHalfEdge();
                e2->twin = e2twin;
                emap[pair5] = e2twin;
            }
            else {
                e2->twin = emap[pair5];
            }
            if (emap[pair0] == NULL) {
                HalfEdge* e2next = D.createHalfEdge();
                e2->next = e2next;
                emap[pair0] = e2next;
            }
            else {
                e2->next = emap[pair0];
            }
            if (emap[pair1] == NULL) {
                HalfEdge* e2prev = D.createHalfEdge();
                e2->prev = e2prev;
                emap[pair1] = e2prev;
            }
            else {
                e2->prev = emap[pair1];
            }
            e2->incidentFace = f;
            emap[pair1] = e2;

            //std::cout << '\n' << "for face: " << i << ", e1: " << emap[pair2];
            std::cout << '\n' << "for face: " << i << ", e2: " << e2;
        }
        else {
            HalfEdge* e2 = emap[pair2];
            e2->origin = vmap[or_faces[i][2]];
            e2->destination = vmap[or_faces[i][0]];
            if (emap[pair5] == NULL) {
                HalfEdge* e2twin = D.createHalfEdge();
                e2->twin = e2twin;
                emap[pair5] = e2twin;
            }
            else {
                e2->twin = emap[pair5];
            }
            if (emap[pair0] == NULL) {
                HalfEdge* e2next = D.createHalfEdge();
                e2->next = e2next;
                emap[pair0] = e2next;
            }
            else {
                e2->next = emap[pair0];
            }
            if (emap[pair1] == NULL) {
                HalfEdge* e2prev = D.createHalfEdge();
                e2->prev = e2prev;
                emap[pair1] = e2prev;
            }
            else {
                e2->prev = emap[pair1];
            }
            e2->incidentFace = f;
            emap[pair1] = e2;


            //std::cout << '\n' << "for face: " << i << ", e1: " << emap[pair2];
            std::cout << '\n' << "for face: " << i << ", e2: " << e2;
        }

        f->exteriorEdge = emap[pair0];

        //iterating throug halfedges
        HalfEdge* e = f->exteriorEdge;
        const HalfEdge* e_start = e;
        do {
            std::cout << " -> " << *e->origin << "\n";
            e = e->next;
        } while (e_start != e);
    }
}
// 2.

void createMeshes(DCEL& D,std::vector<std::list<Face*>>& meshes){

    const auto &faces = D.faces();
    std::stack<Face*> stack_f;
    std::list<Face*> mesh; // list to store all faces (store)
    std::list<Face*> marked_f; // list to check whether face has already been on the stack/used

    for (const auto &f : faces){
        if (std::find(marked_f.begin(), marked_f.end(), f->exteriorEdge->incidentFace) != marked_f.end()){
            continue;
        }
        else{
            stack_f.push(f->exteriorEdge->incidentFace);
        }
        while (!stack_f.empty()) {
            Face* f_top = stack_f.top();

            // for each face popped from stack, get its edges
            std::vector<HalfEdge *> edges;
            edges.push_back(f_top->exteriorEdge);
            edges.push_back(f_top->exteriorEdge->prev);
            edges.push_back(f_top->exteriorEdge->next);

            stack_f.pop();

            // For each edge that was not visited before, push incident face on stack, in lists
            for (const auto &e : edges) {
                if (std::find(marked_f.begin(), marked_f.end(), e->twin->incidentFace) != marked_f.end()) {
                    continue;
                } else {
                    stack_f.push(e->twin->incidentFace);
                    marked_f.push_back(e->twin->incidentFace);
                    mesh.push_back(e->twin->incidentFace);
                }
            }
        }// when stack is empty
        meshes.push_back(mesh);
        mesh.clear();
    }
}

// 3.
void iteration(Face* f_start) {
    std::stack<Face*> stack_f;
    std::list<Face*> marked_f; // list to check whether face has already been on the stack/used

    stack_f.push(f_start->exteriorEdge->incidentFace);

    while (!stack_f.empty()) {
        Face* f_top = stack_f.top();

        // for each face popped from stack, get its edges
        std::vector<HalfEdge*> edges;
        edges.emplace_back(f_top->exteriorEdge);
        edges.emplace_back(f_top->exteriorEdge->prev);
        edges.emplace_back(f_top->exteriorEdge->next);

        stack_f.pop();

        // For each edge that was not visited before, push incident face on stack, in lists
        for (const auto& e : edges) {
            if (std::find(marked_f.begin(), marked_f.end(), e->twin->incidentFace) != marked_f.end()) {
                continue;
            }
            else {
                if (e->origin == e->twin->destination && e->destination == e->twin->origin) {
                    stack_f.push(e->twin->incidentFace);
                    marked_f.push_back(e->twin->incidentFace);
                }
                else if (e->origin == e->twin->origin && e->destination == e->twin->destination){
                    Vertex* e_origin = e->twin->origin;
                    Vertex* e_dest = e->twin->destination;
                    std::swap(e_origin, e_dest);

                    Vertex* e1_origin = e->twin->prev->origin;
                    Vertex* e1_dest = e->twin->prev->destination;
                    std::swap(e1_origin, e1_dest);

                    Vertex* e2_origin = e->twin->next->origin;
                    Vertex* e2_dest = e->twin->next->destination;
                    std::swap(e2_origin, e2_dest);

                    stack_f.push(e->twin->incidentFace);
                    marked_f.push_back(e->twin->incidentFace);
                }
            }
        }
    }
}

float dist(float x, float y, float z, float a, float b, float c){
    return sqrt(pow(x - a, 2) + pow(y - b, 2)+pow(z - c, 2));
}

void orientMeshes(DCEL& D, std::vector<std::list<Face*>> meshes) {
    const auto &vertices = D.vertices();
    const auto &halfEdges = D.halfEdges();
    const auto &faces = D.faces();


    for(const auto &mesh : meshes){
        int iterator = 0;

        for (const auto &face : mesh){
            std::map<float, Face> dist_face_point;

            Vertex *vert0 = face->exteriorEdge->origin;
            Vertex *vert1 = face->exteriorEdge->destination;
            Vertex *vert2 = face->exteriorEdge->next->destination;

            // A = vert1 - vert0 ; B = vert2 - vert0
            double vert0_x = vert0->x;
            double vert0_y = vert0->y;
            double vert0_z = vert0->z;

            double vert1_x = vert1->x;
            double vert1_y = vert1->y;
            double vert1_z = vert1->z;

            double vert2_x = vert2->x;
            double vert2_y = vert2->y;
            double vert2_z = vert2->z;

            Point p0;
            p0.x = vert0_x;
            p0.y = vert0_y;
            p0.z = vert0_z;

            Point p1;
            p1.x = vert1_x;
            p1.y = vert1_y;
            p1.z = vert1_z;

            Point p2;
            p2.x = vert2_x;
            p2.y = vert2_y;
            p2.z = vert2_z;

            // random origin outside mesh
            Point orig_ray;
            orig_ray.x = 500;
            orig_ray.y = 500;
            orig_ray.z = 500;

            // calculate centroid of triangle
            Point centroid;
            centroid.x = (p0.x + p1.x + p2.x)/3;
            centroid.y = (p0.y + p1.y + p2.y)/3;
            centroid.z = (p0.z + p1.z + p2.z)/3;

            // map of [DISTANCE between centroid and ray's origin] = face
            dist_face_point[dist(centroid.x, centroid.y, centroid.z, orig_ray.x, orig_ray.y, orig_ray.z)] = *face;

            ++iterator;
            if (iterator == mesh.size()) {
                Vertex *v0 = dist_face_point.begin()->second.exteriorEdge->origin;
                Vertex *v1 = dist_face_point.begin()->second.exteriorEdge->destination;
                Vertex *v2 = dist_face_point.begin()->second.exteriorEdge->next->destination;

                Face* f_start = dist_face_point.begin()->second.exteriorEdge->incidentFace;
                // A = vert1 - vert0 ; B = vert2 - vert0
                double v0_x = v0->x;
                double v0_y = v0->y;
                double v0_z = v0->z;

                double v1_x = v1->x;
                double v1_y = v1->y;
                double v1_z = v1->z;

                double v2_x = v2->x;
                double v2_y = v2->y;
                double v2_z = v2->z;

                Point point0;
                point0.x = v0_x;
                point0.y = v0_y;
                point0.z = v0_z;

                Point point1;
                point1.x = v1_x;
                point1.y = v1_y;
                point1.z = v1_z;

                Point point2;
                point2.x = v2_x;
                point2.y = v2_y;
                point2.z = v2_z;

                // access the face with the smallest distance to ray's origin
                float volume = ((point0 - orig_ray).dot((point1 - orig_ray).cross(point2 - orig_ray))) / 6;

                if (volume > 0) {
                    iteration(f_start);
                } else {

                    Vertex *e_origin = dist_face_point.begin()->second.exteriorEdge->origin;
                    Vertex *e_dest = dist_face_point.begin()->second.exteriorEdge->destination;
                    std::swap(e_origin, e_dest);

                    Vertex *e1_origin = dist_face_point.begin()->second.exteriorEdge->prev->origin;
                    Vertex *e1_dest = dist_face_point.begin()->second.exteriorEdge->prev->destination;
                    std::swap(e1_origin, e1_dest);

                    Vertex *e2_origin = dist_face_point.begin()->second.exteriorEdge->next->origin;
                    Vertex *e2_dest = dist_face_point.begin()->second.exteriorEdge->next->destination;
                    std::swap(e2_origin, e2_dest);
                    iteration(f_start);
                }
            }
        }
    }
}


// 4.
void mergeCoPlanarFaces(DCEL& D) {
    // to do
}
// 5.
void exportCityJSON(DCEL& D, const char* file_out, std::vector<std::list<Face*>> meshes) {
    const auto& vertices = D.vertices();
    const auto& halfEdges = D.halfEdges();
    const auto& faces = D.faces();
    std::unordered_map<int, Point> vertexID;
    std::fstream fl;
    fl.open(file_out, std::fstream::in | std::fstream::out | std::fstream::trunc);

    //set the vertex vector that will be used for indexing
    int countv = 0;
    for (const auto& v : vertices) {
        Point VtoPoint;
        VtoPoint.x = float(v->x);
        VtoPoint.y = float(v->y);
        VtoPoint.z = float(v->z);
        vertexID[countv] = VtoPoint;
        countv++;
    }

    //write the general part
    fl << "{" << std::endl;
    fl << "\"type\": \"CityJSON\"," << std::endl;
    fl << "\"version\": \"1.0\"," << std::endl;
    fl << "\"CityObjects\": {" << std::endl;

    //write the cityobjects parts
    int idbuilding_count = 1;

    for (const auto& mesh : meshes) {
        fl << '\n' << "\"id-" << idbuilding_count << "\": {" << std::endl;
        fl << "\"type\": \"Building\", " << std::endl;
        fl << "\"geometry\": [{" << std::endl;
        fl << "\"type\": \"MultiSurface\"," << std::endl;
        fl << "\"lod\": 2," << std::endl;
        fl << "\"boundaries\": [" << std::endl;

        //write the boundaries using the index value from the vector created in the begin

        for (const auto& f : mesh) {

            //for (const auto& f : faces) {
            fl << "[[";
            Vertex* v0 = f->exteriorEdge->origin;
            Point VtoPoint;
            VtoPoint.x = float(v0->x);
            VtoPoint.y = float(v0->y);
            VtoPoint.z = float(v0->z);

            for (int i = 0; i < vertexID.size(); i++) {
                if (vertexID[i].x == VtoPoint.x && vertexID[i].y == VtoPoint.y && vertexID[i].z == VtoPoint.z) {
                    fl << i << ", ";
                }
            }

            Vertex* v1 = f->exteriorEdge->destination;
            VtoPoint.x = float(v1->x);
            VtoPoint.y = float(v1->y);
            VtoPoint.z = float(v1->z);

            for (int i = 0; i < vertexID.size(); i++) {
                if (vertexID[i].x == VtoPoint.x && vertexID[i].y == VtoPoint.y && vertexID[i].z == VtoPoint.z) {
                    fl << i << ", ";
                }
            }

            Vertex* v2 = f->exteriorEdge->next->destination;
            VtoPoint.x = float(v2->x);
            VtoPoint.y = float(v2->y);
            VtoPoint.z = float(v2->z);

            for (int i = 0; i < vertexID.size(); i++) {
                if (vertexID[i].x == VtoPoint.x && vertexID[i].y == VtoPoint.y && vertexID[i].z == VtoPoint.z) {
                    fl << i;
                }
            }
            fl << "]], ";
            //}
        }

        fl.seekp(-2, std::ios_base::end);
        fl << std::endl;
        fl << "]" << std::endl;
        fl << "}" << std::endl;
        fl << "]" << std::endl;

        //close the cityobjects
        fl << "},";
        idbuilding_count++;
    }
    fl.seekp(-1, std::ios_base::end);
    fl << '\n' << "}," << std::endl;

    //write the vertices using the index value from the vector created in the begin and close the json
    fl << "\"vertices\": [" << std::endl;

    for (const auto& v : vertices) {
        fl << "[" << float(v->x) << ", " << float(v->y) << ", " << float(v->z) << "]," << std::endl;
    }
    fl.seekp(-3, std::ios_base::end);
    fl << std::endl;
    fl << "]" << std::endl;
    fl << "}";

}

int main(int argc, const char* argv[]) {
    const char* file_in = "C:\\Users\\simon\\Desktop\\Stuff\\1. TU Delft\\2. Semester\\3. GEO1004 3D Modelling of the Built Environment\\2. Assignment\\hw2\\cube_soup.obj";
    const char* file_out = "C:\\Users\\simon\\Desktop\\Stuff\\1. TU Delft\\2. Semester\\3. GEO1004 3D Modelling of the Built Environment\\2. Assignment\\hw2\\soupchef\\cube.json";

    // create an empty DCEL
    DCEL D;

    // 1. read the triangle soup from the OBJ input file and convert it to the DCEL,
    importOBJ(D, file_in);
    printDCEL(D);
    const auto &faces = D.faces();

    // 2. group the triangles into meshes,
    std::vector<std::list<Face*>> meshes;
    createMeshes(D, meshes);

    // 3. determine the correct orientation for each mesh and ensure all its triangles 
    //    are consistent with this correct orientation (ie. all the triangle normals 
    //    are pointing outwards).
    orientMeshes(D, meshes);

    // 4. merge adjacent triangles that are co-planar into larger polygonal faces.

    // 5. write the meshes with their faces to a valid CityJSON output file.
    exportCityJSON(D, file_out,meshes);

    return 0;
}


void printDCEL(DCEL& D) {

    // Quick check if there is an invalid element
    auto element = D.findInValid();
    if (element == nullptr) {
        // Beware that a 'valid' DCEL here only means there are no dangling links and no elimated elements.
        // There could still be problems like links that point to the wrong element.
        std::cout << "DCEL is valid\n";
    }
    else {
        std::cout << "DCEL is NOT valid ---> ";
        std::cout << *element << "\n";
    }

    // iterate all elements of the DCEL and print the info for each element
    const auto& vertices = D.vertices();
    const auto& halfEdges = D.halfEdges();
    const auto& faces = D.faces();
    std::cout << "DCEL has:\n";
    std::cout << " " << vertices.size() << " vertices:\n";
    for (const auto& v : vertices) {
        std::cout << "  * " << *v << "\n";
    }
    std::cout << " " << halfEdges.size() << " half-edges:\n";
    for (const auto& e : halfEdges) {
        std::cout << "  * " << *e << "\n";
    }
    std::cout << " " << faces.size() << " faces:\n";
    for (const auto& f : faces) {
        std::cout << "  * " << *f << "\n";
    }

}


void DemoDCEL() {

    std::cout << "/// STEP 1 Creating empty DCEL...\n";
    DCEL D;
    printDCEL(D);

    /*

    v2 (0,1,0)
     o
     |\
     | \
     |  \
     o---o v1 (1,0,0)
    v0
    (0,0,0)

    We will construct the DCEL of a single triangle
    in the plane z=0 (as shown above).

    This will require:
      3 vertices
      6 halfedges (2 for each edge)
      1 face

    */
    std::cout << "\n/// STEP 2 Adding triangle vertices...\n";
    Vertex* v0 = D.createVertex(0, 0, 0);
    Vertex* v1 = D.createVertex(1, 0, 0);
    Vertex* v2 = D.createVertex(0, 1, 0);
    printDCEL(D);

    std::cout << "\n/// STEP 3 Adding triangle half-edges...\n";
    HalfEdge* e0 = D.createHalfEdge();
    HalfEdge* e1 = D.createHalfEdge();
    HalfEdge* e2 = D.createHalfEdge();
    HalfEdge* e3 = D.createHalfEdge();
    HalfEdge* e4 = D.createHalfEdge();
    HalfEdge* e5 = D.createHalfEdge();
    printDCEL(D);

    std::cout << "\n/// STEP 4 Adding triangle face...\n";
    Face* f0 = D.createFace();
    printDCEL(D);

    std::cout << "\n/// STEP 5 Setting links...\n";
    e0->origin = v0;
    e0->destination = v1;
    e0->twin = e3;
    e0->next = e1;
    e0->prev = e2;
    e0->incidentFace = f0;

    e3->origin = v1;
    e3->destination = v0;
    e3->twin = e0;
    e3->next = e5;
    e3->prev = e4;

    /*
    If a half-edge is incident to 'open space' (ie not an actual face with an exterior boundary),
    we use the infiniteFace which is predifined in the DCEL class
    */
    e3->incidentFace = D.infiniteFace();

    e1->origin = v1;
    e1->destination = v2;
    e1->twin = e4;
    e1->next = e2;
    e1->prev = e0;
    e1->incidentFace = f0;

    e4->origin = v2;
    e4->destination = v1;
    e4->twin = e1;
    e4->next = e3;
    e4->prev = e5;
    e4->incidentFace = D.infiniteFace();

    e2->origin = v2;
    e2->destination = v0;
    e2->twin = e5;
    e2->next = e0;
    e2->prev = e1;
    e2->incidentFace = f0;

    e5->origin = v0;
    e5->destination = v2;
    e5->twin = e2;
    e5->next = e4;
    e5->prev = e3;
    e5->incidentFace = D.infiniteFace();

    f0->exteriorEdge = e0;
    printDCEL(D);


    std::cout << "\n/// STEP 6 Traversing exterior vertices of f0...\n";
    /*
    if all is well in the DCEL, following a chain of half-edges (ie keep going to e.next)
    should lead us back the the half-edge where we started.
    */
    HalfEdge* e = f0->exteriorEdge;
    const HalfEdge* e_start = e;
    do {
        std::cout << " -> " << *e->origin << "\n";
        e = e->next;
    } while (e_start != e); // we stop the loop when e_start==e (ie. we are back where we started)


    std::cout << "\n/// STEP 7 eliminating v0...\n";
    v0->eliminate();
    printDCEL(D);

    /*
    We just eliminated v0. At the same time we know there are elements that still
    pointers to v0 (ie the edges e0, e2, e3, e5). This means we can NOT call D.cleanup()!
    If you do this anyways, the program may crash.

    Eg. if you uncomment the following there could be a crash/stall of the program.
    */
    // D.cleanup(); // this will remove v0 from memory (because we just eliminated v0 and the cleanup() function simply removes all the eliminated elements)
    // std::cout << *v0 << "\n"; // we try to access that memory, but v0 is gone -> undefined behaviour 
    // std::cout << *e0->origin << "\n"; // this equivalent to the previous line (both point to the same memory address)


    std::cout << "\n/// STEP 8 eliminating all the remaining DCEL elements\n";
    for (const auto& v : D.vertices()) {
        v->eliminate();
    }
    for (const auto& e : D.halfEdges()) {
        e->eliminate();
    }
    for (const auto& f : D.faces()) {
        f->eliminate();
    }
    printDCEL(D);

    std::cout << "\n/// STEP 9 cleaning up the DCEL\n";
    D.cleanup();
    printDCEL(D);

}