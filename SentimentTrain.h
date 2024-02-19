#ifndef SENTIMENTTRAIN_H
#define SENTIMENTTRAIN_H
#include "DSString.h"
#include <vector>
#include <map>

class SentimentTrain
{
public:
    void readWordsCustom(char *file1);
    void train();
    void readTestWords(char *file2);
    void test(char *file4);
    void checkAccuracy(char *file3, char *file5);
    void outputVectors();

    char delim = ',';
    DSString date, query, user, tweet, id;
    size_t sentiment;

private:
    // this will be the delimiter after the normalize function in tokenizer
    // collects DSString sentiments, and IDs with their respective tweet
    // read function
    std::vector<DSString> tweetsInFile;
    std::vector<size_t> tweetSentimemts;
    std::vector<DSString> tweetIDs;

    // vectors for tweetsToAnalyze functions
    std::vector<DSString> tweetsInFileTwo;
    std::vector<size_t> tweetSentimemtsTwo;
    std::vector<DSString> tweetIDTwo;

    //vectors to store for checking Accuracy
    std::vector<DSString> accuracyId;
    std::vector<size_t> accuracySentiment;

    //map makes it easier than using vectors to track sentiments
    std::map<DSString, int> tweetBias;

    // implementing stop words
    // stop words retrieved from  From http://www.lextek.com/manuals/onix/stopwords1.html
};
#endif