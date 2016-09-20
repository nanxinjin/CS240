#include <iostream>
#include "problem_classes.h"

void test1() {
    std::cout << "Creating Triangle of Base=3 and Height=4" << std::endl;
    Triangle *tri = new Triangle(3, 4);
    std::cout << "Area of Triangle: " << tri->getArea() << std::endl;
}

void test2()
{
    std::cout << "Creating Triangle of Base=4 and Height=9" << std::endl;
    Triangle tri(4, 9);
    std::cout << "Area of Triangle: " << tri.getArea() << std::endl;

    std::cout << std::endl;
   
    std::cout << "Creating Square of sideLenghth=4" << std::endl;
    Square square(4);
    std::cout << "Area of Square: " << square.getArea() << std::endl;

    std::cout << std::endl;

    std::cout << "Creating Circle of radius=16" << std::endl;
    Circle circle(16);
    std::cout << "Area of Circle: " << circle.getArea() << std::endl;
}

void test3()
{
    // Polymporphism!
    int n = 3;
    Shape ** shapes = new Shape*[n];
    std::cout << "Creating Triangle of Base=7 and Height=9" << std::endl;
    shapes[0] = new Triangle(7, 9);
    std::cout << "Creating Square of sideLenghth=6" << std::endl;
    shapes[1] = new Square(6);
    std::cout << "Creating Circle of radius=7" << std::endl;
    shapes[2] = new Circle(7);
    std::cout << std::endl;
    
    std::cout << "Finding the area of each Shape..." << std::endl;
    for (int i = 0; i < n; ++i) {
	std::cout << shapes[i]->getArea() << std::endl;
    }
}

int main( int argc, char ** argv ) {
    if ( argc < 2 ) {
	std::cout << "Usage: test_array test1|test2|test3|test4|test5|test6" << std::endl;
	exit(1);
    }

    std::string test = argv[1];

    std::cout << "Running " << test << std::endl;

    if ( test == "test1" ) {
	test1();
    }
    else if ( test == "test2" ) {
	test2();
    }
    else if ( test == "test3" ) {
	test3();
    }
    else {
	std::cout << "Test not Found!" << std::endl;
	exit(1);
    }
}
