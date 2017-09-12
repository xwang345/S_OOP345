//Shan Zhang, 113004154
#pragma once
template<typename K, typename V, int N>

class KVList {
	K kk[N];
	V vv[N];
	size_t count;

public:
	KVList() : count(0) {}
	
	size_t size() const {
		return count;
	}

	const K& key(int i) const {
		if(i >= 0 && i < count)
			return kk[i];
	}

	const V& value(int i) const {
		if (i >= 0 && i < count)
			return vv[i];
	}

	KVList& add(const K& k, const V& v) {
		if (count < N) {
			kk[count] = k;
			vv[count] = v;
			count++;
		}
		return *this;
	}

	int find(const K& k) const {
		for (size_t i = 0; i < count; i++) {
			if(kk[i] == k) {
				return i;
			}
		}
		return 0;
	}

	KVList& replace(int i, const K& k, const V& v) {
		if(i >= 0 && i < count) {
			kk[i] = k;
			vv[i] = v;
		}
		return *this;
	}
};