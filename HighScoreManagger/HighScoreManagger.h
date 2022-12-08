#pragma once
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
#include <ctime>
#include <SFML/Graphics.hpp>

using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ios;
using std::vector;
using std::cin;
using std::string;
using std::ofstream;
using std::to_string;
using std::sort;
using std::greater;
using std::less;
using std::srand;

//class scores
class Scores {
public:
	Scores() {};
	Scores(string name, int points) {
		this->name = name;
		this->points = points;
	}
	virtual ~Scores() {};
	string name = "";
	int points = 0;
	int get_points() const { return points; }
	void print() { cout << "Name: " << name << "---------" << "Score: " << points << endl; }
	bool operator > (const Scores& score) const { return points > score.points; }
};

//class scores textos

class text_score : public sf::Text {
public:
	int points = 0;
	string name = "";
	bool operator > (const text_score& score) const { return points > score.points; }
	void print() { cout << "Name text: " << name<< "----------" << "Score text: " << points << endl; }

};

class HighScoreManagger
{
private:
	static HighScoreManagger* instance;
	HighScoreManagger() {
		if (!font.loadFromFile("../assets/youmurdererbb_reg.ttf"))
		{
		}	
	};
	virtual ~HighScoreManagger() {};
	vector<Scores>Leadboard;
	vector<text_score>text_leadboard;
	int capacity = 0;
	ofstream f_write;
	ifstream f_read;
	string name_of_file = "Score.bin";
	Scores s_read;
	sf::Font font;
	text_score text;
public:
	static HighScoreManagger* getinstance() {
		if (instance == nullptr) {
			instance = new HighScoreManagger();
			return instance;
		}
		else {
			return instance;
		}
	}
	void create_vector() {
		cout << "Enter your vector capacity:";
		cin >> capacity;
		f_write.open(name_of_file, ios::binary);
		if (f_write.is_open() && !f_write.fail()) {
			f_write.close();
		}
	}
	Scores dev_score(string name, int points) {
		Scores newinstance;
		newinstance.name = name;
		newinstance.points = points;
		return newinstance;
	}
	void add_score(Scores newscore) {
		//pusheo scores
		Leadboard.push_back(newscore);
		//pusheo text_score
		text.setFont(font);
		text.setFillColor(sf::Color::Red);
		text.setCharacterSize(45);
		text.points = newscore.points;
		text.name = newscore.name;
		text.setString(string("Name: " + newscore.name + "----------" + "Score: " + to_string(newscore.points)));
		text_leadboard.push_back(text);
		//sort scores and text_score
		std::sort(Leadboard.begin(), Leadboard.end(), std::greater<Scores>());
		std::sort(text_leadboard.begin(), text_leadboard.end(), std::greater<text_score>());
		//delete scores
		if (Leadboard.size() > capacity) {
			Leadboard.erase(Leadboard.begin() + capacity, Leadboard.end());
			text_leadboard.erase(text_leadboard.begin() + capacity, text_leadboard.end());
		}
		//sort texts in windows
		for (int i = 0;i< text_leadboard.size();i++) {
			text_leadboard[i].setPosition(0,30 * i);
		}
		//write scores
		write_vector();
	}
	void write_vector() {
		f_write.open(name_of_file, ios::binary);
		if (f_write.is_open() && !f_write.fail()) {
			for (int i = 0; i < Leadboard.size(); i++) {
				f_write.write((char*)&Leadboard[i], sizeof(Scores));
			}
			f_write.close();
		}
		else {
			cout << "the file cannot open (write)" << endl;
		}
	}
	void read_vector() {
		f_read.open(name_of_file,ios::binary);
		if (f_read.is_open() && !f_read.fail()) {
			for (int i = 0; i < Leadboard.size(); i++) {
				f_read.read((char*)&s_read, sizeof(Scores));
				s_read.print();
			}
		}
		else {
			cout << "The file is cannot open (read)" << endl;
		}
		f_read.close();
	}
	void draw_text(sf::RenderWindow& window) {
		for (auto text_for : text_leadboard) {
			window.draw(text_for);
		}
	}
};

