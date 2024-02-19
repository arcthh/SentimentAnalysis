#include "DSString.h"
#include <stdexcept>

using namespace std;
// IMPLEMENT A GETLINE FUNCTIONS

/*
 * Implement the functions defined in DSString.h. You may add more functions as needed
 * for the project.
 *
 * Note that c-strings use `\0` as a terminator symbol
 * but your class should store its length in a member variable. Do not use c-string functions
 * from <string.h> or <cstring> other than for conversion from a c-sting.
 */

/*
DSString::DSString() {
    len = 0; //updated anytime what is inside DSString changes, so you never calculate
    data = nullptr;
}
*/
DSString::DSString()
{
    // constructor for an empty DSString
    len = 0;
    data = new char[1];
    data[0] = '\0';
}

// constructor that converts a c-string
// uses dynamic allocation, this constructor is used in line 11 of test_DSString
// functions need a name for the parameters.
// Three things : find out length of charstr, allocate space, copy data from cstr into DSString
DSString::DSString(const char *cstr)
{
    size_t size = 0;
    // finds the size of the string
    while (cstr[size] != '\0')
    {
        size++;
    }
    // len is internal DSString value
    len = size;
    data = new char[size + 1];

    // copies the data from cstr into DSString
    for (size_t i = 0; i < len; i++)
    {
        data[i] = cstr[i];
    }
    data[len] = '\0';
}

// compiling from terminal
// g++ test.cpp -g -o test

// RULE OF THREE
// copy constructor

/*
definition from : zybooks C++
A copy constructor is another version of a
constructor that can be called with a single pass
by reference argument. The copy constructor is automatically
called when an object is initialized when declared such as MyClass classObject1 = classObject2;,
 or when an object is initialized when allocated via "new" as in newObjectPtr = new MyClass(classObject2);
*/
DSString::DSString(const DSString &source)
{
    len = source.len;
    // data is a char*, so copy the rest
    // create a new char[] for data of len
    data = new char[len + 1];
    // data = source.data only copies pointer to first value
    for (size_t i = 0; i < len; i++)
    {
        data[i] = source[i];
    }
    data[len] = '\0';
}

// need to implement [] operator for DSString to resolve source[i] highlighting

// destructor
DSString::~DSString()
{
    // deletes the c-style array from the heap
    delete[] data;
}

// overloaded assignment operator
/*
Definition : Zybooks C++ (https://learn.zybooks.com/zybook/SMUCS1342GabrielsenSpring2022/chapter/11/section/11)
Each non-pointer member is copied directly from source member
 to destination member. For each pointer member,
 new memory is allocated, the source's
 referenced data is copied to the new memory,
  and a pointer to the new member is assigned as
  the destination member. Allocating and copying data for
  pointer members is known as a deep copy.
  (http://courses.cms.caltech.edu/cs11/material/cpp/donnie/cpp-ops.html)
*/

DSString &DSString::operator=(const DSString &source)
{
    // operator checks for self-assignment
    if (this != &source)
    {
        delete[] data;
        data = new char[source.len];
        len = source.len;
        for (size_t i = 0; i < len; i++)
        {
            data[i] = source[i];
        }
    }
    return *this;
}
// end of rule of three

// returns length of string
size_t DSString::length() const
{
    return len;
}

// make sure index is in range of DSString
// if(index>len -1); this checks to make sure, throw error
//(https://stackoverflow.com/questions/8480640/how-to-throw-a-c-exception)
char &DSString::operator[](size_t index) const
{
    if (index < this->len)
    {
        return data[index];
    }
    else
    {
        throw out_of_range("Index out of bounds");
    }
}

// overloaded operator +
/*
This member function only requires the right operand
as the parameter, because left operand
is the calling object*/

// is returning true;
DSString DSString::operator+(const DSString &rhs) const
{
    // create a new DSString to return with str1 + str2
    DSString newString;
    size_t count = 0;
    // sets the DSString len and data to the proper size and length
    newString.len = this->len + rhs.len;
    newString.data = new char[newString.len + 1];
    delete[] newString.data;
    // copies the result of str1 into newString
    for (size_t i = 0; i < len; i++)
    {
        newString.data[i] = data[i];
        count++;
    }
    // copies str2 into newString
    for (size_t i = count; i < len + count; i++)
    {
        newString.data[i] = rhs.data[i - count];
    }
    newString.data[newString.len] = '\0';
    return newString;
}

