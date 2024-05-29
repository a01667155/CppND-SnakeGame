#include "Score.h"
#include<fstream>
#include <sstream>
#include<iostream>
#include<vector>
 const std::string score_filename = "high_scores.txt";
void updateHighScores(const ScoreEntry& newEntry, std::vector<ScoreEntry>& scores) {
    scores.emplace_back(newEntry);
    std::sort(scores.begin(), scores.end());
    if (scores.size() > 5) {
        scores.pop_back();
    }
}

void readScores(std::vector<ScoreEntry>& scores) {
    std::ifstream infile(score_filename);
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            std::istringstream iss(line);
            ScoreEntry entry;
            if (iss >> entry.name >> entry.score) {
                scores.emplace_back(entry);
            }
        }
        infile.close();
    }
}

void writeScores(const std::vector<ScoreEntry>& scores) {
    std::ofstream outfile(score_filename);
    if (outfile.is_open()) {
        for (const auto& entry : scores) {
            outfile << entry.name << " " << entry.score << std::endl;
        }
        outfile.close();
    }
}
void DisplayHighScores(std::vector<ScoreEntry>& scores){
    std::cout<<"***Highest Scores***\n";
    for (int i = 0; i <scores.size(); ++i)
    {
        std::cout<<i+1<<" "<<scores[i].name<<" "<<scores[i].score<<"\n";
    }
    
}

void CheckHighScore(int score){
    std::vector<ScoreEntry> scores;

    // Check if the file exists and read the existing high scores if it does
    std::ifstream infile(score_filename);
    if (!infile.good()) {
        // If the file doesn't exist, create it with some initial values
        std::ofstream outfile(score_filename);
        if (outfile.is_open()) {
            outfile << "NoName 0\nNoName 0\nNoName 0\nNoName 0\nNoName 0\n";  // Initial scores
            outfile.close();
        }
    }
    infile.close();

    // Read the existing or initial high scores
    readScores(scores);
    for (int i = 0; i < scores.size(); ++i)
    {
      if (scores[i].score<score)
      {
        ScoreEntry newEntry;
      newEntry.score=score;
      std::cout << "Enter the player's name: ";
      std::cin >> newEntry.name;
      updateHighScores(newEntry, scores);
      writeScores(scores);    // Write the updated high scores back to the file
      DisplayHighScores(scores);
      break;
      }
    }
    
}