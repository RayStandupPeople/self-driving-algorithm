#include "quintic_polynomial_curve1d.h"
#include <iostream>
#include <vector>
#include <memory>
#include "dp_path.h"
#include "box2d.h"

/*
* plot - plot the map with gnuplot
* 
* @param path: the path with needed to be plot.
* @param
* 
* @ return: noting 
*/
void plot(const std::vector<SlPoint> &path){

    char*gnuplotPath = "gnuplot";
    FILE* gp = popen(gnuplotPath,"w");
    if (gp == NULL)
    {
        std::cout<<("Cannotopen gnuplot!\n")<<std::endl;;
        return ;
        //exit(0);
    }
    fprintf(gp,"plot cos(x)\n");
    // fprintf(gp,"plot sin(x)\n");
    fprintf(gp,"pause mouse\n");//用户点击后退出
    pclose(gp);

}
int main(){
     
    std::shared_ptr<DpPath> dp_path_ = nullptr;
    std::vector<std::vector<SlPoint>> sample_points_;
    std::vector<Box2d> obstacles_;
   
    Box2d obs1({3, -0.5}, 0.0, 0.8, 1.5);
    Box2d obs2({12, 0.5}, 0.0, 0.8, 1.5);
    obstacles_.emplace_back(obs1);
    obstacles_.emplace_back(obs2);
    
    SlPoint vehicle_position(0.0, 0.0);
    sample_points_.emplace_back(std::vector<SlPoint>{vehicle_position});
    for (double s = 3; s < 20; s += 3) {
      std::vector<SlPoint> level_points;
      for (double l = -1.5; l < 2.0; l += 0.5) {
        level_points.emplace_back(s, l);
      }
      sample_points_.emplace_back(level_points);
    }
  
    dp_path_ = std::make_shared<DpPath>(sample_points_, obstacles_);
    std::vector<SlPoint> path;

    bool ret = dp_path_->Search(&path);
    std::cout << "res:" << ret << std::endl;;
    std::cout << "path :" << std::endl;

    for(int i=1;i<2;++i)
    {
      std::cout << "current point: " <<path[i].s << " "<< path[i].l;
      QuinticPolynomialCurve1d curv(path[i-1].l,0,0,path[i].l,0,0,path[i].s-path[i-1].s);
      std::cout << ", l(i-1), l(i), s: " << path[i-1].l << path[i].l << path[i].s-path[i-1].s;
      std::cout <<"  : " << curv.Coef(5) <<" " << curv.Coef(4)<<" "<< curv.Coef(3)<<" "<< curv.Coef(2)<<" "<<curv.Coef(1) <<" "<<curv.Coef(0);
      std::cout << "l at s(3) with order 5 : " << curv.Evaluate(0,3);
      std::cout << std::endl;

    }
    std::cout << std::endl;
    plot(path);


}