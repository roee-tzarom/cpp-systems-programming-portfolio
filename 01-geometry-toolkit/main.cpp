#include "Point.hpp"
#include "Circle.hpp"
#include "Utilities.hpp"
#include <iostream>

using namespace std;
using namespace Geometry;
using namespace Utils;

int main() {
    cout << "=== Demonstration of Point Functions ===" << endl;
    
    // Creating and printing points
    Point p1 = {3.0, 4.0};
    Point p2 = {1.0, 2.0};
    
    cout << "p1: ";
    printPoint(p1);
    // Expected output: (3,4)
    cout << endl;
    
    cout << "p2: ";
    printPoint(p2);
    // Expected output: (1,2)
    cout << endl;
    
    // Calculate and print the distance between two points
    double dist = distance(p1, p2);
    cout << "Distance between p1 and p2: " << dist << endl;
    // Expected output: Distance between p1 and p2: 2.82843
    
    cout << "\n=== Demonstration of findClosestToOrigin Function ===" << endl;
    
    // Create additional points and store them in an array
    Point points[] = {
        {5.0, 5.0},
        {1.0, 1.0},
        {-3.0, 4.0},
        {2.0, -2.0}
    };
    
    // Demonstrate the use of findClosestToOrigin function
    Point closest = findClosestToOrigin(points, 4);
    cout << "Closest point to origin: ";
    printPoint(closest);
    // Expected output: (1,1)
    cout << endl;
    
    cout << "\n=== Demonstration of Circle Functions ===" << endl;
    
    // Create circles using createCircle function
    Circle c1 = createCircle(0, 0, 5);
    Circle c2 = createCircle(2, 3, 10);
    
    // Print the circles
    cout << "Circle 1: ";
    printCircle(c1);
    // Expected output: Circle: center=(0,0), radius=5
    cout << endl;
    
    cout << "Circle 2: ";
    printCircle(c2);
    // Expected output: Circle: center=(2,3), radius=10
    cout << endl;
    
    // Demonstrate the calculation of area and circumference of a circle
    double area1 = calculateArea(c1);
    double circumference1 = calculateCircumference(c1);
    
    cout << "Circle 1 area: " << area1 << endl;
    // Expected output: Circle 1 area: 78.5398
    
    cout << "Circle 1 circumference: " << circumference1 << endl;
    // Expected output: Circle 1 circumference: 31.4159
    
    // Check if certain points are inside a circle
    Point testPoint1 = {3, 4};
    Point testPoint2 = {6, 6};
    
    cout << "\nIs point (3,4) inside circle 1? " 
         << (isPointInside(c1, testPoint1) ? "Yes" : "No") << endl;
    // Expected output: Is point (3,4) inside circle 1? Yes
    
    cout << "Is point (6,6) inside circle 1? " 
         << (isPointInside(c1, testPoint2) ? "Yes" : "No") << endl;
    // Expected output: Is point (6,6) inside circle 1? No
    
    cout << "\n=== Demonstration of calculateAverage Function ===" << endl;
    
    // Demonstrate the use of calculateAverage function with an array
    double numbers[] = {10.5, 20.3, 15.7, 8.9, 12.6};
    double average = calculateAverage(numbers, 5);
    
    cout << "Average of numbers: " << average << endl;
    // Expected output: Average of numbers: 13.6
    
    cout << "\n=== End of Demonstration ===" << endl;
    
    return 0;
}