# Assignment 2: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Your Name: Arath Dominguez

Used free extension: [ ] 24 hrs or [ ] 48 hrs

[X] Early submission (48 hrs)

[ ] Bonus work. Describe:

Place [x] for what applies.


## UML Diagram

Add your UML class diagram here.

Replace the following image with your diagram. You can draw it by hand and take a photo.
![UML Class Diagram](UML_class.png)

## Answers

1. How do you train the model and how do you classify a new tweet? Give a short description of the main steps.

    > I trained my model by appending normalized tweets into a vector with the respective sentiment in a different vector (ensures that they are at same index). Then, I tokenized my tweet and put these tokens in a seperate temporary vector that will enable me to iterate through the entire vector. Next, I check to see if the token exists in my map. If it does, I check the sentiment of the word, and adjust my map accordingly. This is all within a for-loop to go through every word in every tweet. 

2. How long did your code take for training and what is the time complexity of your training implementation (Big-Oh notation)? Remember that training includes reading the tweets, breaking it into words, counting, ... Explain why you get this complexity (e.g., what does `N` stand for and how do your data structures/algorithms affect the complexity).

   > My training function has a time complexity of O(n*m). The training potion calls two functions, readCustomWords() and train(). Time complexity only takes the highest degree into consideration and in train() I have a nested for-loop that iterates through each tweet in my tweetsInFile to tokenize, then goes through the new tokenized vector to update the map.
   > How long did my code take to run : 1025261 MICROSECONDS

3. How long did your code take for classification and what is the time complexity of your classification implementation (Big-Oh notation)? Explain why.

   > The runtime complexity of my classification function is O(n*m), where n is the number of tweets in the test dataset and m is number of words in each tweet. It uses a nested for loop.
   > How long did my code take to run : 367734 Microseconds


4. How do you know that you use proper memory management? I.e., how do you know that you do not have
   a memory leak?

   > When I was creating my DSString class, I utilized valgrind to detect any memory leaks. For every 'new' statement, I make sure that there is a delete operator. My constructors have a delete operator and I implemented a destructor. To check for memory leaks, run through the program with valgrind and see if there are any bytes missing.

5. What was the most challenging part of the assignment?

   > The most challenging part in my opinion was figuring out the DSString class and adding functions to help me analyze the tweets. I opted into creating my tokenize function and toLower function in the DSString class to simulate an actual string class. 