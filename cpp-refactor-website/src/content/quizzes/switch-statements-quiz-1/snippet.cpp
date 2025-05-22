#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum class ShapeType {
    CIRCLE,
    RECTANGLE,
    TRIANGLE
};

class Shape {
private:
    ShapeType type;
    double dimension1; // Could be radius, width, side length
    double dimension2; // Could be height

public:
    Shape(ShapeType type, double d1, double d2 = 0.0) 
        : type(type), dimension1(d1), dimension2(d2) {}

    ShapeType getType() const { return type; }
    double getDimension1() const { return dimension1; }
    double getDimension2() const { return dimension2; }

    double calculateArea() const {
        switch (type) {
            case ShapeType::CIRCLE:
                return 3.14159 * dimension1 * dimension1;
            case ShapeType::RECTANGLE:
                return dimension1 * dimension2;
            case ShapeType::TRIANGLE:
                return 0.5 * dimension1 * dimension2;
            default:
                return 0.0;
        }
    }

    void draw() const {
        switch (type) {
            case ShapeType::CIRCLE:
                std::cout << "Drawing a circle with radius " << dimension1 << std::endl;
                break;
            case ShapeType::RECTANGLE:
                std::cout << "Drawing a rectangle with width " << dimension1 
                          << " and height " << dimension2 << std::endl;
                break;
            case ShapeType::TRIANGLE:
                std::cout << "Drawing a triangle with base " << dimension1 
                          << " and height " << dimension2 << std::endl;
                break;
            default:
                std::cout << "Unknown shape type." << std::endl;
        }
    }
};

class ShapeRenderer {
public:
    void renderShape(const Shape& shape) {
        switch (shape.getType()) {
            case ShapeType::CIRCLE:
                renderCircle(shape.getDimension1());
                break;
            case ShapeType::RECTANGLE:
                renderRectangle(shape.getDimension1(), shape.getDimension2());
                break;
            case ShapeType::TRIANGLE:
                renderTriangle(shape.getDimension1(), shape.getDimension2());
                break;
            default:
                std::cout << "Cannot render unknown shape type." << std::endl;
        }
    }

private:
    void renderCircle(double radius) {
        std::cout << "Rendering circle with OpenGL..." << std::endl;
    }

    void renderRectangle(double width, double height) {
        std::cout << "Rendering rectangle with OpenGL..." << std::endl;
    }

    void renderTriangle(double base, double height) {
        std::cout << "Rendering triangle with OpenGL..." << std::endl;
    }
};

class ShapeExporter {
public:
    std::string exportToSVG(const Shape& shape) {
        switch (shape.getType()) {
            case ShapeType::CIRCLE:
                return "<circle cx=\"50\" cy=\"50\" r=\"" + std::to_string(shape.getDimension1()) + "\" />";
            case ShapeType::RECTANGLE:
                return "<rect width=\"" + std::to_string(shape.getDimension1()) + 
                       "\" height=\"" + std::to_string(shape.getDimension2()) + "\" />";
            case ShapeType::TRIANGLE:
                return "<polygon points=\"0,0 " + std::to_string(shape.getDimension1()) + 
                       ",0 " + std::to_string(shape.getDimension1()/2) + "," + 
                       std::to_string(shape.getDimension2()) + "\" />";
            default:
                return "<!-- Unknown shape type -->";
        }
    }
};

int main() {
    std::vector<std::unique_ptr<Shape>> shapes;
    
    shapes.push_back(std::make_unique<Shape>(ShapeType::CIRCLE, 5.0));
    shapes.push_back(std::make_unique<Shape>(ShapeType::RECTANGLE, 4.0, 6.0));
    shapes.push_back(std::make_unique<Shape>(ShapeType::TRIANGLE, 8.0, 4.0));
    
    ShapeRenderer renderer;
    ShapeExporter exporter;
    
    for (const auto& shape : shapes) {
        shape->draw();
        std::cout << "Area: " << shape->calculateArea() << std::endl;
        renderer.renderShape(*shape);
        std::string svg = exporter.exportToSVG(*shape);
        std::cout << "SVG: " << svg << std::endl;
        std::cout << "------------------------" << std::endl;
    }
    
    return 0;
}
