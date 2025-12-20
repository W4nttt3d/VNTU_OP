#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>

const int LINE_WIDTH = 20;

std::string justifyLine(const std::vector<std::string>& words, int wordsLen) 
{
    if (words.empty()) return "";
    if (words.size() == 1) return words[0];

    int spacesNeeded = LINE_WIDTH - wordsLen;    
    int gaps = static_cast<int>(words.size()) - 1;
    int baseSpaces = spacesNeeded / gaps;
    int extraSpaces = spacesNeeded % gaps;

    std::string line;
    for (size_t i = 0; i < words.size(); ++i) 
    {
        line += words[i];
        if (i < static_cast<size_t>(gaps)) 
        {
            int thisGap = baseSpaces + (extraSpaces-- > 0 ? 1 : 0);
            line.append(thisGap, ' ');
        }
    }
    return line;
}

std::string joinWithSingleSpaces(const std::vector<std::string>& words) 
{
    if (words.empty()) return "";
    std::string line = words[0];
    for (size_t i = 1; i < words.size(); ++i) 
    {
        line += ' ';
        line += words[i];
    }
    return line;
}

int main() {
    std::ifstream fin("F1.txt");
    std::ofstream fout("F2.txt");

    if (!fin.is_open() || !fout.is_open()) {
        std::cerr << "File open error\n";
        return 1;
    }

    std::string word;
    std::vector<std::string> words; 
    int wordsLen = 0;              
    int currentLineLen = 0; 

    while (fin >> word) 
    {
        if (words.empty()) 
        {
            words.push_back(word);
            wordsLen = static_cast<int>(word.length());
            currentLineLen = wordsLen;
        }
        else 
        {
            if (currentLineLen + 1 + static_cast<int>(word.length()) <= LINE_WIDTH) 
            {
                words.push_back(word);
                wordsLen += static_cast<int>(word.length());
                currentLineLen += 1 + static_cast<int>(word.length()); 
            }
            else 
            {
                if (words.size() == 1) 
                {
                    fout << words[0] << '\n';
                }
                else 
                {
                    if (wordsLen < LINE_WIDTH) fout << justifyLine(words, wordsLen) << '\n';
                    else fout << joinWithSingleSpaces(words) << '\n';
                }

                words.clear();
                words.push_back(word);
                wordsLen = static_cast<int>(word.length());
                currentLineLen = wordsLen;
            }
        }
    }

    if (!words.empty())
    {
        if (words.size() == 1)
        {
            fout << words[0] << '\n';
        }
        else
        {
            if (wordsLen < LINE_WIDTH)
            {
                fout << justifyLine(words, wordsLen) << '\n';
            }
            else
            {
                fout << joinWithSingleSpaces(words) << '\n';

            }

        }
    }

    fin.close();
    fout.close();
    return 0;
}