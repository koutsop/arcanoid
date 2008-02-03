/*
 * author: koutsop
 */
//TODO tropo na diabazoume ola ta terrain pou uparxoun
#include <string>
#include <cassert>

#include "Game.h"

#define BUFF_SZ			20321
#define PARSE_ONE_SEC	1

#define CONFIG_FILE		"./configs_files/game.cfg"
#define BUFFER_IMAGE	"./images/bufferEditorsScreen.bmp"
#define BAGROUND_IMAGE	"./images/editorsScreen.bmp"

#define BALL			"ball"
#define WALL_12			"upper_wall"
#define WALL_3			"right_wall"
#define WALL_6			"down_wall"
#define WALL_9			"left wall"

#define PAYER_ONE 1
#define PAYER_TWO 2

static void InitiallizingAllegro(void){
	//Innits
	allegro_init();
	install_timer();
	install_keyboard();		// Initialize keyboard routines
	install_mouse();

	set_color_depth(16);	// Set the color depth
	//set_gfx_mode(GFX_AUTODETECT, 640,480,0,0); 
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 640,480,0,0); // Change our graphics mode to 640x480
	return;
}
/////////////////////////////////////////////////////////////////////


//constructor
Game::Game(void){
	currTime	= 0;
	currLevel	= 0;
	InitiallizingAllegro();
}

//Destructor
Game::~Game(){
	delete bitmaps;
	delete spriteH;
	delete terrain;
	delete filmsInfo;
	delete collisionC;
	delete animationFH;
	delete inputManager;
}
/////////////////////////////////////////////////////////////////////



