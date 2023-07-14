//
// Created by top on 2023-07-14.
//

#include "Object_category.h"
#include <utility>
Object_category:: ~Object_category() {
    delete polygon_object;
    // 根据需要删除其他类型的子类对象
}
void Object_category::add_object() {
    if (polygon_object != nullptr){
        polygon_object->add_object();
    }
}

int Object_category::size() {
    if (polygon_object != nullptr){
        polygon_object->size();
    }
}

// ------------------------------------------------------------------
Ball_class :: ~Ball_class() {
    balls.clear();  // 清空 balls 容器
}

Ball_class :: Ball_class() : Object_category(), balls(){}

Ball_class :: Ball_class(Ball* const ball) : Object_category(), balls()
{
    balls.push_back(ball);
}
Ball_class::Ball_class(QRectF rect, Velocity2D ball_v) {
    balls.push_back(new Ball(rect,std::move(ball_v)));
}
Ball_class :: Ball_class(QVector<Ball*>& some_balls) : Object_category(), balls()
{
    balls.append(some_balls);
}

void Ball_class :: add_object(const QRectF rect, Velocity2D ball_v) {
    balls.push_back(new Ball(rect,std::move(ball_v)));
}
void Ball_class :: add_object(Ball *ball) {
    balls.push_back(ball);
}
QVector<Ball*>& Ball_class :: get_objects(){
    return balls;
}

int Ball_class :: size() {
    return balls.size();
}

Ball& Ball_class :: operator[](int index) {
    if (index >= 0 && index < balls.size()) {
        return *balls[index];
    } else {
        throw std :: out_of_range("Ball_class:: 索引越界！");
    }
}



//---------------------------------------------------------------------------------------------

Ball :: Ball(const QRectF rect, Velocity2D ball_v):
        ball_rect(rect),
        rad(rect.width()/2),
        m(rect.width()/2),
        ball_v(std::move(ball_v)),
        color(generateRandomColor()){
    ball_cent = rect.center();
}

void Ball :: coordinate_change_df(const QPointF &dpf){
    ball_rect.translate(dpf);
    ball_cent = ball_rect.center();
    trace_push(ball_cent);
}

void Ball :: set_v(Velocity2D &v){
    ball_v = v;
}

QColor Ball :: generateRandomColor()
{
    int red = qrand() % 256;
    int green = qrand() % 256;
    int blue = qrand() % 256;
    return QColor::fromRgb(red, green, blue);
}

void Ball :: trace_push(QPointF &p){
    if (trace_queue.size() == len_trace_queue){
        trace_queue.dequeue();
        trace_queue.enqueue(p);
    } else{
        trace_queue.enqueue(p);
    }
}

//  --------------------------------------------------------------------------------------------

Polygon_boundary_class :: ~Polygon_boundary_class(){
    rect_polygons.clear();
}
Polygon_boundary_class :: Polygon_boundary_class() {

}

Polygon_boundary_class :: Polygon_boundary_class(Rect_boundary *rect_bound) {
    rect_polygons.push_back(rect_bound);
}

Polygon_boundary_class :: Polygon_boundary_class(QVector<Rect_boundary *>& some_rect_bounds) {
    rect_polygons.append(some_rect_bounds);
}

void Polygon_boundary_class :: add_rect_polygon(Rect_boundary *rect_bound) {
    rect_polygons.push_back(rect_bound);
}

void Polygon_boundary_class :: add_rect_polygon(const QVector<QPointF *> &coordinates) {
    rect_polygons.push_back(new Rect_boundary(coordinates));
}

QVector<Rect_boundary *> &Polygon_boundary_class :: get_objects() {
    return rect_polygons;
}

Rect_boundary &Polygon_boundary_class :: operator[](int index) {
    if (index >= 0 && index < rect_polygons.size()) {
        return *rect_polygons[index];
    } else {
        throw std::out_of_range("Polygon_boundary_class:: 索引越界！");
    }
}

int Polygon_boundary_class::size(){
    return rect_polygons.size();
}

//  --------------------------------------------------------------------------------------------

Rect_boundary :: Rect_boundary(const QVector<QPointF*>& coordinates) {
    for (auto c : coordinates){
        polygon<<*c;
    }
}

Rect_boundary::~Rect_boundary() {
    for (auto point : polygon) {
        delete &point;
    }
}

QPolygonF &Rect_boundary::get_polygon() {
    return polygon;
}
QPointF& Rect_boundary:: operator[](int index){
    if (index >= 0 && index < polygon.size()) {
        return polygon[index];
    } else {
        throw std::out_of_range("Rect_boundary:: 索引越界！");
    }
}


int Rect_boundary::size() {
    return polygon.size();
}
