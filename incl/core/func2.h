#pragma once
#include "core/arr.h"

//Func Exts
#define ARG(...) __VA_ARGS__
#define func(RetT,fname,...) function<RetT(__VA_ARGS__)> fname=[&](__VA_ARGS__)->RetT
#define lam(expr,...) [&](__VA_ARGS__){return expr;}

template<class T,class U>bool assmin(T& a,U&& b){return a>b?a=b,true:false;}
template<class T,class U>bool assmax(T& a,U&& b){return a<b?a=b,true:false;}
template<class T>int argmin(const Arr<T>& a){return min_element(a.begin(),a.end())-a.begin();}
template<class T>int argmax(const Arr<T>& a){return max_element(a.begin(),a.end())-a.begin();}
Arr<int> range(int n){Arr<int> r;while(n--)r.pushb(sz(r));return r;}
template<class T>Arr<pair<int,T>> enumer(const Arr<T>& a){
	Arr<pair<int,T>> r;
	for(auto&i:a)r.pushb(sz(r),i);
	return r;
}
Arr<int> permuinv(const Arr<int>& a){
	Arr<int> r(sz(a));
	for(auto [i,v]:enumer(a))r[v]=i;
	return r;
}
Arr<Arr<int>> occur(const Arr<int>& a){
	Arr<Arr<int>> r(*max_element(a.begin(),a.end()));
	for(auto [i,v]:enumer(a))r[v].pushb(i);
	return r;
}