#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <set>

#define INIT_SIZE 10000
#define WORK_SIZE 10000
#define CASE_NAME "medium"
#define NGRAM_PROB() (std::rand()%2 == 0)
#define QUERY_PROB() (std::rand()%3 <= 1)
#define APROB 20
#define QPROB 80
#define DPROB 100

int main(int argc, char *argv[]){
    std::vector<std::string> wordlist;
    std::set<std::string> ngramset;
    std::vector<std::string> ngrams;
    std::ifstream fin("Words");

    std::srand(std::time(0));
    while (!fin.eof()){
        std::string buf;
        fin >> buf;
        wordlist.push_back(buf);
    }
    fin.close();
    {
        std::ofstream fout(std::string(CASE_NAME) + std::string(".init"));
        for (int i = 0; i < INIT_SIZE; i++){
            while(1){
                std::string s = wordlist[std::rand()%wordlist.size()];
                while(NGRAM_PROB())
                    s = s + " " + wordlist[std::rand()%wordlist.size()];
                if (ngramset.find(s) == ngramset.end()){
                    ngramset.insert(s);
                    ngrams.push_back(s);
                    fout << s << std::endl;
                    break;
                }
            } 
        }
        fout.close();
    }
    {
        std::ofstream fout(std::string(CASE_NAME) + std::string(".work"));
        for (int i = 0; i < WORK_SIZE; i++){
            int v = std::rand()%100;
            if (v < APROB){
                while(1){
                    std::string s = wordlist[std::rand()%wordlist.size()];
                    while(NGRAM_PROB())
                        s = s + " " + wordlist[std::rand()%wordlist.size()];
                    if (ngramset.find(s) == ngramset.end()){
                        ngramset.insert(s);
                        ngrams.push_back(s);
                        fout << "A " << s << std::endl;
                        break;
                    }
                }
            }
            else if (v < QPROB){
                std::string s = wordlist[std::rand()%wordlist.size()];
                while(QUERY_PROB())
                    s = s + " " + wordlist[std::rand()%wordlist.size()];
                fout << "Q " << s << std::endl;
            }
            else{
                std::string s = ngrams[std::rand()%ngrams.size()];
                ngrams.erase(std::remove(ngrams.begin(), ngrams.end(), s), ngrams.end());
                ngramset.erase(s);
                fout << "D " << s << std::endl;
            }
        }
        fout.close();
    }
    return 0;
}