void Game::InitiallizingFilmsInfo(){
	set_config_file(CONFIG_FILE);
	string filmsPath = get_config_string("GENERAL", "films", "");
	if( !filmsPath.compare("") ) { assert(0); }

	filmsInfo = new LoadFilmsInfo(filmsPath.c_str());
	assert(filmsInfo);
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::InitiallizingBitmapLoader(void){
	assert(filmsInfo);
	bitmaps = new BitmapLoader();
	assert(bitmaps);
	bitmaps->LoadFilms(*(filmsInfo));
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::InitiallizingAnimationFilmHolder(void) {
	set_config_file(CONFIG_FILE);
	string bboxesPath = get_config_string("GENERAL", "animationHolder", "");
	if( !bboxesPath.compare("") ) { assert(0); }

	animationFH = new AnimationFilmHolder(bboxesPath, (*filmsInfo), (*bitmaps));
	assert(animationFH);
	return;
}
/////////////////////////////////////////////////////////////////////



/* precodition: Prepei na exei dimiourgi8ei o animation Film Holder
			  : o collision Checker o sprite Holder kai telos o animation Holder
 */
Board * Game::CreatingBoard(int playerNo){
	int x, y;
	string filmID;
	set_config_file(CONFIG_FILE);
	
	x		= get_config_int("BOARD", "start_x", -1);
	y		= get_config_int("BOARD", "start_y", -1);
	filmID	= get_config_string("FILMS", "board", "");
	
	if( !filmID.compare("") ) { assert(0); }
	if( (x == -1) || (y == -1)) { assert(0); }

	Board *theBoard = new Board( x, y, 
							  const_cast<AnimationFilm *>(animationFH->GetFilm(filmID)), 
							  playerNo);
	assert(theBoard);
	collisionC->AddMovable(dynamic_cast<Sprite *>(theBoard));
	spriteH->Insert(BOARD, dynamic_cast<Sprite *>(theBoard));

	//Add to animation Holder
	movBoard = new MovingAnimation(x, y, 1, true, countAnimationID);
	countAnimationID++;
	animationH->Insert(BOARD, movBoard );
	
	//Add to animator Holder
	board = new MovingAnimator();
	AnimatorHolder::Register(board);

	return theBoard;
}
/////////////////////////////////////////////////////////////////////


/* precodition: Prepei na exei dimiourgi8ei o animation Film Holder
			  : o collision Checker o sprite Holder kai telos o animation Holder
 */
Ball * Game::CreatingBall(void){
	int x, y;
	string filmID;
	set_config_file(CONFIG_FILE);
	
	x		= get_config_int("BALL", "start_x", -1);
	y		= get_config_int("BALL", "start_y", -1);
	filmID	= get_config_string("FILMS", "ball", "");
	
	if( !filmID.compare("") ) { assert(0); }
	if( (x == -1) || (y == -1)) { assert(0); }
	
	Ball *theBall = new Ball( x, y, 
							  const_cast<AnimationFilm *>(animationFH->GetFilm(filmID)), 
							  filmID.c_str());
	assert(theBall);
	collisionC->AddMovable(dynamic_cast<Sprite *>(theBall));
	spriteH->Insert(BALL, dynamic_cast<Sprite *>(theBall));

	//Add to animation Holder
	movBall = new MovingAnimation(x, y, 1, true, countAnimationID);
	countAnimationID++;
	animationH->Insert(BALL, movBall );
	
	//Add to animator Holder
	ball = new MovingAnimator();
	AnimatorHolder::Register(ball);

	return theBall;
}
/////////////////////////////////////////////////////////////////////


void Game::DisplayALL(){
	Sprite *board = board = spriteH->GetSprite(BOARD); 
	Sprite *ball = spriteH->GetSprite(BALL);
	
	assert(baground || buffer || board || ball);
	
	blit(baground, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	
	if( board->IsVisible() )
		board->Display(buffer);

	if( ball->IsVisible() )
		ball->Display(buffer);

	terrain->DisplayTerrain(buffer, spriteH);
	blit(buffer , screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::DeleteAll(){
	delete bitmaps;
	delete spriteH;
	delete terrain;
	delete filmsInfo;
	delete collisionC;
	delete animationFH;
	delete inputManager;
}
/////////////////////////////////////////////////////////////////////



void Game::CheckF1(void){
	if(currLevel >= terrain->GetLevelsNo()-1)	//simenh oti eimatse sto teleuteo level kai den kaeni na proxorisoume
			return;
	if( StateHolder::stateKey.Key_F1 ){
		DeleteAll();
		currLevel++;
		AnimatorHolder::Clear();
		countAnimationID = 0;
		CreateAll();
	}
	return;
}
/////////////////////////////////////////////////////////////////////


//precodition: prepei thn prwth fora pou kaloume thn methon na einai
//to fps 0 
static void FPSCalculation(int &fps){
	static unsigned long sec = 0;
	
	if( !sec )  { sec = time((time_t *)0); }		
	else{
		if( (time((time_t *)0)- sec) >= PARSE_ONE_SEC ) {//upologizoume an perase ena sec
			std::cout<<"fps:"<<fps<<std::endl;
			fps = 0;
			sec = 0;
		}
		else	{fps++;} 
	}//else
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::CheckBoardInput(){
	MovingAnimation * mov = dynamic_cast<MovingAnimation*>(animationH->GetAnimation(BOARD));
		
	if( !StateHolder::IsStoped()){
		if( board->HasFinished() ){//8eloume na ton baloume mia mono fora sthn lista me tous ranning
			board->Start(spriteH->GetSprite(BOARD), movBoard, 0);
			AnimatorHolder::MarkAsRunning(board);
		}
		dynamic_cast<Board*>(spriteH->GetSprite(BOARD))->SetKey(StateHolder::stateKey);
		mov->SetDx( inputManager->GetOldMouseX() );
	}
	else{
		if( !board->HasFinished() ){	//8eloume na ton baloume mia mono fora sthn lista me tous suspended
			board->Stop();
			AnimatorHolder::MarkAsSuspended(board);
		}
	}
	return;
}
/////////////////////////////////////////////////////////////////////



void Game::SystemLoopDispatching( bool input ){

	if(StateHolder::IsRunning()){
		if(StateHolder::stateKey.Key_P){
			StateHolder::Pause();
			AnimatorHolder::Pause();
		}
		else{
			if( StateHolder::stateKey.Key_Left || StateHolder::stateKey.Key_Mouse_Left)
				StateHolder::GoLeft();
				
			else if(StateHolder::stateKey.Key_Right || StateHolder::stateKey.Key_Mouse_Right)
				StateHolder::GoRight();
			else
				StateHolder::Stop();

			CheckBoardInput();
			CheckF1();
		}
	}//first if
	else{ //paused
		if(StateHolder::stateKey.Key_P){
			StateHolder::Run();
			AnimatorHolder::Resum();
		}
	}

	return;
}
/////////////////////////////////////////////////////////////////////



void Game::GameLoop(void){
	bool input = false;
	int fps = 0;

	ball->Start(spriteH->GetSprite(BALL), movBall, 0);
	AnimatorHolder::MarkAsRunning(ball);

	while( !key[KEY_ESC] && (currLevel < terrain->GetLevelsNo()) ) {
		SetGameTime();

		input = inputManager->CheckInput();
		collisionC->CollisionCheck();
		AnimatorHolder::Progress(GetGameTime());
		collisionC->CleanUp();
		terrain->BricksCleanUp(spriteH);
		DisplayALL();
		FPSCalculation(fps);
		SystemLoopDispatching(input);
		AnimatorHolder::printSize();//Na diagrafei kata thn paradwsh
	}
	return;
}

void Game::CreateAll(void){
	spriteH			= new SpriteHolder();
	animationH		= new AnimationHolder();
	collisionC		= new CollisionChecker();
	inputManager	= new InputManager();
	assert(spriteH || collisionC || inputManager);

	InitiallizingFilmsInfo();
	InitiallizingBitmapLoader();
	InitiallizingAnimationFilmHolder();

	terrain = new Terrain(CONFIG_FILE, animationFH, collisionC, animationH, spriteH);
	assert(terrain);

	buffer		= bitmaps->Load(BUFFER_IMAGE);
	baground	= bitmaps->Load(BAGROUND_IMAGE);

	theBall	 = CreatingBall();
	theBoard = CreatingBoard(PAYER_ONE);
	countAnimationID = terrain->LoadingTerrain(countAnimationID, currLevel);
	assert(buffer || baground || theBall || theBoard);
	return;
}

void Game::PlayGame(void){
	KeyLogger::Init("test.txt");
	KeyLogger::Enable();

	CreateAll();
	StateHolder::Init();
	GameLoop();
	KeyLogger::Terminate();
	return;
}