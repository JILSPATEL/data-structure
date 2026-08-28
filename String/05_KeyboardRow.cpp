/*
Problem:
Given a list of words, return the words that can be typed using letters from only one row of the
standard American keyboard.

Approach / Intuition:
- Represent the three keyboard rows as strings: `qwertyuiop`, `asdfghjkl`, and `zxcvbnm`.
- For each word, convert each character to lowercase so uppercase and lowercase letters are treated
    the same.
- Check the word against each keyboard row. If every character is found in a row, the word is
    valid and is added to the answer.
- Keep the original spelling and input order when adding valid words.

Why this works:
- A word can be typed using one row exactly when all of its characters belong to that row.
- Counting the characters found in a row and comparing the count with the word length confirms that
    no character comes from another row. Checking all three rows covers every possible valid word.

Example:
- Input: ["Hello", "Alaska", "Dad", "Peace"]
- "Hello" uses letters from the first and second rows, so it is rejected.
- "Alaska" and "Dad" use only letters from the second row, so they are accepted.
- "Peace" uses letters from multiple rows, so it is rejected.
- Output: ["Alaska", "Dad"]

Complexity: O(n * m) time and O(1) extra space apart from the output, where n is the number of
words and m is the maximum word length.
*/

class Solution {
public:
    vector<string> findWords(vector<string>& words) {
        string row1 = "qwertyuiop";
        string row2 = "asdfghjkl";
        string row3 = "zxcvbnm";

        vector<string> ans;

        for (string str1 : words) {

            int i = 0;
            for (char ch : str1) {
                ch = tolower(ch);
                if (row1.find(ch) != string::npos) {
                    i++;
                }
            }

            if (i == str1.size()) {
                ans.push_back(str1);
                continue;
            }

            i = 0;
            for (char ch : str1) {
                ch = tolower(ch);
                if (row2.find(ch) != string::npos) {
                    i++;
                }
            }

            if (i == str1.size()) {
                ans.push_back(str1);
                continue;
            }

            i = 0;
            for (char ch : str1) {
                ch = tolower(ch);
                if (row3.find(ch) != string::npos) {
                    i++;
                }
            }

            if (i == str1.size()) {
                ans.push_back(str1);
            }
        }

        return ans;
    }
};