#include <iostream>
#include <cmath>
#include <QVector>

class Vector2D {
    // 构造函数
    Vector2D(double angle = 0.0, double v = 0.0) : angle(angle), v(v) {}
    // 将速度垂直分解
    QVector<Vector2D> velocity_decomposing(double horizontal_angle) {
        int integer_part = static_cast<int>(horizontal_angle);
        double decimal_part = horizontal_angle - static_cast<double>(integer_part); // 转为int和小数部分
        double vertical_angle = (integer_part+90) % 360 + decimal_part;
    }
private:
    double angle;
    double v;
};

int main() {
    // 创建两个速度向量对象
    Vector2D v1(0, 1.0);  // 向量v1的x分量和y分量分别为1.0


    return 0;
}
