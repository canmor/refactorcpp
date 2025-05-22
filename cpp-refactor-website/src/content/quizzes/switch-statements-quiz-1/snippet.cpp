#include <iostream>
#include <string>
#include <vector>
#include <memory>

enum class ShapeType {
    CIRCLE,
    RECTANGLE,
    TRIANGLE,
    SQUARE,
    HEXAGON
};

class Shape {
private:
    ShapeType type;
    double dimension1; // Could be radius, width, side length, etc.
    double dimension2; // Could be height, another side length, etc.

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
            case ShapeType::SQUARE:
                return dimension1 * dimension1;
            case ShapeType::HEXAGON:
                return (3 * std::sqrt(3) * dimension1 * dimension1) / 2.0;
            default:
                return 0.0;
        }
    }

    double calculatePerimeter() const {
        switch (type) {
            case ShapeType::CIRCLE:
                return 2 * 3.14159 * dimension1;
            case ShapeType::RECTANGLE:
                return 2 * (dimension1 + dimension2);
            case ShapeType::TRIANGLE:
                // Assuming dimension1 is base and dimension2 is height
                // This is a simplification as we'd need the third side
                double hypotenuse = std::sqrt(dimension1 * dimension1 / 4 + dimension2 * dimension2);
                return dimension1 + 2 * hypotenuse;
            case ShapeType::SQUARE:
                return 4 * dimension1;
            case ShapeType::HEXAGON:
                return 6 * dimension1;
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
            case ShapeType::SQUARE:
                std::cout << "Drawing a square with side length " << dimension1 << std::endl;
                break;
            case ShapeType::HEXAGON:
                std::cout << "Drawing a hexagon with side length " << dimension1 << std::endl;
                break;
            default:
                std::cout << "Unknown shape type." << std::endl;
        }
    }
};

class ShapeFactory {
public:
    static std::unique_ptr<Shape> createShape(ShapeType type, double d1, double d2 = 0.0) {
        return std::make_unique<Shape>(type, d1, d2);
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
            case ShapeType::SQUARE:
                renderSquare(shape.getDimension1());
                break;
            case ShapeType::HEXAGON:
                renderHexagon(shape.getDimension1());
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

    void renderSquare(double side) {
        std::cout << "Rendering square with OpenGL..." << std::endl;
    }

    void renderHexagon(double side) {
        std::cout << "Rendering hexagon with OpenGL..." << std::endl;
    }
};

class ShapeExporter {
public:
    std::string exportToSVG(const Shape& shape) {
        switch (shape.getType()) {
            case ShapeType::CIRCLE:
                return generateCircleSVG(shape.getDimension1());
            case ShapeType::RECTANGLE:
                return generateRectangleSVG(shape.getDimension1(), shape.getDimension2());
            case ShapeType::TRIANGLE:
                return generateTriangleSVG(shape.getDimension1(), shape.getDimension2());
            case ShapeType::SQUARE:
                return generateSquareSVG(shape.getDimension1());
            case ShapeType::HEXAGON:
                return generateHexagonSVG(shape.getDimension1());
            default:
                return "<!-- Unknown shape type -->";
        }
    }

private:
    std::string generateCircleSVG(double radius) {
        return "<circle cx=\"50\" cy=\"50\" r=\"" + std::to_string(radius) + "\" />";
    }

    std::string generateRectangleSVG(double width, double height) {
        return "<rect width=\"" + std::to_string(width) + "\" height=\"" + std::to_string(height) + "\" />";
    }

    std::string generateTriangleSVG(double base, double height) {
        // Simplified triangle SVG
        return "<polygon points=\"0,0 " + std::to_string(base) + ",0 " + 
               std::to_string(base/2) + "," + std::to_string(height) + "\" />";
    }

    std::string generateSquareSVG(double side) {
        return "<rect width=\"" + std::to_string(side) + "\" height=\"" + std::to_string(side) + "\" />";
    }

    std::string generateHexagonSVG(double side) {
        // Simplified hexagon SVG
        return "<polygon points=\"...\" />"; // Points would be calculated based on side length
    }
};

int main() {
    // Create shapes
    std::vector<std::unique_ptr<Shape>> shapes;
    
    shapes.push_back(ShapeFactory::createShape(ShapeType::CIRCLE, 5.0));
    shapes.push_back(ShapeFactory::createShape(ShapeType::RECTANGLE, 4.0, 6.0));
    shapes.push_back(ShapeFactory::createShape(ShapeType::TRIANGLE, 8.0, 4.0));
    shapes.push_back(ShapeFactory::createShape(ShapeType::SQUARE, 3.0));
    shapes.push_back(ShapeFactory::createShape(ShapeType::HEXAGON, 2.0));
    
    ShapeRenderer renderer;
    ShapeExporter exporter;
    
    // Process all shapes
    for (const auto& shape : shapes) {
        // Draw the shape
        shape->draw();
        
        // Calculate and display area
        std::cout << "Area: " << shape->calculateArea() << std::endl;
        
        // Calculate and display perimeter
        std::cout << "Perimeter: " << shape->calculatePerimeter() << std::endl;
        
        // Render the shape
        renderer.renderShape(*shape);
        
        // Export to SVG
        std::string svg = exporter.exportToSVG(*shape);
        std::cout << "SVG: " << svg << std::endl;
        
        std::cout << "------------------------" << std::endl;
    }
    
    return 0;
}
