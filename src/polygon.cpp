#include "polygon.hpp"


Poly::Poly(list<Point> points) {
    verticies.insert(verticies.end(), points.begin(), points.end());

    float x_sum = 0.0, y_sum = 0.0;
    int num_verticies = (float) verticies.size();

    for (auto it = verticies.begin(); it != verticies.end(); it++) {
        x_sum += it->getX();
        y_sum += it->getY();
    }

    center.setX(x_sum / num_verticies);
    center.setY(y_sum / num_verticies);
}

bool Poly::is_type(string name) {
    if (name == "Poly")
        return true;
    return false;
}

vector<Point>& Poly::get_verticies() {

    return verticies;
}

bool Poly::detection(float mx, float my) {
    int cont = 0, n = this->verticies.size();

    for (int i = 0, j = n - 1; i < n; j = i++) {
        float xi = this->verticies[i].getX();
        float yi = this->verticies[i].getY();
        float xj = this->verticies[j].getX();
        float yj = this->verticies[j].getY();

        if (((yi > my) != (yj > my))) {

            float x_intersection; 
            if (yj != yi) x_intersection=(xj - xi) * (my - yi) / (yj - yi) + xi;
            if (mx < x_intersection) {
                cont++;
            }
        }
    }
    if (cont%2 == 0){
        return false;
    }
    else{
        return true;
    }
}

Point Poly::get_center() {
    return this->center;
}

list<Point> Poly::get_points() {
    list<Point> listpoints(verticies.begin(), verticies.end());

    return listpoints;
}

void Poly::set_points(list<Point> new_points) {
    verticies.clear();
    verticies.assign(new_points.begin(), new_points.end());

    float x_sum = 0, y_sum = 0;
    for (auto &p : verticies) {
        x_sum += p.getX();
        y_sum += p.getY();
    }
    center.setX(x_sum / verticies.size());
    center.setY(y_sum / verticies.size());
}


void Poly::set_vertices(const std::vector<Point>& novosVertices) {
    verticies = novosVertices;

    // Recalcula o centro do polígono
    float x_sum = 0.0f, y_sum = 0.0f;
    for (const auto& p : verticies) {
        x_sum += p.getX();
        y_sum += p.getY();
    }
    if (!verticies.empty()) {
        center.setX(x_sum / verticies.size());
        center.setY(y_sum / verticies.size());
    }
}