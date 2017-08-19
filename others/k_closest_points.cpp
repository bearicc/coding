/* 
 * Given some points and a point origin in two dimensional space, find k points out of the some points which are nearest to origin.
 * Return these points sorted by distance, if they are same with distance, sorted by x-axis, otherwise sorted by y-axis.
 * 
 * Have you met this question in a real interview? Yes
 * Example
 * Given points = [[4,6],[4,7],[4,4],[2,5],[1,1]], origin = [0, 0], k = 3
 * return [[1,1],[2,5],[4,4]]
 * 
 */

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    vector<Point> kClosest(vector<Point>& points, Point& origin, int k) {
        auto compare = [&](const Point& a, const Point& b) {
            int dist1 = dist(a, origin), dist2 = dist(b, origin);
            if (dist1 == dist2) {
                return a.x - b.x;
            }
            return dist1 - dist2;
        };
        // auto compare = [&](const Point& a, const Point& b) {
        //     int dist1 = dist(a, origin), dist2 = dist(b, origin);
        //     if (dist1 == dist2) {
        //         return a.x < b.x;
        //     }
        //     return dist1 < dist2;
        // };
        // auto it = points.begin() + k;
        // nth_element(points.begin(), it, points.end(), compare);
        quickselect(points, 0, (int)points.size()-1, k, compare);
        vector<Point> ret(points.begin(), points.begin() + k);
        sort(ret.begin(), ret.end(), [&](const Point& a, const Point& b) {
            int dist1 = dist(a, origin), dist2 = dist(b, origin);
            return dist1 < dist2 || dist1 == dist2 && a.x < b.x;
        });
        return ret;
    }
private:
    int dist(const Point& a, const Point& b) {
        return (a.x - b.x) * (a.x - b.x) +
               (a.y - b.y) * (a.y - b.y);
    }
    template<typename T>
    void quickselect(vector<Point>& points, int begin, int end, int k, T& compare) {
        if (begin > end) return;
        int i = begin, j = end;
        Point pivot = points[i + (j - i) / 2];
        while (i <= j) {
            while (i <= j && compare(points[i], pivot) < 0) {
                ++i;
            }
            while (i <= j && compare(points[j], pivot) > 0) {
                --j;
            }
            if (i <= j) {
                swap(points[i++], points[j--]);
            }
        }
        if (begin + k - 1 <= j) {
            quickselect(points, begin, j, k, compare);
        } else if (begin + k -1 >= i) {
            quickselect(points, i, end, k - (i - begin), compare);
        }
    }
    // void quickselect(vector<Point>& points, int begin, int end, int k, T& compare) {
    //      int i = begin, j = begin;
    //      while (i < end) {
    //          if (compare(points[i], points[end])) {
    //              swap(points[j++], points[i]);
    //          }
    //          ++i;
    //      }
    //      swap(points[j], points[end]);
    //      if (k == j) {
    //          return;
    //      } else if (k < j) {
    //          quickselect(points, begin, j-1, k, compare);
    //      } else {
    //          quickselect(points, j+1, end, k, compare);
    //      }
    // }
};