bool DSString::operator==(const DSString &source) const
{
    // if the sizes are different, then they are incorrect
    if (this->length() != source.length())
    {
        return false;
    }
    else
    {
        // sizes are corrext, but goes through individual letters
        for (size_t i = 0; i < length(); i++)
        {
            // if letters do not match, false
            if ((*this)[i] != source[i])
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
    return false;
}
// implement < operator
bool DSString::operator<(const DSString &source) const
{
    // CODE WORKED WITH TAs
    for (size_t i = 0; i < min(source.len, this->len); i++)
    {
        if (this->data[i] != source.data[i])
        {
            if (this->data[i] < source.data[i])
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }

    if (this->len < source.len)
    {
        return true;
    }
    return false;
}

// check that null terminator is proper
DSString DSString::substring(size_t start, size_t numChars) const
{
    // make a new DSString and add in the substring to it
    DSString newData;
    newData.len = numChars;
    delete[] newData.data; // delete to avoid memory issues
    newData.data = new char[numChars + 1];

    // goes through the number of characters; skip letters between index 0 and start
    for (size_t i = 0; i < numChars; ++i)
    {
        char c = this->data[start + i];
        newData.data[i] = c;
    }
    newData.data[numChars] = '\0'; // null terminated
    return newData;
}

// lowers words to miniscula
DSString DSString::toLower() const
{
    // code referenced from (https://stackoverflow.com/questions/19300596/implementation-of-tolower-function-in-c)
    DSString lowerStr;
    lowerStr.len = this->len;
    delete[] lowerStr.data;

    lowerStr.data = new char[this->len + 1];

    for (size_t i = 0; i < len; i++)
    {
        // changes to lowercase if the character is A-Z
        if ((this->data[i]) >= 65 && (this->data)[i] <= 90)
        {
            lowerStr.data[i] = this->data[i] + 32;
        }
        // normalize DSString and get rid of anything that is not alpha char
        else if ((this->data[i] < 97 || this->data[i] > 122))
        {
            lowerStr.data[i] = ' ';
        }
        else
        {
            lowerStr.data[i] = this->data[i]; // a-z
        }
    }
    lowerStr.data[len] = '\0';
    return lowerStr;
}

// returns a pointer to data
char *DSString::c_str() const
{
    return this->data;
}

// code for istream and ostream. friend functions
// from Arath Dominguez (https://github.com/SMUCS2341/assignment-2-don-t-be-sentimental-arcthh/blob/main/DSString.cpp)
std::ostream &operator<<(std::ostream &os, const DSString &dStr)
{
    for (size_t i = 0; i < dStr.len; i++)
    {
        char ch = dStr.data[i];
        os << ch;
    }
    return os;
}
//
std::istream &operator>>(std::istream &is, DSString &dStr)
{
    while (!is.eof() && !isspace(is.get()))
    {
        char ch;
        is >> ch;
        dStr += ch;
    }
    return is;
}

// plus equals operator, adds in from the input stream
DSString &DSString::operator+=(const char &rhs)
{
    data[len] = rhs;
    data[len + 1] = '\0';
    len++;
    return *this;
}
// Code referenced from (https://www.geeksforgeeks.org/implementing-of-strtok-function-in-c/)
// creates a vector of DSString and returns after tokenizing a normalized tweet

std::vector<DSString> DSString::tokenize(DSString str)
{
    // tokensInTweet will parse out a tweet based on a space character and return these
    vector<DSString> tokensInTweet;
    // goes through and collects indeces of str based on words
    size_t start = 0;
    size_t end = 0;
    while (end < str.length())
    {
        // collects start of tokens
        while (start < str.length() && str[start] == 32 && str[start] != '\0')
        {
            start++; // ensures that start is not a blank space
        }

        // finds end
        end = start;
        // end will be the space
        while (end < str.length() && ((str[end] != 32 && str[end] != '\n') || str[end] == '\0'))
        {
            end++;
        }
        if (end > str.length())
            break;

        // substr is start, numChars so do end-start
        tokensInTweet.push_back(str.substring(start, end - start));
        start = end + 1;
    }
    return tokensInTweet;
}

// custom getline functions
// uses char arrays in DSStrings to avoid using as CLI
std::istream &getline(std::istream &in, DSString &c, char delim)
{
    // create buffer, use getline function, put into DSString
    char buffer[10000];
    if (in.getline(buffer, 10000, delim))
    {
        c = DSString(buffer);
    }
    return in;
}

std::istream &getline(std::istream &in, DSString &c)
{
    char buffer[10000];
    in.getline(buffer, 10000);
    c = DSString(buffer);
    return in;
}
