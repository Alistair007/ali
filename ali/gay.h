#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <memory>
using namespace std;

#define start int main(){
#define end }
#define iff if(
#define do ){
#define is ==
#define not !
#define isnot !=
#define elif } else iff
#define var auto
#define pointer *
#define referenceof &
#define dereference *
#define deref(x) *x
#define def auto
#define func {
#define say std::cout <<
#define sayl(text) std::cout << #text "\n"
#define saytoo <<
#define ask std::cin >>
#define forr(name) for (size_t name = 0
#define fortimes(times) for (size_t __priv = 0; __priv < times; __priv++){
#define addelement(e) .push_back(e);
#define at(i) [i] 

// For big boys only
#define arr(T) std::vector<T>
#define smartptr(T) std::unique_ptr<T>
#define hash(rT) std::map<const char*, rT>

// Renamed functions
void(*print)(const char*, ...) = (void (*)(const char*, ...))printf;