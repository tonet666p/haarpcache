#include <iostream>
#include <cstring>
#include <vector>
#include "../utils.cpp"

// use this line to compile
// g++ -I. -fPIC -shared -g -o imageshack.us.so imageshack.us.cpp
// regex: ^http.*(\.imageshack\.(com|us))\/.*(\.jpg|\.png|\.gif|\.jpeg)$
// http://imagizer.imageshack.us/a/img923/7209/Gc2Ifq.jpg
// http://imageshack.com/a/img923/7209/Gc2Ifq.jpg
string get_filename(string url) {
	vector<string> paths;
	string filename = "";

	stringexplode(url, "/", &paths);
	int psize = paths.size();
	short save = 0;
	for(int i=2;i<psize-1;i++) {
		filename += paths.at(i);
		filename += "_";
	}

	return filename+paths.at(psize-1);
}


extern "C" resposta hgetmatch2(const string url) {
	resposta r;
	r.range_min = 0;
	r.range_max = 0;

	r.file = get_filename(url);
	r.domain = "imageshack";
	r.match = true;
	return r;
}
