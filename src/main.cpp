
#include "hittables/Sphere.hpp"
#include "hittables/Scene.hpp"
#include "Camera.hpp"

int main() {

    // Scene
    Scene scene;
    scene.AddObject(std::make_shared<Sphere>(Point3D (0,0,-1), 0.5));
    scene.AddObject(std::make_shared<Sphere>(Point3D (0,-100.5,-1), 100));
    scene.AddObject(std::make_shared<Sphere>(Point3D (3,0,-3), 2));

    // Render
    Camera::GetCamera()->Render(scene);

}
