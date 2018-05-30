#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>
#include <fstream>

using namespace std;

void SetDictionary(vector<pair<string,string> > &dictionary_vector);
int FindWords(const vector<pair<string,string> > dictionary_vector, const string input_query, const string input, string &answer_word);

int main(){
	vector<pair<string,string> > dictionary_vector;
	SetDictionary(dictionary_vector);
	for(int i=0;i<10;i++){
		cout<<i+1<<":"<<"Please input the query"<<endl;
		string input;
		string input_query;
		string answer_word;
		cin>>input;
		input_query=input;
		transform(input_query.begin(),input_query.end(),input_query.begin(), ::tolower);
		int max_point=FindWords(dictionary_vector,input_query,input,answer_word);
		if(max_point==0){
			cout<<"Oh, Sorry! I couldn't find a word in \""<<input<<"\" ."<<endl;
		}
		else{
			cout<<endl;
			cout<<"The word with the highest score ("<<max_point<<" poins) in \""<<input<<"\" is"<<endl;
			transform(answer_word.begin(),answer_word.end(),answer_word.begin(), ::toupper);
			cout<<answer_word<<endl;
		}
	}
	return 0;
}

void SetDictionary(vector<pair<string,string> > &dictionary_vector){
	ifstream ifs("dictionary.txt");
	string input_word;
	string sorted_word;
	int words_cnt=0;
	while(getline(ifs,input_word)){
		input_word.erase(input_word.size()-1);
		sorted_word=input_word;
		sort(sorted_word.begin(),sorted_word.end());
		dictionary_vector.push_back(make_pair(sorted_word,input_word));
		++words_cnt;
	}
	cout<<words_cnt<<" words in dictionary"<<endl;
	return;
}

int FindWords(const vector<pair<string,string> > dictionary_vector, const string input_query, const string input, string &answer_word){
	char points[27]={'a','b','d','e','g','i','n','o','r','s','t','u','c','f','h','l','m','p','v','w','y','j','k','q','x','z'};
	int max_point=0;
	string sorted_query=input_query;
	sort(sorted_query.begin(),sorted_query.end());
	for(int i=0;i<dictionary_vector.size();i++){
		int k_cnt=0;
		for(int j=0;j<dictionary_vector[i].first.size();j++){
			bool k_flg=false;
			for(int k=k_cnt;k<sorted_query.size();k++){
				if(dictionary_vector[i].first[j]==sorted_query[k]){
					k_cnt=k+1;
					k_flg=true;
					break;
				}
			}
			if(!k_flg){
				break;
			}
			else if(j==dictionary_vector[i].first.size()-1){
				if(max_point==0){
					cout<<"Congrats! I was able to find the word in \""<<input<<"\" . Which is"<<endl;	
				}
				cout<<dictionary_vector[i].second<<", ";
				//Count and update the points
				int point=0;
				for(int p=0;p<27;p++){
					for(int ip=0;ip<dictionary_vector[i].second.size();ip++){
						if(points[p]==dictionary_vector[i].second[ip]){
							if(ip<14){
								point+=1;
							}
							else if(ip<22){
								point+=2;
							}
							else if(ip<27){
								point+=3;
							}
							
						}
					}
				}
				point++;
				point*=point;
				if(point>max_point){
					max_point=point;
					answer_word=dictionary_vector[i].second;
				}
				
			}
		}
	}
	return max_point;
}
