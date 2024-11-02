#include "../lib/tm_usage.h"
#include <cstring>
#include <fstream>
#include <iostream>
#include "mps.h"
using namespace std;

void help_message() { cout << "please check proper usage"; }

int main(int argc, char *argv[]) {
  if (argc != 3) {
    help_message();
    return 0;
  }
  CommonNs::TmUsage tmusg;
  CommonNs::TmStat stat;

  //////////// read the input file /////////////

  // char buffer[200];
  fstream fin(argv[1]);
  // fstream fin;
  // fin.open(argv[1]);
  fstream fout;
  fout.open(argv[2], ios::out);
  // fin.getline(buffer, 200);
  // fin.getline(buffer, 200);
  int n; 
  fin >> n;
  MPS mps(n);
  int num1, num2;
  for(int i = 0; i < n / 2; i++){
    fin >> num1 >> num2;
    mps.add(num1, num2);
  }
  fin >> num1;
  if(num1 != 0){
    cout << "input error!\n";
    return 0;
  }

  //////////// main part ////////////////
  tmusg.periodStart();
  mps.print(fout);
  tmusg.getPeriodUsage(stat);
  cout << "The total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms"
       << endl;
  cout << "memory: " << stat.vmPeak << "KB" << endl; // print peak memory

  //////////// write the output file ///////////
  // fout << "# " << data.size() << " data points" << endl;
  // fout << "# index number" << endl;
  // for (int i = 0; i < data.size(); i++)
  //   fout << i << " " << data[i] << endl;
  fin.close();
  fout.close();
  return 0;
}
