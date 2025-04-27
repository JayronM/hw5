#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void helper(int position, const string& in, string& current, string remaining, const set<string>&dict, set<string>& results);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> results;
    string current = in; //current state
    helper(0,in,current,floating,dict,results);
    return results;

}

void helper(int position, const string& in, string& current, string remaining, const set<string>&dict, set<string>& results){
    int n = in.size();
    //if floating letter been placed down
    if(position ==n){
        if(remaining.empty()){
            if(dict.find(current)!=dict.end()){
        results.insert(current);
        }
        }
        return;
    }
    //positioned fixed, copy and recusrve it
    if(in[position]!= '-'){
        current[position]= in[position];
        helper(position+1, in, current, remaining, dict, results);
    } else{
        int blanks=0; //amoutn of blanks left
        for(int i = position;i<n; i++){
            if(in[i]=='-') blanks++;
        }
        //if blanks equal floating letters, place letter
        if(blanks ==(int)remaining.size()){
            for(int i=0; i< (int)remaining.size();i++){
                char c = remaining[i];
                string nestFloating = remaining;
                nestFloating.erase(i, 1);
                current[position]= c;
                helper(position+1, in, current, nestFloating, dict, results);
            }
        } else{
            //place a floating letter
            for(int i= 0; i<(int)remaining.size(); i++){
                char c = remaining[i];
                string nestFloating = remaining;
                nestFloating.erase(i,1);
                current[position] =c;
                helper(position+1, in, current, nestFloating, dict, results);
            }
            for(char c = 'a'; c<= 'z';c++){
                bool isFloating = false;
                for(char f: remaining){
                    if(c==f){ 
                        isFloating = true;
                        break;
                        }
                }
                if(isFloating) continue;
                
                current[position] =c;
                helper(position+1, in, current, remaining, dict, results);
                
            }
        }
    }
}
