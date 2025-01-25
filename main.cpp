#include <fstream>
#include <iostream>
#include <string>
#include <array> 

using namespace std;

void dump(string displayValue){ // dump built-in function displaying values in the console
    for(char singleSign : displayValue){
        if(singleSign != '"'){
            cout << singleSign;
        }
    }
}

int main()
{
    string keywords[][4] = {{"dump","(","@any",")"}};
    
    ifstream file;
    file.open("code.txt"); //opening file
    string lineOfCode;

    if (file.is_open()) {
        
        while (getline(file, lineOfCode)) {
            int charCount = 0;
            for(char sign : lineOfCode){ //getting length of one line
                charCount++;
            }
            
            char charList[charCount]; //creating an array with that length
            charCount = 0;
            
            for(char sign : lineOfCode){ //adding chars to that array
                charList[charCount] = sign;
                charCount++;
            }
            string text = ""; //a part of line, getting longer with each iteration
            int foundKeywordID = -1; //id of a found keyword in keywords array
            string foundKeyword = ""; //a part of keyword, getting longer with each iteration
            int chainContinue = 0; //streak of using this keyword in a line
            string operand = "";
            
            for(int i = 0; i < charCount;i++){ 
                text += charList[i];
                if(foundKeywordID == -1){ //searching for a keyword
                    
                    for(int j = 0;j < 1;j++){
                        if(text == keywords[j][0]){
                            foundKeywordID = j;
                            foundKeyword = keywords[j][0];
                        }
                    }
                    
                }else{ //continuation of a keyword chain
                    if(chainContinue<4){ //prevent going out of chain indexes
                        if(keywords[foundKeywordID][chainContinue] != "@any"){ //check if can increment
                            chainContinue++;
                        }
                        if(keywords[foundKeywordID][chainContinue] != "@any"){ //check if can add
                            foundKeyword += keywords[foundKeywordID][chainContinue];
                        }else{
                            if(charList[i] == ')'){ //if ends an operand
                                chainContinue++;
                                foundKeyword += keywords[foundKeywordID][chainContinue];
                                continue;
                            }
                            foundKeyword += charList[i];
                            operand += charList[i];
                        }
                    }
                    if(charList[i] == ';'){ //end of line. 
                        switch(foundKeywordID){ //time to execute found keywords
                            case 0:
                            dump(operand);
                            break;
                        }
                        break;
                    }
                }
            }
        }
        
        file.close();
    }
    else {
        cerr << "Error while trying to read file." << endl;
    }

    return 0;
}