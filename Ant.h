#include "Header.h"


class Ant{
private:
    vector<Town*> TODO;
    vector<Town*> DONE;

    Town* current;
    float coef;
	int increasor;

public:
    Ant(Town* current = nullptr, float coef = 6.5f, int increasor = 1000);
    ~Ant();

    void setCurrent(Town* _current);
    Town* getCurrent() const { return current; };

    void setCoef(float _coef) { coef = _coef; };
    float getCoef() const { return coef; };

	void setIncreasor(int _increasor) { increasor = _increasor; };
    int getIncreasor() const { return increasor; };

    void setTODO(vector<Town*>);
    void addDONE(Town*);

	void clear();


	void MoveAnt(Town*);

    float distance(Town*);
    float distance(Town*, Town*);
    float distance(Vector2, Vector2);
    vector<pair<Town*, float>> calcDistance();
    int choice();
    void moving();


	float findLittlest(vector<pair<Town*, float>>, size_t = 0);
	float findBiggest(vector<pair<Town*, float>>, size_t = 0);

	float pathSize();


    bool ISin(Town*, vector<Town*>);

    //display 
    void print();
    void display();
    void displayDone();
    void displaySetPref(vector<pair<Town*, float>>, Vector2 = { -1, -1 }, int = 50);
    void displayPref(vector<pair<Town*, float>>, Vector2 = { -1, -1 });
};