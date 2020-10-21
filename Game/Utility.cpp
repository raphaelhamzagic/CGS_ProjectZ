#include "Utility.h"

std::set<int> Utility::WriteHighScore(int score)
{
    // see if exists and read the values
    std::string fileName = "highscores.txt";
    std::ifstream highscoreFile(fileName);
    std::istream_iterator<int> startIterator(highscoreFile), endIterator;
    std::set<int> highscores(startIterator, endIterator);
    highscoreFile.close();

    // if its empty, populate and save
    if (highscores.empty())
    {
        highscores.insert(100);
        highscores.insert(50);
        highscores.insert(20);
        highscores.insert(10);
        highscores.insert(5);

        std::ofstream outFile(fileName);
        std::ostream_iterator<int> outIterator(outFile, "\n");
        std::copy(highscores.begin(), highscores.end(), outIterator);
        outFile.close();
    }

    // write the score
    highscores.insert(score);

    // remove the lowest score
    highscores.erase(highscores.begin());

    // write the highscores
    std::ofstream outFile(fileName);
    std::ostream_iterator<int> outIterator(outFile, "\n");
    std::copy(highscores.begin(), highscores.end(), outIterator);
    outFile.close();

    return highscores;
}
