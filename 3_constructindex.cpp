#include <iterator>
#include <sstream>
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>


typedef std::map<std::string, std::vector<int> > map_t; 
typedef std::map<int, std::string> map_url; 
void show_pair(const map_t::value_type& p) 
{ 
     	std::cout << p.first  << " "; 
	for(std::vector<std::string>::size_type i = 0; i != (p.second).size(); i++) {
    		std::cout << " " << (p.second)[i] < " "; 
	}
	std::cout << "\n";

} 

std::vector<int> intersection(std::vector<int> a, std::vector<int> b){
	int size_a, size_b;
	size_a = a.size();
	size_b = b.size();
	int i=0,j=0;
	std::vector<int> c;
	std::sort (a.begin(), a.end());
	std::sort (b.begin(), b.end());
	
	for( ;i < size_a && j < size_b; ){
		if( a[i] < b[j]){
			i++;
		}
		else if(a[i] > b[j]){
			j++;
		}
		else{
			c.push_back(a[i]);
			i++;
			j++;	
		}

	}
	return c;	

}

std::vector<int> intersectAll(std::vector<std::vector<int> > array){
	std::vector<int> temp;
	std::vector<int> result = array[0];
	for(int i = 1; i< array.size(); i++){
		temp = intersection(result, array[i]);
		if(temp.size() > 0)
			result = intersection(result, array[i]);
	}
	return result;
}


int main(int argc, char *argv[]) {

	std::cout << "You have " << argc - 1<< " search terms" << std::endl; 
	if(argc < 2){
		std::cout << "Not enough arguments." << std::endl;
		return 1;
	}
	std::vector<std::string> args;
	
    	for(int i = 1; i < argc; i++){
        	args.push_back(argv[i]);
	
	}
	std::string line;
	int value;
	std::string temp;
	int key;
	std::string urlvalue;
	clock_t t1,t2, t3, t4;
	
	std::ifstream inputfile("index.txt");
	map_t index;
	t1 = clock();
	while(getline(inputfile, line)){
		std::string::size_type pos = line.find(" ");
		if(pos != std::string::npos){

			temp = line.substr(pos+1);
			std::stringstream ss(temp);
			while( ss >> value)
				index[line.substr(0, pos)].push_back(value);
		}
	}
	t2 = clock();
	inputfile.close();

	std::ifstream urlmap("urls.txt");
	map_url url;
	t3 = clock();
	while(getline(urlmap, line)){
		std::string::size_type pos = line.find(" ");
		if(pos != std::string::npos){
			url[atoi((line.substr(0, pos)).c_str())] = line.substr(pos+1);
		}
	}
	t4 = clock();
	urlmap.close();

	float indextime ((float)t2-(float)t1);
	float urltime ((float)t4-(float)t3);

	std::cout<< "Index creation took: " << indextime / CLOCKS_PER_SEC << "s" << std::endl;
	std::cout<< "URL Map Creation took: " << urltime / CLOCKS_PER_SEC << "s" << std::endl;

	std::vector<std::vector<int> > array;

	for(int k =0; k< args.size(); k++){
		if(index.find(args[k]) == index.end())
			std::cout << args[k] << " not found" << std::endl;
		else
			array.push_back(index.find(args[k])->second);
		
	}

	if(array.size() > 0){	
		std::vector<int> c(intersectAll(array));
	
		for(int k =0; k< c.size(); k++){
			if(url.find(c[k]) != url.end()){
				std::cout<< " " << (url.find(c[k]))->second << "\n";	
			}
		}
	}
	
}
