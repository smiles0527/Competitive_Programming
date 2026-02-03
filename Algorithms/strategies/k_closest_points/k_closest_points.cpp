#include <bits/stdc++.h>

using namespace std;

#pragma once

#include <vector>

/**
 * Represents a point in 2D space
 */
struct Point {
    int x;
    int y;
    
    Point(int x = 0, int y = 0) : x(x), y(y) {}
};

/**
 * Find the K closest points to the origin (0, 0).
 * Distance is calculated using Euclidean distance.
 * 
 * @param points Vector of points
 * @param k Number of closest points to return
 * @return Vector of the K closest points to the origin
 */
std::vector<Point> kClosestPoints(std::vector<Point>& points, int k);


// Implementation

// Helper function to calculate squared distance from origin
static int squaredDistance(const Point& p) {
    return p.x * p.x + p.y * p.y;
}

std::vector<Point> kClosestPoints(std::vector<Point>& points, int k) {
    if (k <= 0) return {};
    if (k >= static_cast<int>(points.size())) return points;
    
    // Use partial_sort for O(n log k) complexity
    std::partial_sort(points.begin(), points.begin() + k, points.end(),
        [](const Point& a, const Point& b) {
            return squaredDistance(a) < squaredDistance(b);
        });
    
    return std::vector<Point>(points.begin(), points.begin() + k);
}

