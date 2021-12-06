#include <iostream>
#include <fstream>
#include "vec3.hpp"
#include "ray.hpp"

float hit_sphere(const vec3 &center, float radius, const ray &r){
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0f * dot(oc, r.direction());
    float c = dot(oc, oc) - radius*radius;
    float discr = b*b - 4*a*c;
    if(discr < 0)
        return -1.0f;
    else
        return (-b - sqrt(discr))/(2.0f*a);
}

vec3 lerp(vec3 v0, vec3 v1, float t){
    //lerp -> 1-t * first vec + t * second vec
    return (1.0f-t) * v0 + t * v1;
}

vec3 color (const ray& r){
    float t = hit_sphere(vec3(0,0,-1), 0.5f, r);
    if(t > 0.0f){
        vec3 N = unit_vector(r.point_at_parameter(t) - vec3(0,0,-1));
        return 0.5*vec3(N.x()+1, N.y()+1, N.z()+1);
    }
    /*if (hit_sphere(vec3(0,0, 1), 0.5, r)) // small sphere placed at z=-1
        return vec3(1, 0, 0); // if true make color red of the sphere (means our ray hit to sphere)*/
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return lerp(vec3(1.0, 1.0, 1.0), vec3(0.5, 0.7, 1.0), t);
}

int main(){

   std::ofstream mfile;
   mfile.open("o.ppm");

   int nx = 200;
   int ny = 100;
   mfile << "P3 \n" << nx << " " << ny << "\n255\n";
   vec3 lower_left_corner(-2.0, -1.0, -1.0);
   vec3 horizontal (4.0, 0.0, 0.0);
   vec3 vertical (0.0, 2.0, 0.0);
   vec3 origin (0.0, 0.0, 0.0);

    for (int j = ny-1; j >= 0; --j){
        for (int i = 0; i < nx; ++i){
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r (origin, lower_left_corner + u*horizontal + v*vertical);
            vec3 col = color(r);
            int ir = int(255.99 * col[0]);
            int ig = int (255.99 * col[1]);
            int ib = int (255.99 * col[2]);

            mfile << ir << " " << ig << " " << ib << "\n";
        }
    }
    mfile.close();
}
