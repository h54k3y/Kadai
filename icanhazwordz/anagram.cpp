#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

void SetDictionary(map<string,string> &dictionary_map);

bool MakeAnagram(const map<string,string>& dictionary_map,const string input_query, string &anagram);


int main(){
	map<string,string> dictionary_map;
	SetDictionary(dictionary_map);
	for(int i=1;i<10;i++){
		cout<<i<<":"<<"Please input the query"<<endl;
		string input;
		string input_query;
		string anagram;
		cin>>input;
		input_query=input;
		transform(input_query.begin(),input_query.end(),input_query.begin(), ::tolower);
		bool find=MakeAnagram(dictionary_map,input_query,anagram);
		if(find){
			cout<<"Congrats! I was able to find the word in \""<<input<<"\" . Which is"<<endl;
			transform(anagram.begin(),anagram.end(),anagram.begin(), ::toupper);
			cout<<anagram<<endl;
		}
		else{
			cout<<"Oh, Sorry! I couldn't find a word in \""<<input<<"\" ."<<endl;
		}
	}
	return 0;
}

void SetDictionary(map<string,string> &dictionary_map){
	ifstream ifs("dictionary.txt");
	string input_word;
	string sorted_word;
	int words_cnt=0;
	while(getline(ifs,input_word)){
			input_word.erase(input_word.size()-1);
			sorted_word=input_word;
			sort(sorted_word.begin(),sorted_word.end());
			dictionary_map[sorted_word]=input_word;
			words_cnt++;
	}
	cout<<words_cnt<<" words in \"dictionary.txt"<<"\" ."<<endl;
	cout<<dictionary_map.size()<<" words in maps"<<endl;
	return;
}

bool MakeAnagram(const map<string,string>& dictionary_map,const string input_query, string &anagram){
	string sorted_query=input_query;
	sort(sorted_query.begin(),sorted_query.end());
	if(dictionary_map.count(sorted_query)!=0 && dictionary_map.at(sorted_query)!=input_query){
		anagram=dictionary_map.at(sorted_query);
		return true;
	}
	else{
		return false;
	}

}