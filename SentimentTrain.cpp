#include "SentimentTrain.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

// USING CUSTOM GETLINE FUNCTION
//this function reads in the words in the training dataset into a vector defined in the .h file
void SentimentTrain::readWordsCustom(char *fileOne)
{
    // Open the file
    ifstream readFile(fileOne);
    if (!readFile.is_open())
    {
        cout << "Failed to open file\n";
    }
    else
    {
        cout << "\nopened file";
    }
    // sets a delimeter and a DSString
    char delim = ',';
    DSString line;
    // ignores header line
    getline(readFile, line);

    // stores all the things in line
    // 4,2014351367,Wed Jun 03 01:14:33 PDT 2009,NO_QUERY,cathyleehart,@just_tam21 hahah its kind of the same as adelaides except a bit bigger
    // makes sure it iterates through whole file
    while (readFile.good())
    {
        // temporary token
        DSString token;
        // reads in sentiment
        getline(readFile, token, delim);
        sentiment = atoi(token.c_str());

        // reads in ID
        getline(readFile, token, delim);
        id = token;

        // IGNORES DATE and QUERY
        getline(readFile, token, delim);
        getline(readFile, token, delim);

        // reads in USER and ignores
        getline(readFile, token, delim);

        // Read the tweet
        getline(readFile, token);
        // NORMALIZES TWEET
        DSString tweet = token.toLower();

        // Stores information in three vectors
        tweetsInFile.push_back(tweet);
        tweetIDs.push_back(id);
        tweetSentimemts.push_back(sentiment);

        // for (int i = 0; i < tweetsInFile.size(); i++){
        //     cout << "sent : " << tweetSentimemts.at(i) << "ID: " << tweetIDs.at(i) << "\n";
        // }
    }
    // closes the read file
    readFile.close();

    // code to check that it outputs the tweets
    //  ofstream outFile("../zzGetlineCustomOutput.txt");
    //  for(auto item : tweetIDs){
    //      outFile << item << endl;
    //  }
    //  outFile.close();
}

// this code is identical to readWordsCustom, but does not read in a sentiment
void SentimentTrain::readTestWords(char *fileTwo)
{
    ifstream readFile(fileTwo);
    if (!readFile.is_open())
    {
        cout << "Failed to open file\n";
    }
    else
    {
        cout << "\nopened file";
    }
    // sets a delimeter and a DSString
    char delim = ',';
    DSString line;
    // ignores header line
    getline(readFile, line); // id,Date,Query,User,Tweet

    while (readFile.good())
    {
        // temporary token
        DSString token;
        // reads in ID
        getline(readFile, token, delim);
        id = token;

        // IGNORES DATE and QUERY
        getline(readFile, token, delim);
        getline(readFile, token, delim);

        // reads in USER
        getline(readFile, token, delim);

        // Read the tweet
        getline(readFile, token);
        // NORMALIZES TWEET
        DSString tweet = token.toLower();

        // Stores information in three vectors
        tweetsInFileTwo.push_back(tweet);
        tweetIDTwo.push_back(id);
    }
    // closes the read file
    readFile.close();

    // code to check that it outputs the tweets
    //  ofstream outFile("../zztweetsToAnalyze.txt");
    //  for(auto item : tweetsInFileTwo){
    //      outFile << item << endl;
    //  }
    //  outFile.close();
}

// train function should put my values into the map
void SentimentTrain::train()
{
    // go through each tweet. tweetsInFile holds a whole tweet
    for (size_t i = 0; i < tweetsInFile.size(); ++i)
    {
        // returns a vector of individual words using the tokenize function
        vector<DSString> wordsInTweet = tweetsInFile.at(i).tokenize(tweetsInFile.at(i));
        // iterates through this temprary vector to update the map
        for (size_t k = 0; k < wordsInTweet.size(); k++)
        {
            // removes words that are of length < 3
            if (wordsInTweet.at(k).length() < 3)
            {
                // do nothing
            }
            else
            {
                // if the bias is in the map
                if (tweetBias.find(wordsInTweet.at(k)) != tweetBias.end())
                {
                    // increment or decrement the sentiment
                    if (tweetSentimemts[i] == 4)
                    {
                        tweetBias.at(wordsInTweet.at(k)) += 1;
                    }
                    else
                    {
                        tweetBias.at(wordsInTweet.at(k)) -= 1;
                    }
                }
                // if the word is not in the map
                else
                {
                    // add the word to the map with a given sentiment
                    if (tweetSentimemts.at(i) == 4)
                    {
                        tweetBias.insert({wordsInTweet.at(k), 1});
                    }
                    else
                    {
                        tweetBias.insert({wordsInTweet.at(k), -1});
                    }
                }
            }
        }
    }
    // lets user see the bias in words
    //  ofstream outFile("../zzmapOutput.txt");
    //  for(auto item : tweetBias){
    //      outFile << item.first << ' ' << item.second << endl;
    //  }
    //  outFile.close();
}

