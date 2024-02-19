#include <iostream>
#include "DSString.h"
#include "SentimentTrain.h"
#include <fstream>
#include <vector>
#include <chrono>
#include <ctime> // for srand(time(NULL))

using namespace std;
// should run with
// ./sentiment ./data/train_dataset_20k.csv ./data/test_dataset_10k.csv ./data/test_dataset_sentiment_10k.csv ../RESULTS.CSV ../ACCURACY.TXT

// please use ../RESULTS.csv  ../ACCURACY.txt
// if not, the files wlil be found in the build directory
int main(int argc, char **argv)
{
    // creates a trainer
    SentimentTrain classifier;

    classifier.readWordsCustom(argv[1]);
    classifier.train();

    classifier.readTestWords(argv[2]);
    classifier.test(argv[4]);

    classifier.checkAccuracy(argv[3], argv[5]);
    // classifier.outputVectors();
    return 0;
}

// code to find time
//  srand(time(NULL));
//  std::cout << "N, time [micro sec.]" << "\n";
//  auto start = std::chrono::high_resolution_clock::now();
//  auto stop = std::chrono::high_resolution_clock::now();
//  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
//  std::cout << '\n' << duration.count() << "\n";
