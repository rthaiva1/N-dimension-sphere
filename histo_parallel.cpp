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

  if (argc != 4)
  {
      std::fprintf(stderr, "./sphere <points> <dimensions> <threads>\n");
      std::exit(1);
  }
  int n_points=atoi(argv[1]);
  int dim=atoi(argv[2]);
  int threads=atoi(argv[3]);
  omp_set_num_threads(threads);
  std::map<float, int> plot;
  for(int a=1;a<=100;a++)
  {
    float interval = (float)a/100;
    plot.insert(std::pair<float, int>(interval,0));//Initalize count to 0
  }
  int divide = (n_points/threads);
  #pragma omp parallel
  {
    float distance;
    float temp;
    std::default_random_engine eng;
    std::uniform_real_distribution<float> dist(-1, 1);
    for(int i=0;i<divide;i++)
    {
      while(1)
      {
        distance=0.0;
        for(int j=0; j<dim;j++)
        {
          temp=dist(eng);
          distance=distance+temp*temp;
          if(distance>1)
          {
            j=dim;
          }
        }
        if(distance<=1.0)
        {
            plot[std::floor((sqrt(distance)*100)+0.5)/100]++;
            break;
        }
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
