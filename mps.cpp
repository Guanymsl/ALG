#include "mps.h"
#include <algorithm>
#include <csetjmp>
#include <cstddef>
#include <iostream>

#define SHORT_MAX 0xffff

MPS::MPS(int n) {
  size =  n;
  adj = new int[size];
  dp_table_1 = new unsigned short*[size];
  if(size < SHORT_MAX * 2){
    for(int i = 0; i < size; i++){
      dp_table_1[i] = new unsigned short[size - i];
    }
    for(int i = 0; i < size; i++){
      for(int j = 0; j < size - i; j++){
        dp_table_1[i][j] = SHORT_MAX;
      }
    }
  }
  else{
    for(int i = 0; i < size; i++){
      dp_table_1[i] = new unsigned short[std::min(size - i, SHORT_MAX * 2 - 1)];
    }
    for(int i = 0; i < size; i++){
      for(int j = 0; j < std::min(size - i, SHORT_MAX * 2 - 1); j++) dp_table_1[i][j] = SHORT_MAX;
    }
    dp_table_2 = new int*[size - SHORT_MAX * 2 + 1];
    for(int i = 0; i <= size - SHORT_MAX * 2; i++){
      dp_table_2[i] = new int[size - SHORT_MAX * 2 + 1 - i];
    }
    for(int i = 0; i <= size - SHORT_MAX * 2; i++){
      for(int j = 0; j < size - SHORT_MAX * 2 - i + 1; j++){
        dp_table_2[i][j] = -1;
      }
    }
  }
}

void MPS::add(int a, int b) {
  adj[a] = b;
  adj[b] = a;
}

int MPS::calc(int i, int j){
  if(i >= j) return 0;
  if(j - i < int(SHORT_MAX) * 2 - 1){
    if(dp_table_1[i][j - i] != int(SHORT_MAX)) return dp_table_1[i][j - i];
  }
  else{
    if(dp_table_2[i][j - i - 2 * SHORT_MAX + 1] != -1) return dp_table_2[i][j - i - 2 * SHORT_MAX + 1];
  }

  int connected_point = adj[j];
  if(j - i < SHORT_MAX * 2 - 1){
    if(connected_point > j || connected_point < i){
      dp_table_1[i][j - i] = calc(i, j - 1);
      return dp_table_1[i][j - i];
    }
    else{
      if(connected_point == i){
        dp_table_1[i][j - i] = calc(i + 1, j - 1) + 1;
        return dp_table_1[i][j - i];
      }
      else{
        dp_table_1[i][j - i] = std::max(calc(i, j - 1), calc(i, connected_point - 1) + calc(connected_point + 1, j) + 1);
        return dp_table_1[i][j - i];
      }
    }
  }
  else{
    if(connected_point > j || connected_point < i){
      dp_table_2[i][j - i - SHORT_MAX * 2 + 1] = calc(i, j - 1);
      return dp_table_2[i][j - i - SHORT_MAX * 2 + 1];
    }
    else{
      if(connected_point == i){

        dp_table_2[i][j - i - SHORT_MAX * 2 + 1] = calc(i + 1, j - 1) + 1;
        return dp_table_2[i][j - i - SHORT_MAX * 2 + 1];
      }
      else{
        // std::cout << "branch 8";
        dp_table_2[i][j - i - SHORT_MAX * 2 + 1] = std::max(calc(i, j - 1), calc(i, connected_point - 1) + calc(connected_point + 1, j) + 1);
        return dp_table_2[i][j - i - SHORT_MAX * 2 + 1];
      }
    }
  }
}

int MPS::run_dp(){
  return calc(0, size - 1);
}

void MPS::find_prt(int i, int j){
  if(i >= j) return;
  int connected_point = adj[j];
  if(connected_point > j || connected_point < i){
    find_prt(i, j - 1);
  }
  else{
    if(connected_point == i){
      answer.push_back(i);
      find_prt(i + 1, j - 1);
    }
    else{
      // if(dp_table_1[i][j - i] == dp_table[i][j - i - 1]){
      //   find_prt(i, j - 1);
      // }
      if(calc(i, j) == calc(i, j - 1)){
        find_prt(i, j - 1);
      }
      else{
        answer.push_back(connected_point);
        find_prt(i, connected_point - 1);
        find_prt(connected_point + 1, j - 1);
      }
    }
  }
}

void MPS::print(std::fstream &fout){
  int ans = run_dp();
  // std::cout << "finish run_dp()" << std::endl;
  find_prt(0, size - 1);
  std::cout << ans << std::endl;
  std::cout << answer.size() << std::endl;
  fout << ans << std::endl;
  sort(answer.begin(), answer.end());
  for(int i = 0; i < answer.size(); i++){
    std::cout << answer[i] << ' ' << adj[answer[i]] << std::endl;
    fout << answer[i] << ' ' << adj[answer[i]] << std::endl;
  }
}

MPS::~MPS() {
  for(int i = 0; i < size; i++){
    delete[] dp_table_1[i];
  }
  delete[] dp_table_1;
  if(size >= SHORT_MAX * 2){
    for(int i = 0; i <= size - SHORT_MAX * 2; i++){
      delete[] dp_table_2[i];
    }
    delete[] dp_table_2;
  }
  delete[] adj;
}
