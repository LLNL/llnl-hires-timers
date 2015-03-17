#include <unistd.h>
#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <hires-timers.h>

using namespace std;

void measure_fixed_sleep_seconds(int seconds) {
  cout << "Measuring sleep time." << endl;
  timing_t start = get_time_ns();
  sleep(seconds);
  timing_t end = get_time_ns();
  double measured = (end - start) / 1e9;

  cout << "  Slept:    " << seconds  << " sec" << endl;
  cout << "  Measured: " << measured << " sec" << endl;
}


void measure_minimum_ns_between_call(int iterations) {
  assert(iterations > 0);
  cout << "Timer Statistics over " << iterations << " iterations:"  << endl;
  vector<timing_t> times(iterations);

  for (int i=0; i < iterations; i++) {
    timing_t start = get_time_ns();
    timing_t end   = get_time_ns();
    times.push_back(end - start);
  }

  std::sort(times.begin(), times.end());
  timing_t total  = accumulate(times.begin(), times.end(), 0);
  timing_t total2 = inner_product(times.begin(), times.end(), times.begin(), 0);

  cout << "  Min:     " << times.front()                     << " ns" << endl;
  cout << "  Max:     " << times.back()                      << " ns" << endl;
  cout << "  Mean:    " << total / (double) times.size()     << " ns" << endl;
  cout << "  Median:  " << times[times.size() / 2]           << " ns" << endl;
  cout << "  StdDev:  " << sqrt(total2 / (times.size() - 1)) << " ns" << endl;
}

int main(int argc, char **argv) {
  cout << "Starting tests." << endl;
  measure_fixed_sleep_seconds(2);
  cout << endl;

  measure_minimum_ns_between_call(10000);
  cout << endl;

  cout << "Done." << endl;
}
