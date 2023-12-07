//
// Created by tmai42 on 12/7/23.
//

#ifndef SCENE_HPP
#define SCENE_HPP

#include "IHittable.hpp"

#include <memory>
#include <vector>

class Scene : public IHittable {
public:

    bool CheckHit(const Ray& ray_to_check, const Interval<double> &distance_interval, HitResult& record) const override {
        bool hit_anything = false;
        auto closest_so_far = distance_interval.GetGetUpperBound();

        for (const auto& object : m_hittable_objects) {
            if (object->CheckHit(ray_to_check, Interval{distance_interval.GetLowerBound(), closest_so_far}, record)) {
                hit_anything = true;
                closest_so_far = record.t;
            }
        }

        return hit_anything;
    }

    void AddObject(std::shared_ptr<IHittable> hittable_object) {
        m_hittable_objects.emplace_back(hittable_object);
    }

    void Clear() {
        m_hittable_objects.clear();
    }

private:

    //TODO: try to rewrite in more compact way, mb using pre-allocated memory to keep objects more compact
    std::vector<std::shared_ptr<IHittable>> m_hittable_objects;

};


#endif //SCENE_HPP
