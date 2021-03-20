#include <iostream>
#include <map>
#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <assert.h>
//#include <bits/stdc++.h>

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


/*
  Example functions that you could implement. But you are
  free to organise/modify the code however you want.
  After each function you should have a DCEL without invalid elements!
*/
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
void faceinfection(HalfEdge* a, Vertex* o, Vertex* d, int i, std::unordered_map<Face*, int> fmap) {
    if (
        a->origin == o &&
        a->destination == d) {
        fmap[a->incidentFace] = i + 1;
    }
    else if (
        a->origin == d &&
        a->destination == o) {
        fmap[a->incidentFace] = i + 1;
    }
    else if (
        a->next->origin == o &&
        a->next->destination == d) {
        fmap[a->incidentFace] = i + 1;
    }
    else if (
        a->next->origin == d &&
        a->next->destination == o) {
        fmap[a->incidentFace] = i + 1;
    }
    else if (
        a->prev->origin == o &&
        a->prev->destination == d) {
        fmap[a->incidentFace] = i + 1;
    }
    else if (
        a->prev->origin == d &&
        a->prev->destination == o) {
        fmap[a->incidentFace] = i + 1;
    }
}

void groupTriangles(DCEL& D) {
    const auto& vertices = D.vertices();
    const auto& halfEdges = D.halfEdges();
    const auto& faces = D.faces();

    std::unordered_map<Face*, int> fmap;
    //std::unordered_map<Vertex*, Vertex*> nextfacemap;
    //std::unordered_map<pair, Vertex*, pair_hash> nextfacemap;

    for (const auto& f : faces) {

        // add that if marked to not go iterate over that face

        // initiate the marking counter that eventually makes sure that only the most recently marked faces are selected 
        // in the rest of the iteration proces
        int i = 1;

        // mark the first face in the facelist 
        fmap[f->exteriorEdge->incidentFace] = 0;

        // starting with the first face in the facelist
        // put the origin and destination of the first halfedge in a map
        // in both directions to not exclude dangling halfedges as a result of an incorrect orientated face
        Vertex* o1 = f->exteriorEdge->origin;
        Vertex* d1 = f->exteriorEdge->destination;
        //nextfacemap[o1] = d1;
        //nextfacemap[d1] = o1;

        Vertex* o2 = f->exteriorEdge->next->origin;
        Vertex* d2 = f->exteriorEdge->next->destination;
        //nextfacemap[o2] = d2;
        //nextfacemap[d2] = o2;

        Vertex* o3 = f->exteriorEdge->prev->origin;
        Vertex* d3 = f->exteriorEdge->prev->destination;
        //nextfacemap[o3] = d3;
        //nextfacemap[d3] = o3;

        // go to the next face that borders every halfedge
        for (const auto& f : faces) {
            HalfEdge* a = f->exteriorEdge;
            if (fmap[f->exteriorEdge->incidentFace] == NULL) {
                // try face neighbouring on side o1-d1
                faceinfection(a, o1, d1, i, fmap);
                // try face neighbouring on side o2-d2
                faceinfection(a, o2, d2, i, fmap);
                // try face neighbouring on side o3-d3
                faceinfection(a, o3, d3, i, fmap);
            }


                
                // try face neighbouring on side o1-d1
                if (
                    f->exteriorEdge->origin == o1 &&
                    f->exteriorEdge->destination == d1 ) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->origin == d1 &&
                    f->exteriorEdge->destination == o1 ) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->next->origin == o1 &&
                    f->exteriorEdge->next->destination == d1 ) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->next->origin == d1 &&
                    f->exteriorEdge->next->destination == o1 ) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->prev->origin == o1 &&
                    f->exteriorEdge->prev->destination == d1) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->prev->origin == d1 &&
                    f->exteriorEdge->prev->destination == o1) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }

                // try face neighbouring on side o2-d2
                else if (
                    f->exteriorEdge->origin == o2 &&
                    f->exteriorEdge->destination == d2) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->origin == d2 &&
                    f->exteriorEdge->destination == o2) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->next->origin == o2 &&
                    f->exteriorEdge->next->destination == d2) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->next->origin == d2 &&
                    f->exteriorEdge->next->destination == o2) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->prev->origin == o2 &&
                    f->exteriorEdge->prev->destination == d2) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->prev->origin == d2 &&
                    f->exteriorEdge->prev->destination == o2) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }

                // try face neighbouring on side o3-d3
                else if (
                    f->exteriorEdge->origin == o3 &&
                    f->exteriorEdge->destination == d3) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->origin == d3 &&
                    f->exteriorEdge->destination == o3) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->next->origin == o3 &&
                    f->exteriorEdge->next->destination == d3) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->next->origin == d3 &&
                    f->exteriorEdge->next->destination == o3) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->prev->origin == o3 &&
                    f->exteriorEdge->prev->destination == d3) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                else if (
                    f->exteriorEdge->prev->origin == d3 &&
                    f->exteriorEdge->prev->destination == o3) {
                    fmap[f->exteriorEdge->incidentFace] = i + 1;
                }
                
        }




            /*
            the incident face of the memory location
            of the twin = 

            the incident face of the memory location
            of e0 of the next face

            //only if correctly orientated!

            so the memory location of the incident face
            is always the next face

            //mark as checked_i
            //
            map[incidentface*] = checked
        f->exteriorEdge->next->twin
            //mark as checked_i
        f->extoriorEdge->prev->twin
            //mark as checked_i

        //for every face marked as checked_i
        f->exteriorEdge->twin
            //if marked == NULL {
            //mark as checked_i+1 }
            //else {break}
        f->exteriorEdge->next->twin
            //if marked == NULL {
            //mark as checked_i+! }
            //else { break }
        f->extoriorEdge->prev->twin
            //if marked == NULL {
            //mark as checked1_i+1 }
            //else { break }

            //i++
                */
    }

}

