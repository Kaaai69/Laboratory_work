#include <iostream>
#include <cmath>

using std::cout;
int main()
{    
    double x1, x2, x3, x4, y1, y2, y3, y4, z1, z2, z3, z4;
    cout << "Введите координаты точки A: ";
    std::cin >> x1 >> y1 >> z1;
    cout << "Введите координаты точки B: ";
    std::cin >> x2 >> y2 >> z2;
    cout << "Введите координаты точки C: ";
    std::cin >> x3 >> y3 >> z3;
    cout << "Введите координаты точки D: ";
    std::cin >> x4 >> y4 >> z4;
    
    double m11 = x1, m12 = y1, m13 = z1, m14 = 1;
    double m21 = x2, m22 = y2, m23 = z2, m24 = 1;
    double m31 = x3, m32 = y3, m33 = z3, m34 = 1;
    double m41 = x4, m42 = y4, m43 = z4, m44 = 1;
    
    double d1 = -(std::pow(x1, 2) + std::pow(y1, 2) + std::pow(z1, 2));
    double d2 = -(std::pow(x2, 2) + std::pow(y2, 2) + std::pow(z2, 2));
    double d3 = -(std::pow(x3, 2) + std::pow(y3, 2) + std::pow(z3, 2));
    double d4 = -(std::pow(x4, 2) + std::pow(y4, 2) + std::pow(z4, 2));

    double det = m11 * (m22*(m33*m44 - m34*m43) - m23*(m32*m44 - m34*m42) + m24*(m32*m43 - m33*m42))
               - m12 * (m21*(m33*m44 - m34*m43) - m23*(m31*m44 - m34*m41) + m24*(m31*m43 - m33*m41))
               + m13 * (m21*(m32*m44 - m34*m42) - m22*(m31*m44 - m34*m41) + m24*(m31*m42 - m32*m41))
               - m14 * (m21*(m32*m43 - m33*m42) - m22*(m31*m43 - m33*m41) + m23*(m31*m42 - m32*m41));

    double det1 = d1 * (m22*(m33*m44 - m34*m43) - m23*(m32*m44 - m34*m42) + m24*(m32*m43 - m33*m42))
                - m12 * (d2*(m33*m44 - m34*m43) - m23*(d3*m44 - m34*d4) + m24*(d3*m43 - m33*d4))
                + m13 * (d2*(m32*m44 - m34*m42) - m22*(d3*m44 - m34*d4) + m24*(d3*m42 - m32*d4))
                - m14 * (d2*(m32*m43 - m33*m42) - m22*(d3*m43 - m33*d4) + m23*(d3*m42 - m32*d4));
    
    double det2 = m11 * (d2*(m33*m44 - m34*m43) - m23*(d3*m44 - m34*d4) + m24*(d3*m43 - m33*d4))
                - d1 * (m21*(m33*m44 - m34*m43) - m23*(m31*m44 - m34*m41) + m24*(m31*m43 - m33*m41))
                + m13 * (m21*(d3*m44 - m34*d4) - d2*(m31*m44 - m34*m41) + m24*(m31*d4 - d3*m41))
                - m14 * (m21*(d3*m43 - m33*d4) - d2*(m31*m43 - m33*m41) + m23*(m31*d4 - d3*m41));
    
    double det3 = m11 * (m22*(d3*m44 - m34*d4) - d2*(m32*m44 - m34*m42) + m24*(m32*d4 - d3*m42))
                - m12 * (m21*(d3*m44 - m34*d4) - d2*(m31*m44 - m34*m41) + m24*(m31*d4 - d3*m41))
                + d1 * (m21*(m32*m44 - m34*m42) - m22*(m31*m44 - m34*m41) + m24*(m31*m42 - m32*m41))
                - m14 * (m21*(m32*d4 - d3*m42) - m22*(m31*d4 - d3*m41) + d2*(m31*m42 - m32*m41));
    
    double det4 = m11 * (m22*(m33*d4 - d3*m43) - m23*(m32*d4 - d3*m42) + d2*(m32*m43 - m33*m42))
                - m12 * (m21*(m33*d4 - d3*m43) - m23*(m31*d4 - d3*m41) + d2*(m31*m43 - m33*m41))
                + m13 * (m21*(m32*d4 - d3*m42) - m22*(m31*d4 - d3*m41) + d2*(m31*m42 - m32*m41))
                - d1 * (m21*(m32*m43 - m33*m42) - m22*(m31*m43 - m33*m41) + m23*(m31*m42 - m32*m41));
    
    double A = det1 / det;
    double B = det2 / det;
    double C = det3 / det;
    double D = det4 / det;
    cout << "Уравнение сферы: x² + y² + z² + (" << A << ")x + (" << B << ")y + (" << C << ")z + (" << D << ") = 0" << "\n";
    return 0;
}