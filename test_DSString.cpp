#include <iostream>
#include <vector>
#include <algorithm>

#include "DSString.h"

using namespace std;
// checking functions that work

// VALGRIND : LOSING DATA IN SUBSTRING
int main()
{
    DSString nuStr;
    cout << "Should be 0: " << nuStr.length() << endl;

    DSString myString = "Hello World !24590 hello this is a positive tweet5";
    myString.toLower();
    cout << "lowercase  " << myString << endl;

    vector<DSString> tweetsing = myString.tokenize(myString);
    for (const auto &token : tweetsing)
    {
        std::cout << token << '\n';
    }

    // // this uses the one argument constructor in DSString and then the inherited operator=

    cout << "substr: " << myString.substring(6, 25) << endl;

    DSString a = "testing";
    // problem with the = operator
    // no memory
    DSString b = a;
    cout << "CALLING LENGTH FUNCTION: length of b - " << b.length() << endl;
    cout << "USING []" << b[0] << " should be t" << endl;
    // no memory leaks
    DSString c = a + b;
    cout << "Should be 14 and testing x 2: " << c.length() << "   " << c << endl;

    cout << boolalpha;
    cout << (a == b) << endl;

    // use initialization list (see DSVector.h)
    vector<DSString> strings = {
        DSString("lll"),
        DSString("ddd"),
        DSString("mmm")};

    // find strings
    for (const auto &s : strings)
        cout
            << s << "\n";

    cout << "found ddd: " << (find(strings.begin(), strings.end(), DSString("ddd")) != strings.end()) << endl;
    cout << "found zzz: " << (find(strings.begin(), strings.end(), DSString("zzz")) != strings.end()) << endl;

    // sorting
    sort(strings.begin(), strings.end());

    for (const auto &s : strings)
        cout
            << s << "\n";

    // now we can do more efficient search
    cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << endl;
    cout << "found ddd: " << binary_search(strings.begin(), strings.end(), DSString("ddd")) << endl;

    return 0;
}
