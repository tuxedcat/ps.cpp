#pragma once
#include "Core.h"

template<typename T>
Str<T> itos(int i){
	if(!i)
		return "0";
	Str<T> ret;
	while(i)
		ret.push_back(i%10+'0'), i/=10;
	reverse(ret.begin(), ret.end());
	return ret;
}

//a.k.a. partial match table, pi
template<typename T>
Arr<int> failure_function(const Str<T> &p) {
	Arr<int> ret(sz(p));
	int si = 1, pi = 0;
	int psz=sz(p);
	while (si + pi < psz) {
		if (pi < psz && p[si + pi] == p[pi]) {
			pi++;
			ret[si + pi - 1] = pi;
		}
		else {
			if (!pi)
				++si;
			else {
				si += pi - ret[pi - 1];
				pi = ret[pi - 1];
			}
		}
	}
	return ret;
}

template<typename T>
Arr<int> failure_function2(const Str<T> &p) {
	int pi = 0;
	Arr<int> ret(sz(p));
	hfor(i, 1, sz(p)) {
		while (pi > 0 && p[i] != p[pi])
			pi = ret[pi - 1];
		if (p[i] == p[pi])
			ret[i] = ++pi;
	}
	return ret;
}

//return: full matched pattern's start indexs
template<typename T>
Arr<int> kmp(const Str<T> &s, const Str<T> &p) {
	int ssz=sz(s);
	int psz=sz(p);
	if (ssz < psz)
		return {};
	Arr<int> ret;
	auto ff = failure_function(p);
	int si = 0, pi = 0;
	while (si <= ssz - psz) {
		if (pi < psz && s[si + pi] == p[pi]) {
			if (++pi == psz)
				ret.push_back(si);
		}
		else {
			if (!pi)
				++si;
			else {
				si += pi - ff[pi - 1];
				pi = ff[pi - 1];
			}
		}
	}

	return ret;
}

//return: partial matched length of that index
template<typename T>
Arr<int> kmp2(const Str<T> &s, const Str<T> &p) {
	const auto &ff = failure_function2(p);
	Arr<int> ans(sz(s));
	int pi = 0;
	hfor(i, 0, sz(s)) {
		while (pi > 0 && s[i] != p[pi])
			pi = ff[pi - 1];
		if (s[i] == p[pi] && (ans[i] = ++pi) == sz(p))
			pi = ff[pi - 1];
	}
	return ans;
}

bool cmp(int i, int j, const Arr<int> &g, int t){
	if(g[i]==g[j])
		return g[i+t] < g[j+t];
	return g[i]<g[j];
}

//sa[i]: 사전순으로 i번째인 접미사의 시작인덱스
template<typename T>
Arr<int> suffix_array(const Str<T> &s){
	int n = sz(s);
	Arr<int> sa(n), ord(n+1), nord(n+1);
	hfor(i, 0, sz(s))
		sa[i]=i, ord[i]=s[i];

	ord[n]=-1;
	for(int i=1;i<n;i*=2){
		sort(sa.begin(), sa.end(), [&](const int &a, const int &b){return cmp(a, b, ord, i);});
		nord[sa[0]]=0;
		nord[n]=-1;
		hfor(j, 1, n)
			nord[sa[j]]=nord[sa[j-1]]+cmp(sa[j-1], sa[j], ord, i);
		ord=nord;
	}
	return sa;
}

//lcp[i]: 사전순 i번째 접미사와 i−1번째 접미사의 가장 긴 공통 접두사의 길이
//plzrun's code
template<typename T>
Arr<int> get_lcp(const Str<T> &s, const Arr<int> &sa){
	int n = sz(s);
	Arr<int> lcp(n), psa(n+1), plcp(n+1);
	psa[sa[0]]=-1;
	hfor(i,1,n)
	psa[sa[i]]=sa[i-1];
	int common=0;
	hfor(i,0,n){
		if(psa[i]==-1)
			plcp[i]=0;
		else{
			while(s[i+common] == s[psa[i] + common])
				common++;
			plcp[i]=common;
			common = max(common-1,0);
		}
	}
	hfor(i,0,n)
		lcp[i]=plcp[sa[i]];
	return lcp;
}

//jh05013's code, O(NlogN)
template<typename T>
Arr<int> suffix_array2(const Str<T> &s){
	int n = sz(s), c = 0;
	Arr<int> temp(n), pos2bckt(n), bckt(n), bpos(n), out(n);
	for(int i=0; i<n; i++) out[i] = i;
	sort(out.begin(), out.end(), [&](int a, int b){return s[a] < s[b];});
	for(int i=0; i<n; i++) {
		bckt[i] = c;
		if (i + 1 == n || s[out[i]] != s[out[i + 1]]) c++;
	}
	for (int h = 1; h < n && c < n; h <<= 1) {
		for (int i=0; i<n; i++) pos2bckt[out[i]] = bckt[i];
		for (int i=n-1; i>=0; i--) bpos[bckt[i]] = i;
		for (int i=0; i<n; i++) if (out[i] >= n-h)
			temp[bpos[bckt[i]]++] = out[i];
		for (int i=0; i<n; i++) if (out[i] >= h)
			temp[bpos[pos2bckt[out[i] - h]]++] = out[i] - h;
		c = 0;
		hfor(i,0,n-1){
			int a=bckt[i]!=bckt[i+1] || temp[i]>=n-h || pos2bckt[temp[i+1]+h]!=pos2bckt[temp[i]+h];
			bckt[i]=c;
			c+=a;
		}
		bckt[n-1]=c++;
		temp.swap(out);
	}
	return out;
}

//comet's code
template<typename T>
Arr<int> get_lcp2(const Str<T> &s, const Arr<int> &sa){
	int h=0;
	int n=sz(s);
	Arr<int> rank(n);
	hfor(i, 0, sz(sa))
		rank[sa[i]]=i;
	Arr<int> lcp(n);
	hfor(i,0,n){
		if(rank[i]){
			int j=sa[rank[i]-1];
			while(s[i+h]==s[j+h])
				h++;
			lcp[rank[i]]=h;
		}
		h -= !!h;
	}
	return lcp;
}