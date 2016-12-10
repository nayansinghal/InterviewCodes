#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <stdlib.h>
#include <cstring>
using namespace std;
class TrieNode{
public:
    TrieNode* children[26];
    char c;
    bool isKey;
    TrieNode(): isKey(false), c('0'){
        memset(children, NULL, sizeof(TrieNode*) * 26);
    }
};

class WordDictionary {
public:

    WordDictionary(){
        root = new TrieNode();
        
    }
    // Adds a word into the data structure.
    void addWord(string word) {
       TrieNode* ptr = root;
       
       for(int i=0; i<word.length(); i++){
           if(ptr->children[word[i]-'a'] == NULL){
                ptr->children[word[i]-'a'] = new TrieNode();
                ptr->children[word[i]-'a']->c = word[i];
            }
           ptr = ptr->children[word[i]-'a'];
       }
       ptr->isKey = true;
    }

    bool query(string& word, TrieNode* ptr, int pos){
        if(ptr == NULL)
            return false;

        for(int i = pos; i<word.length(); i++){
            //cout<<i<<"\n";
            if(ptr && word[i] != '.')
                ptr = ptr->children[word[i]-'a'];
            else if(ptr && word[i] == '.'){
                TrieNode* temp = ptr;
                for(int j=0; j<26; j++){
                    ptr = temp->children[j];
                    if(query(word, ptr, i+1))
                        return true;
                }
            }
            else
                break;
        }
        return ptr && ptr->isKey;
    }
    // Returns if the word is in the data structure. A word could
    // contain the dot character '.' to represent any one letter.
    bool search(string word) {
        query(word, root,0);
    }
private:
    TrieNode* root;
};
int main()
{
    WordDictionary wordDictionary;
    wordDictionary.addWord("bad");
    wordDictionary.addWord("dad");
    wordDictionary.addWord("mad");
    cout<<wordDictionary.search("pad");
    cout<<wordDictionary.search("bad");
    cout<<wordDictionary.search(".ad");
    cout<<wordDictionary.search("b..");
}