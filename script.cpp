#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef struct Ip {
	string ip;
	float ocorrencia_ip;
}Ip;


string linha;
string str;
vector<string> ips;
vector<Ip*> ips_sorted;
map<string,float> dicionario;
pair<std::map<char,int>::iterator,bool> ret;


std::string ExtractString( std::string source, std::string start, std::string end ){
     std::size_t startIndex = source.find( start );

     // If the starting delimiter is not found on the string
     // stop the process, you're done!
     //
     if( startIndex == std::string::npos )
     {
        return "";
     }

     // Adding the length of the delimiter to our starting index
     // this will move us to the beginning of our sub-string.
     //
     startIndex += start.length();

     // Looking for the end delimiter
     //
     std::string::size_type endIndex = end.length() - 1;
     // source.find( end, startIndex );

     // Returning the substring between the start index and
     // the end index. If the endindex is invalid then the
     // returned value is empty string.
     return source.substr( startIndex, endIndex - startIndex );
}



template<typename A, typename B>
std::pair<B,A> flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::multimap<B,A> flip_map(const std::map<A,B> &src)
{
    std::multimap<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()), 
                   flip_pair<A,B>);
    return dst;
}

bool compareByOcorrencia(const Ip *a, const Ip *b)
{
    return a->ocorrencia_ip > b->ocorrencia_ip;
}


void calcularIps(string file_str) {


	ifstream file(file_str);

    int count = 0;
    string ip_atual = "";

	while(getline(file,linha)) {
		count++;
		string str = ExtractString(linha,"IP: ","");
		// cout<<"IP: ["<<str<<"]"<<endl;

		if(str.length() == 0) {
			str = ExtractString(linha,"Current Packets: 0, Baseline: "," 	 Detected Time:");
			if(str.length() == 0){
				continue;
			}
			else if(ip_atual.length() > 0) {
				float value = atof(str.c_str());
				// cout<<"Value: "<<value<<endl;
				if(dicionario.count(ip_atual)) {
					float num = dicionario[ip_atual];
					dicionario[ip_atual] = value + dicionario[ip_atual];
					// cout<<"EXISTE:  "<<dicionario[ip_atual]<<endl;
				}
				else {
					dicionario[ip_atual] = value;
				}
			}

		}
		else {
			ip_atual = str;
			continue;
		}

		// cout<<str<<endl;
		// if(str.length() > 0){
		// 	ips.push_back(str);
		// 	//cout<<endl;
		// }

		// if(dicionario.count(str)) {


		// 	int num = dicionario[str];
		// 	dicionario[str] = ++num;
		// 	// cout<<"EXISTE:  "<<dicionario[str]<<endl;
		// }
		// else {

		// 	dicionario[str] = 1;
		// }

	}

	


	


}

void ordenarIps(){
	std::map<string,float>::iterator it = dicionario.begin();
	for (it=dicionario.begin(); it!=dicionario.end(); ++it){

    	Ip *ip = new Ip();
    	ip->ip = it->first;
    	ip->ocorrencia_ip = it->second;
    	ips_sorted.push_back(ip);
	}

	sort(ips_sorted.begin(),ips_sorted.end(),compareByOcorrencia);
}

void listarIps() {
	vector<Ip*>::iterator it2 = ips_sorted.begin();
	for(it2 = ips_sorted.begin(); it2 != ips_sorted.end(); ++it2){
		cout<<(*it2)->ip<<" -> "<<(*it2)->ocorrencia_ip<<endl;
	}

    // cout<< "NUMEROS: "<<count<<endl;
}



int main () {

	// for(int i = 1; i < 22; i++) {
	// 	string src;
	// 	if(i < 10){
	// 		src = "report-2017-01-0"+to_string(i)+".log";
	// 	}
	// 	else {
	// 		src = "report-2017-01-"+to_string(i)+".log";
	// 	}
		
	// }

	string src = "report.log";
	calcularIps(src);

	ordenarIps();
	listarIps();

}





