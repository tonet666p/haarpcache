#include <iostream>
#include <cstring>
#include <vector>
#include "../utils.cpp"

// use this line to compile
// g++ -I. -fPIC -shared -g -o steampowered.com.so steampowered.com.cpp  
// regex:
// http://cdn.edgecast.cs.steampowered.com/depot/401537/manifest/99479346433520935/5? 
// http://cdn.edgecast.cs.steampowered.com/depot/401537/chunk/2105fa26d7e64a307d0795084c293cc5b2096fdf?
// ^http.{3,60}\.cs\.steampowered\.com\/depot\/[0-9]+\/chunk|manifest\/\w{19,}(\/5){,1}$
// ^http.{3,60}\.steamcontent\.com\/depot\/[0-9]+\/chunk|manifest\/\w{19,}(\/5){,1}$
string get_filename(string url) {
	vector<string> paths, direct;
	string file = "";
	
	stringexplode(url, "/", &paths);
	int psize = paths.size();
	short save = 0;
	for(int i=0;i<psize;i++) {
		if(save == 1) {
			file = paths.at(i);
			save = 0;
		}
		if(paths.at(i) == "depot")
			save = 1;
		if(paths.at(i) == "chunk"){
			file = file + "_" + "chunk";
			stringexplode(paths.at(i+1), "?", &direct);
			file = file + "_" + direct.at(0);
			return file;
		}
		if(paths.at(i) == "manifest"){
			file = file + "_" + "manifest";
			file = file + "_" + paths.at(i+1);
			return file;
		}
	}
	return "";
}

extern "C" resposta hgetmatch2(const string url) {
	resposta r;	
	r.range_min = 0;
	r.range_max = 0;

	r.file = get_filename(url);
	r.domain = "steampowered";
	r.match = true;
	return r;
}

