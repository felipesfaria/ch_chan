#include <iostream>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <CGAL/ch_jarvis.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;

using namespace std;
int main()
{
  Point_2 points[5] = { Point_2(0,0), Point_2(10,0), Point_2(10,10), Point_2(6,5), Point_2(4,1) };
  Point_2 result[5];
  Point_2 *ptr = CGAL::ch_graham_andrew( points, points+5, result );
  //Point_2 *ptr = CGAL::ch_jarvis( points, points+5, result );
  std::cout <<  ptr - result << " points on the convex hull" << std::endl;
	for(Point_2 *i = result; i != ptr ; ++i){
		std::cout << (*i) << std::endl;
	}
  return 0;
}
