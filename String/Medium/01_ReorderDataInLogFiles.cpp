/*
Problem:
Given a list of logs, each containing an identifier followed by its content, reorder them so that:
- Letter-logs come first, sorted lexicographically by content and then by identifier when contents
    are equal.
- Digit-logs come after all letter-logs and keep their original relative order.

Approach / Intuition:
- The first character after the identifier and space tells us whether a log is a digit-log or a
    letter-log.
- Store the two types separately. Digit-logs do not need sorting, so appending them in the order
    they were encountered preserves their relative order.
- Sort letter-logs with a custom comparator. Compare their contents first; if the contents match,
    compare their identifiers.
- Append the digit-logs after the sorted letter-logs.

Why this works:
- Separating the logs guarantees that every letter-log appears before every digit-log.
- The comparator applies exactly the required ordering to letter-logs.
- Digit-logs are inserted into their result section in input order, so their relative order is
    unchanged.

Example:
- Input: ["dig1 8 1 5 1", "let1 art can", "dig2 3 6", "let2 own kit dig", "let3 art zero"]
- Sorted letter-logs: ["let1 art can", "let3 art zero", "let2 own kit dig"]
    ("art can" < "art zero" < "own kit dig")
- Digit-logs retain their order: ["dig1 8 1 5 1", "dig2 3 6"]
- Output: ["let1 art can", "let3 art zero", "let2 own kit dig", "dig1 8 1 5 1", "dig2 3 6"]

Complexity: O(n log n) time for sorting the letter-logs and O(n) extra space, where n is the
number of logs.
*/

class Solution {
public:
    vector<string> reorderLogFiles(vector<string>& logs) {
        vector<string> digitVec;
        vector<string> letterVec;
        for(string log:logs){
            int i=log.find(' ')+1;
            if(isdigit(log[i])){
                digitVec.push_back(log);
            }else{
                letterVec.push_back(log);
            }
        }
        sort(letterVec.begin(),letterVec.end(),[](string a,string b){
            int posA=a.find(' ');
            int posB=b.find(' ');

            string contentA=a.substr(posA+1);
            string contentB=b.substr(posB+1);

            if(contentA!=contentB){
                return contentA<contentB;
            }

            string idA=a.substr(0,posA);
            string idB=b.substr(0,posB);

            return idA<idB;
        });

        letterVec.insert(letterVec.end(),digitVec.begin(),digitVec.end());

        return letterVec;
    }
};