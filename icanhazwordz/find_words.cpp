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
	vector<pair<string,string> > dictionary_vector;
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
	char one_point[15]={'a','b','d','e','g','i','n','o','r','s','t','u'};
	char two_point[10]={'c','f','h','l','m','p','v','w','y'};
	char three_point[6]={'j','k','q','x','z'};
	for(int i=0;i<10;i++){
		cout<<"Please input the query"<<endl;
		int max_point=0;
		int max_size=0;
		string input_query;
		cin>>input_query;
		transform(input_query.begin(),input_query.end(),input_query.begin(), ::tolower);
		string sorted_query=input_query;
		string answer_word;
		sort(sorted_query.begin(),sorted_query.end());
		for(int i=0;i<dictionary_vector.size();i++){
			int k_cnt=0;
			for(int j=0;j<dictionary_vector[i].first.size();j++){
				int k_flg=0;
				for(int k=k_cnt;k<sorted_query.size();k++){
					if(dictionary_vector[i].first[j]==sorted_query[k]){
						k_cnt=k+1;
						k_flg=1;
						break;
					}
				}
				if(k_flg==0){
					break;
				}
				else if(j==dictionary_vector[i].first.size()-1){
					if(max_size==0){
						cout<<"Congrats! I was able to find the word in \""<<input_query<<"\" . Which is"<<endl;
					
					}
					cout<<dictionary_vector[i].second<<", ";
					if(dictionary_vector[i].second.size()>=max_size){
						int point=0;
						for(int p=0;p<13;p++){
							for(int dp=0;dp<dictionary_vector[i].second.size();dp++){
								if(one_point[p]==dictionary_vector[i].second[dp]){
									point+=1;
								}
							}
						}
						for(int p=0;p<10;p++){
							for(int dp=0;dp<dictionary_vector[i].second.size();dp++){
								if(two_point[p]==dictionary_vector[i].second[dp]){
									point+=2;
								}
							}
						}
						for(int p=0;p<6;p++){
							for(int dp=0;dp<dictionary_vector[i].second.size();dp++){
								if(three_point[p]==dictionary_vector[i].second[dp]){
									point+=3;
								}
							}
						}
						point++;
						point*=point;
						if(point>max_point){
							max_point=point;
							max_size=dictionary_vector[i].second.size();
							answer_word=dictionary_vector[i].second;
						}
					}
				}

			}
			if(i==dictionary_vector.size()-1){
				if(max_size==0){
					cout<<"Oh, Sorry! I couldn't find a word in \""<<input_query<<"\" ."<<endl;
				}
				else{
					cout<<endl;
					cout<<"The word with the highest score ("<<max_point<<" poins) in \""<<input_query<<"\" is"<<endl;
					cout<<answer_word<<endl;
				}
			}
		}
	}
	return 0;
}