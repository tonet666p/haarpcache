#include <iostream>
#include <cstring>
#include <vector>
#include "../utils.cpp"

// use this line to compile
// g++ -I. -fPIC -shared -g -o spotify.com.so spotify.com.cpp
// regex:
//   ^http.{3,20}\.spotify\.com(\.edgesuite\.net)?\/(audio\/\w{40}\?|head\/\w{40})$
//
// http://heads4-ak.spotify.com.edgesuite.net/head/3361099590eb25307f580713f318e5696a2a5b4f
// http://audio-sp-sjc.spotify.com/audio/0bbb9705b7056daa2113d30574a8f6ec1adee485?
// http://audio4-ak.spotify.com.edgesuite.net/audio/f231854b63504908efa3a15657bb20067796b260?

string get_filename(string url) {
        vector<string> paths, direct;
        string file = "";

        stringexplode(url, "/", &paths);
        int psize = paths.size();
        short save = 0;
        // If the url is edgesuite.net
        if(paths.at(1).find("spotify.com") != string::npos){
                for(int i=1;i<psize;i++) {
                        if(save == 1){
                                stringexplode(paths.at(i), "?", &direct);
                                return  file + direct.at(0);
                        }
                        if(paths.at(i) == "audio"){
                                file += "audio_";
                                save = 1;
                        }
                        if(paths.at(i) == "head"){
                                file += "head_";
                                save = 1;
//                              return file+paths.at(i+1);
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
        r.domain = "spotify";
        r.match = true;
        return r;
}
