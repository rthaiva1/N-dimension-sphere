#include <random>
#include <vector>
#include <algorithm>
#include <iostream>
#include <map>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <math.h>
#include <cmath>
#include "matplotlibcpp.h"
namespace plt =matplotlibcpp;

int main(int argc, char **argv) {
  if (argc != 2)
  {
      std::fprintf(stderr, "./sphere <points>\n");
      std::exit(1);
  }
  int n_points=atoi(argv[1]);
  std::vector<std::vector<float>> x, y, z;
  std::map<float, int> plot;
  for(int a=1;a<=100;a++)
  {
    float interval = (float)a/100;
    plot.insert(std::pair<float, int>(interval,0));//Initalize count to 0
  }
    float distance;
    float temp;
    std::default_random_engine eng;
    std::uniform_real_distribution<float> dist(-1, 1);
    for(int i=0;i<n_points;i++)
    {
      std::vector<float> x_row, y_row, z_row;
      while(1)
      {
        distance=0.0;
        float temp1,temp2;
        for(int j=0; j<3;j++)
        {

          temp=dist(eng);
          if(j==0)
          {
            x_row.push_back(temp);
            temp1=temp;
          }
          if(j==1)
          {
            y_row.push_back(temp);
            temp2=temp;
          }
          if(j==2)
          {
            z_row.push_back(::std::sin(::std::hypot(temp1,temp2)));
          }
          distance=distance+temp*temp;
          if((j==2) && (distance>1))
          {
            x_row.pop_back();
            y_row.pop_back();
            z_row.pop_back();
          }
        }
        if(distance<=1.0)
        {
            plot[std::floor((sqrt(distance)*100)+0.5)/100]++;
            break;
        }
      }
      x.push_back(x_row);
      y.push_back(y_row);
      z.push_back(z_row);
  }
  std::for_each(plot.begin(),plot.end(),[](const std::pair<float, int> &p)
  {
        std::cout << "{" << p.first << ": " << p.second << "}\n";
  });
  plt::plot_surface(x, y, z);
  plt::show();
    struct rusage ru;
    int rv = getrusage(RUSAGE_SELF, &ru); assert(rv == 0);
    auto cv = [](const timeval &tv) {
        return double(tv.tv_sec) + double(tv.tv_usec)/1000000;
    };
    std::cerr << "Resource Usage:\n";
    std::cerr << "    User CPU Time: " << cv(ru.ru_utime) << '\n';
    std::cerr << "    Sys CPU Time: " << cv(ru.ru_stime) << '\n';
    std::cerr << "    Max Resident: " << ru.ru_maxrss << '\n';
    std::cerr << "    Page Faults: " << ru.ru_majflt << '\n';
}
