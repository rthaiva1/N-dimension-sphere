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
#include <omp.h>
#include <cmath>

int main(int argc, char **argv) {

  if (argc != 3)
  {
      std::fprintf(stderr, "./sphere <points> <dimensions>\n");
      std::exit(1);
  }
  int n_points=atoi(argv[1]);
  int dim=atoi(argv[2]);
  std::map<float, int> plot;
  for(int a=1;a<=100;a++)
  {
    float interval = (float)a/100;
    plot.insert(std::pair<float, int>(interval,0));//Initalize count to 0
  }
    float distance;
    int i,j;
    std::default_random_engine eng;
    std::uniform_real_distribution<float> radius(0, 1);
    std::uniform_real_distribution<float> angle(0, 360);
    for(i=0;i<n_points;i++)
    {
      while(1)
      {
        float temp1,temp2=1.0;
        distance=0.0;
        for(j=0; j<dim;j++)
        {
          if(j==0)
          {
            temp1=angle(eng);
            distance=pow(radius(eng)*cos(temp1),2);
          }
          if(j==(dim-1))
          {
            temp2=temp2*sin(temp1);
            temp1=angle(eng);
            distance=distance+pow(radius(eng)*temp2*sin(temp1),2);
          }
          else
          {
            temp2=temp2*sin(temp1);
            temp1=angle(eng);
            distance=distance+pow(radius(eng)*temp2*cos(temp1),2);
          }
        }
        distance=sqrt(distance);
        if(distance<=1.0)
        {
            plot[std::floor((distance*100)+0.5)/100]++;
            break;
        }
      }
  }
  printf("Total points printed:%d\n",n_points);
  std::for_each(plot.begin(),plot.end(),[](const std::pair<float, int> &p)
  {
        std::cout << "{" << p.first << ": " << p.second << "}\n";
  });
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
