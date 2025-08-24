#include "line.hpp"
#include <list>

Line::Line(Point primeiro, Point segundo): p1(primeiro), p2(segundo) {}

bool Line::is_type(string name) {
    if (name == "Line")
        return true;
    return false;
}

bool Line::detection(float mx, float my) {
    int t=5; // tolerância
    float px1 = this->p1.getX(), px2 = this->p2.getX(), py1 = this->p1.getY(), py2 = this->p2.getY();//Cordenadas dos pontos da linha
    
    for(int i = 0; i<4; i++){

        if(((px1<mx-t and px2<mx-t) or (px1>mx+t and px2>mx+t)) and ((py1<my-t and py2<my-t) or (py1>my+t and py2>my+t))){
            return false;
        }
        else if (((px1 >= mx-t and px1 <= mx) and (py1 >= my-t and py1 <= my+t)) or ((px2 >= mx-t and px2 <= mx) and (py2 >= my-t and py2 <= my+t))){
            return true;
        }
        else{
            if (px1 < mx-t){
                if (px2-px1) py1 += (mx-t - px1)*(py2-py1)/(px2-px1);
                px1 = mx-t;

            }
            else if (px1 > mx+t){
                if (px2-px1) py1 += (mx+t - px1)*(py2-py1)/(px2-px1);
                px1 = mx+t;
                
            }
            else if(py1 < my-t){
                if (py2-py1)px1 += (my-t - py1)*(px2-px1)/(py2-py1);
                py1 = my-t;
            }
            else if(py1 > my+t){
                if (py2-py1) px1 += (my+t - py1)*(px2-px1)/(py2-py1);
                py1 = my+t;
            }
            else{
                return true;
            }
        }
    }
    return false;
}

Point Line::getp1() {
    return p1;
}

Point Line::getp2(){
    return p2;
}

Point Line::get_center() {
    float xm = (this->getp1().getX() + this->getp2().getX()) / 2.0;
    float ym = (this->getp1().getY() + this->getp2().getY()) / 2.0;
    return Point(xm, ym);
}
    
list<Point> Line::get_points() {
    return list<Point>{this->getp1(), this->getp2()};
}

void Line::set_points(list<Point> new_points) {
    for (int i = 0; i < 3; i++) {
        this->p1.set(i, new_points.front().get(i));
        this->p2.set(i, new_points.back().get(i));
    }
}