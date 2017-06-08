#include <iostream>
#include <cstring>
#include <vector>
#include "../utils.cpp"

// use this line to compile
// g++ -I. -fPIC -shared -g -o cdn.dota2.com.so cdn.dota2.com.cpp  
// regex:
// http://cdn.dota2.com/apps/dota2/images/blogfiles/2014/solo_esta_parte_cambia.png
string get_filename(string url) {
	vector<string> paths;
	
	stringexplode(url, "/", &paths);
	int psize = paths.size();
	short save = 0;
	for(int i=0;i<psize;i++) {
		if(save == 1) {
			return paths.at(i);
		}
		if(paths.at(i) == "dota2" && paths.at(i+1) == "images" && paths.at(i+2) == "blogfiles" && paths.at(i+3) == "2014"){
			save = 1;
			i+=3;
		}
		
	}
	return "";
}

extern "C" resposta hgetmatch2(const string url) {
	resposta r;	
	r.range_min = 0;
	r.range_max = 0;

	r.file = get_filename(url);
	r.domain = "dota2";
	r.match = true;
	return r;
	
}

