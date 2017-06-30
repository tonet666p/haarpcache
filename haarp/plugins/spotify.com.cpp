#include <iostream>
#include <cstring>
#include <vector>
#include "../utils.cpp"

// use this line to compile
// g++ -I. -fPIC -shared -g -o steampowered.com.so steampowered.com.cpp  
// regex: 
//   http.{3,20}(\.spotify\.com|)\/(audio|head)\/\w{45}(\?){,1}$
//   http.{3,20}\.spotity\.com\.edgesuite\.net\/
//
// http://heads4-ak.spotify.com.edgesuite.net/head/3361099590eb25307f580713f318e5696a2a5b4f
// http://audio-sp-sjc.spotify.com/audio/0bbb9705b7056daa2113d30574a8f6ec1adee485?
// http://audio4-ak.spotify.com.edgesuite.net/audio/f231854b63504908efa3a15657bb20067796b260? 
// http.{3,4}cdn\.(\w|\.)*cs\.steampowered\.com\/depot\/[0-9]+\/manifest\/\w{40}
// http.{3,4}cdn\.(\w|\.)*cs\.steampowered\.com\/depot\/[0-9]+\/chunk|manifest\/\w{19}\/5
string get_filename(string url) {
	vector<string> paths, direct;
	string file = "";
	
	stringexplode(url, "/", &paths);
	int psize = paths.size();
	short save = 0;
	// If the url is edgesuite.net
	if(paths.at(1).find("spotify.com") != string::npos){
		for(int i=0;i<psize;i++) {
			if(save = 1){
				stringexplode(paths.at(i), "?", &direct);
				file = file + direct.at(0);
				return file;
			}
			if(paths.at(i) == "audio"){
				file += "audio_";
				save = 1;
			}
			if(paths.at(i) == "head"){
				return "head_"+paths.at(i+1);
			}
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
