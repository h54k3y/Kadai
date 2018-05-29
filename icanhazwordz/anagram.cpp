#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;
int main(){
	ifstream ifs("dictionary.txt");
	map<string,string> dictionary_map;

	string input_word;
	string sorted_word;
	int words_cnt=0;
	while(getline(ifs,input_word)){
		input_word.erase(input_word.size()-1);
		sorted_word=input_word;
		sort(sorted_word.begin(),sorted_word.end());
		dictionary_map[sorted_word]=input_word;
		++words_cnt;
	}
	cout<<words_cnt<<" words in \"dictionary.txt"<<"\" ."<<endl;
	cout<<dictionary_map.size()<<" words in maps"<<endl;
	for(int i=0;i<10;i++){
		cout<<"Please input the query"<<endl;
		string input_query;
		cin>>input_query;
		string sorted_query=input_query;
		string anagram;
		sort(sorted_query.begin(),sorted_query.end());
		if(dictionary_map.count(sorted_query)!=0 && dictionary_map[sorted_query]!=input_query){
			cout<<"The anagram of \""<<input_query<<"\" is"<<endl;
			cout<<dictionary_map[sorted_query]<<endl;
		}
		else{
			cout<<"There is no anagram of \""<<input_query<<"\" ."<<endl;
		}
	}
	return 0;
}