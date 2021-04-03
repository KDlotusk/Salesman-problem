#include "Ant.h"


Ant::Ant(Town* current, float coef, int increasor){
    setCurrent(current);
    setCoef(coef);
	setIncreasor(increasor);

	if(current != nullptr){
		addDONE(current);
	}

    cout << "[+] ANT" << endl;
}

Ant::~Ant(){

    cout << "[-] ANT" << endl;
}


void Ant::setCurrent(Town* _current) {
    
    current = _current;
	//no we do not delete
}


void Ant::setTODO(vector<Town*> TAB){
	TODO.clear();
    for(size_t k = 0; k < TAB.size(); k++){
        if(!ISin(TAB[k], DONE))
            TODO.push_back(TAB[k]);
    }
}

void Ant::addDONE(Town* T){
    DONE.push_back(T);
}

void Ant::clear(){
	auto tmp = DONE[0];
	TODO.clear();
	DONE.clear();
	addDONE(tmp);
	setCurrent(tmp);
}


void Ant::MoveAnt(Town* T) {
	setCurrent(T);
	addDONE(T);

}



float Ant::distance(Town* T) {

    return sqrtf(powf(T->Coos.x - current->Coos.x, 2) + powf(T->Coos.y - current->Coos.y,2));

}

float Ant::distance(Town* T1, Town* T2) {

    return sqrtf(powf(T2->Coos.x - T1->Coos.x, 2) + powf(T2->Coos.y - T1->Coos.y,2));

}
float Ant::distance(Vector2 Coos1, Vector2 Coos2) {

    return sqrtf(powf(Coos2.x - Coos1.x, 2) + powf(Coos2.y - Coos1.y,2));

}

vector<pair<Town*, float>> Ant::calcDistance() {

	vector<pair<Town*, float>> TAB;

	for(size_t k = 0; k < TODO.size(); k++) {
		pair<Town*, float> p = { TODO[k] , distance(TODO[k]) };
		TAB.push_back(p);
	}

	return TAB;
}

int Ant::choice() {

	if(TODO.size() == 0) {
		MoveAnt(DONE[0]);
		return 1;

	}

	else {
		vector<pair<Town*, float>> TAB = calcDistance();
		float Vmin = findLittlest(TAB);

		vector<pair<Town*, float>> pref;

		for(size_t k = 0; k < TAB.size(); k++){
			pref.push_back({TAB[k].first, (Vmin / (TAB[k].second * coef))});
		}

		displayPref(pref);

		vector<int> randomise;
		int somme = 0;
		for(size_t k = 0; k < pref.size(); k++){
			somme += pref[k].second * increasor;
			randomise.push_back(pref[k].second * increasor);
		}

		int randValue = rand()%somme;
		for(size_t k = 0; k < randomise.size(); k++){
			if(randomise[k] >= randValue)
				MoveAnt(pref[k].first);
		}

		return 0;
	}

}


float Ant::findLittlest(vector<pair<Town*, float>> TAB, size_t i){
	float Vmin = TAB[0].second;
	
	for(size_t k = i; k < TAB.size(); k++){
		if(TAB[k].second < Vmin){
			Vmin = TAB[k].second;
		}
	}

	return Vmin;
}

float Ant::findBiggest(vector<pair<Town*, float>> TAB, size_t i){
	float Vmax = TAB[0].second;
	
	for(size_t k = i; k < TAB.size(); k++){
		if(TAB[k].second > Vmax){
			Vmax = TAB[k].second;
		}
	}

	return Vmax;
}

float Ant::pathSize() {
	float total = 0;

	for(size_t k = 0; k < DONE.size() - 1; k++) {
		total += distance(DONE[k], DONE[k+1]);

	}

	return total;
}



bool Ant::ISin(Town* val, vector<Town*> TAB){
    for(size_t k = 0; k < TAB.size(); k++){
        if(TAB[k] == val)
            return true;

    }

    return false;
}

void Ant::print() {

    cout << "\t ANT :" << current->name << endl;

}

//to use only between Begin and End drawing function
void Ant::display() {

    DrawCircleV(current->Coos, 13.0f, {101, 39, 44, 255});

}

void Ant::displayDone() {

    for(size_t k = 1; k < DONE.size(); k++){
        DrawLineV(DONE[k-1]->Coos, DONE[k]->Coos, RAYWHITE);

    }

    for(size_t k = 0; k < DONE.size(); k++){
        DrawCircleV(DONE[k]->Coos, 17.0f, {188, 84, 75, 255});

    }
}

void Ant::displaySetPref(vector<pair<Town*, float>> pref, Vector2 pos, int qte){
	
	for(size_t k = 0; k < qte; k++){
		Vector2 nextPos;

		for(size_t j = 0; j < pref.size(); j++){
			//calcul nextPos
			float L = distance(pos, pref[k].first->Coos) / (qte - k); // should look like it's accelerating

			nextPos.x = ( 1 - L / (10 * sqrt(2))) * pos.x + (L / (10 * sqrt(2)) * pref[k].first->Coos.x);
			nextPos.y = ( 1 - L / (10 * sqrt(2))) * pos.y + (L / (10 * sqrt(2)) * pref[k].first->Coos.y);

			// display
			unsigned char c = (unsigned char)(pref[k].second * 255);
			DrawLineV(pos, nextPos, { 245, 245, 245, c });
		}
	}
}


void Ant::displayPref(vector<pair<Town*, float>> pref, Vector2 pos){

	for(size_t k = 0; k < pref.size(); k++){
		unsigned char c = (unsigned char)(pref[k].second * 255);
		DrawLineV(pos, pref[k].first->Coos, { 245, 245, 245, c });
	}
}