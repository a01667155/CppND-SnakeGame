#ifndef Score_H
#define Score_H

#include <fstream>
#include <vector>
#include <algorithm>

struct ScoreEntry {
    std::string name;
    int score;
    // Comparator for sorting
    bool operator<(const ScoreEntry& other) const {
        return score > other.score; // Sort in descending order
    }
};
void CheckHighScore(int score);
void readScores(std::vector<ScoreEntry>& scores);
void updateHighScores(const ScoreEntry& newEntry, std::vector<ScoreEntry>& scores);
void writeScores(const std::vector<ScoreEntry>& scores);
void DisplayHighScores(const std::vector<ScoreEntry>& scores);


#endif
