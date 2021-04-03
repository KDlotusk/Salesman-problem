#include "Header.h"
#include "Ant.h"


const int WIDTH = 1600;
const int HEIGHT = 1000;

vector<Town*> TAB;
vector<Ant*> ANTS;



void addAnt(){
	bool verif = false;

	size_t k;
	for(k = 0; k < TAB.size(); k++){
		if(TAB[k]->Coos.x - 17.0f <= float(GetMouseX()) && TAB[k]->Coos.x + 17.0f >= float(GetMouseX())
		&& TAB[k]->Coos.y - 17.0f <= float(GetMouseY()) && TAB[k]->Coos.y + 17.0f >= float(GetMouseY())) {

			verif = true;

			break;
		}
	}
	for(size_t j = 0; j < ANTS.size(); j++){
		if(ANTS[j]->getCurrent() == TAB[k])
			verif = false;
	}
	if(verif == true){
		Ant* a = new Ant(TAB[k]);
		ANTS.push_back(a);
	}
}

int main() {
	
	srand(time(NULL));

	bool simu = false;


	InitWindow(WIDTH, HEIGHT, "Merchant problem");

	SetTargetFPS(60);

	while(!WindowShouldClose()) {
		
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
			Town* v = new Town {{float(GetMouseX()), float(GetMouseY())}, char('A' + TAB.size())};
			TAB.push_back(v);
		}

		if(IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
			addAnt();
		}

		if (IsKeyPressed(KEY_SPACE)){
			simu = true;
		}
		if (IsKeyPressed(KEY_ENTER)){
			for(size_t k = 0; k < ANTS.size(); k++)
				ANTS[k]->clear();
			simu = false;
		}

			

		BeginDrawing();

			ClearBackground({29, 41, 81, 255});
			
			for(size_t k = 0; k < TAB.size(); k++){

				DrawCircleV(TAB[k]->Coos, 17.0f, RAYWHITE);
			}

			if(IsKeyDown(KEY_RIGHT_SHIFT)){
				ClearBackground({29, 41, 81, 255});

				float Vmin = ANTS[0]->pathSize();
				int Imin = 0;
				for(size_t k = 0; k < ANTS.size(); k++){
					if(ANTS[k]->pathSize() < Vmin){
						Vmin = ANTS[k]->pathSize();
						Imin = k;
					}
					
				}

				ANTS[Imin]->displayDone();
				ANTS[Imin]->display();

			}
			else {
				for(size_t k = 0; k < ANTS.size(); k++){
					ANTS[k]->displayDone();
				}
				for(size_t k = 0; k < ANTS.size(); k++){
					ANTS[k]->display();
				}
			}
			
			if(simu == true){
				for(size_t k = 0; k < ANTS.size(); k++){
					ANTS[k]->display();

				
					ANTS[k]->setTODO(TAB);
					ANTS[k]->choice();
				}
			}

		EndDrawing();

		
	}

	//delete 
	for(size_t k = 0; k < TAB.size(); k++){
		delete TAB[k];
	}
	for(size_t k = 0; k < ANTS.size(); k++){
		delete ANTS[k];
	}

	CloseWindow();  
}