// this function will break down a tweet into different words and find them on the map to inc or dec the sentiment
void SentimentTrain::test(char *fileFour)
{
    // go through each tweet. tweetsInFile holds a whole tweet

    for (size_t i = 0; i < tweetsInFileTwo.size(); ++i)
    {
        int netSentiment = 0;
        // returns a vector of individual words using the tokenize function
        vector<DSString> wordsInTweet = tweetsInFileTwo.at(i).tokenize(tweetsInFileTwo.at(i));
        // will have to go through the individual words
        for (size_t k = 0; k < wordsInTweet.size(); k++)
        {
            // if the bias is in the map, it returns true
            if (tweetBias.find(wordsInTweet.at(k)) != tweetBias.end())
            {
                netSentiment += tweetBias.at(wordsInTweet.at(k));
            } // no else bc it will skip
        }
        // still in the first for loop, check for the netSentiment value
        // pushed into vector to output all the same
        if (netSentiment > 0)
        {
            sentiment = 4; //if net sentiment is above 0, tweet is classified as positive
            tweetSentimemtsTwo.push_back(sentiment);
        }
        else
        {
            sentiment = 0;
            tweetSentimemtsTwo.push_back(sentiment);
        }
    }
    ofstream outFile(fileFour);
    if (!outFile.is_open())
    {
        cout << "Failed to open file\n";
    }
    else
    {
        cout << "\nopened file";
    }
    cout << "\nwriting in file test";
    for (size_t i = 0; i < tweetIDTwo.size(); i++)
    {
        outFile << tweetSentimemtsTwo.at(i) << ',' << tweetIDTwo.at(i) << endl;
    }
    outFile.close();
}

//uses CLI to check the accuracy of the classification
void SentimentTrain::checkAccuracy(char *file3, char *file5)
{
    double count = 0;
    // open file three
    ifstream readFile(file3);
    if (!readFile.is_open())
    {
        cout << "Failed to open file\n";
    }
    else
    {
        cout << "\nopened file";
    }
    //./sentiment ./data/train_dataset_20k.csv ./data/test_dataset_10k.csv ./data/test_dataset_sentiment_10k.csv ./results.csv ./accuracy.txt
    // sets a delimeter and a DSString
    char delim = ',';
    DSString line;
    // ignores header line
    getline(readFile, line);
    while (readFile.good())
    {
        // temporary token
        DSString token;
        // reads in sentiment
        getline(readFile, token, delim);
        sentiment = atoi(token.c_str());

        // reads in ID
        getline(readFile, token);
        id = token;
        // pushes back into the vectors
        accuracyId.push_back(id);
        accuracySentiment.push_back(sentiment);
    }
    readFile.close();

    // checks how many tweets are correct
    for (size_t i = 0; i < accuracySentiment.size(); i++)
    {
        if (accuracySentiment.at(i) == tweetSentimemtsTwo.at(i))
        {
            count += 1;
        }
    }
    //calculation for accuracy
    float checkAcc = count / (float)(accuracySentiment.size() - 1);

    ofstream outFile(file5);
    if (!outFile.is_open())
    {
        cout << "Failed to open file\n";
    }
    else
    {
        cout << "\nopened file";
    }

    outFile << "Accuracy: " << fixed << setprecision(3) << checkAcc << '\n';
    // goes through accuracy
    for (size_t i = 0; i < accuracyId.size(); ++i)
    {
        if (accuracySentiment.at(i) != tweetSentimemtsTwo.at(i))
        {
            outFile << tweetSentimemtsTwo.at(i) << "," << accuracySentiment.at(i) << "," << accuracyId.at(i) << '\n';
        }
    }
    outFile.close();
}

//test function 
void SentimentTrain::outputVectors()
{
    for (size_t i = 0; i < accuracyId.size(); i++)
    {
        cout << accuracyId.at(i) << " " << tweetIDTwo.at(i) << '\n';
    }
}