// 3.
float dist(float x, float y, float z, float a, float b, float c){
    return sqrt(pow(x - a, 2) + pow(y - b, 2)+pow(z - c, 2));
}

void orientMeshes(DCEL& D) {
    const auto &vertices = D.vertices();
    const auto &halfEdges = D.halfEdges();
    const auto &faces = D.faces();
    std::unordered_map<float, Face> dist_face_point;

    /*
        for (const auto &h : halfEdges) {

        Vertex *vert0 = h->origin;
        Vertex *vert1 = h->destination;
        Vertex *vert2 = h->next->destination;
     */

    int iterator = 0;
    for (const auto &f : faces) {

        Vertex *vert0 = f->exteriorEdge->origin;
        Vertex *vert1 = f->exteriorEdge->destination;
        Vertex *vert2 = f->exteriorEdge->next->destination;

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

        Vertex A = Vertex(vert1_x - vert0_x, vert1_y - vert0_y, vert1_z - vert0_z);
        Vertex B = Vertex(vert2_x - vert0_x, vert2_y - vert0_y, vert2_z - vert0_z);

        double nx = A.y * B.z - A.z * B.y;
        double ny = A.z * B.x - A.x * B.z;
        double nz = A.x * B.y - A.y * B.x;

        Vertex nor = Vertex((nx), (ny), (nz));

        // magnitude of n
        double mag_n = sqrt((nx * nx) + (ny * ny) + (nz * nz));

        // normalize
        Vertex normal = Vertex((nx / mag_n), (ny / mag_n), (nz / mag_n));

        Point norm;
        norm.x = nor.x;
        norm.y = nor.y;
        norm.z = nor.z;

        Point orig_ray;
        orig_ray.x = 0;
        orig_ray.y = 0;
        orig_ray.z = 0;

        // calculate centroid of triangle
        Vertex centroid = Vertex((vert0_x + vert0_y + vert0_z)/3,
                                 (vert1_x + vert1_y + vert1_z)/3,
                                 (vert2_x + vert2_y + vert2_z)/3);

        // map of [DISTANCE between centroid and ray's origin] = face
        dist_face_point[dist(centroid.x, centroid.y, centroid.z, orig_ray.x, orig_ray.y, orig_ray.z)] = *f;

        ++iterator;
        if (iterator == faces.size()){
            Vertex *v0 = dist_face_point.begin()->second.exteriorEdge->origin;
            Vertex *v1 = dist_face_point.begin()->second.exteriorEdge->destination;
            Vertex *v2 = dist_face_point.begin()->second.exteriorEdge->next->destination;

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

            float smallest_dist = dist_face_point.begin()->first;
            float volume = ((point0 - orig_ray).dot((point1 - orig_ray).cross(point2 - orig_ray))) / 6;

            std::cout << "\n" << "VOLUME " << volume;
            std::cout << "\n" << "SMALLEST DISTANCE to centroid " << smallest_dist ;
            std::cout << "\n" << "DISTANCE to vertex " << dist(p0.x, p0.y, p0.z, orig_ray.x, orig_ray.y, orig_ray.z);

            if(volume > 0){
                //ACCESS h and navigate to twins
            }
            else{continue;}

        }
        //std::cout << "\n" <<   "\n" << "VERT A    " << A << " Vert B  " << B << " mag: "<< mag_n << " n " << nor;
        //std::cout << "\n" << "VERT Normal    " << norm;

    }
}


// 4.
void mergeCoPlanarFaces(DCEL& D) {
    // to do
}
// 5.


void exportCityJSON(DCEL& D, const char* file_out) {
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

    fl << "\"id-" << idbuilding_count << "\": {" << std::endl;
    fl << "\"type\": \"Building\", " << std::endl;
    fl << "\"geometry\": [{" << std::endl;
    fl << "\"type\": \"MultiSurface\"," << std::endl;
    fl << "\"lod\": 2," << std::endl;
    fl << "\"boundaries\": [" << std::endl;

    //write the boundaries using the index value from the vector created in the begin 
    for (const auto& f : faces) {
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
    }

    fl.seekp(-2, std::ios_base::end);
    fl << std::endl;
    fl << "]" << std::endl;
    fl << "}" << std::endl;
    fl << "]" << std::endl;

    //close the cityobjects
    fl << "}" << std::endl;
    fl << "}," << std::endl;

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
    const char* file_in = "C:\\Users\\simon\\Desktop\\Stuff\\1. TU Delft\\2. Semester\\3. GEO1004 3D Modelling of the Built Environment\\2. Assignment\\hw2\\cube.obj";
    const char* file_out = "C:\\Users\\simon\\Desktop\\Stuff\\1. TU Delft\\2. Semester\\3. GEO1004 3D Modelling of the Built Environment\\2. Assignment\\hw2\\soupchef\\cube.json";

    // create an empty DCEL
    DCEL D;

    // 1. read the triangle soup from the OBJ input file and convert it to the DCEL,
    importOBJ(D, file_in);
    printDCEL(D);

    // 2. group the triangles into meshes,

    // 3. determine the correct orientation for each mesh and ensure all its triangles 
    //    are consistent with this correct orientation (ie. all the triangle normals 
    //    are pointing outwards).
    orientMeshes(D);

    // 4. merge adjacent triangles that are co-planar into larger polygonal faces.

    // 5. write the meshes with their faces to a valid CityJSON output file.
    exportCityJSON(D, file_out);

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