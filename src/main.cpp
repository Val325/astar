#include <random>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <map>
#include <unistd.h>
#include <limits>
#include <list>
#include <cmath>
#include <unordered_set>

#include "astar.cpp"
#include "image.cpp"
#include "world.cpp"
#include "agent.cpp"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

int main(void)
{
    srand(time(NULL));
 
    if(TTF_Init() == -1)
    {
        printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
    }

	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_Window* win = SDL_CreateWindow("Q-learning", 100, 100, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (win == NULL) {
		fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}
    
	SDL_Renderer* ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == NULL) {
		fprintf(stderr, "SDL_CreateRenderer Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(win);
		SDL_Quit();
		return EXIT_FAILURE;
	}
    
    int sizeCell = 100;
    int xLenghtCells = SCREEN_WIDTH / sizeCell; 
    int yLenghtCells = SCREEN_HEIGHT / sizeCell;
    
    std::cout << "-------- Debug --------" << std::endl;
    std::cout << "Size x len: " << xLenghtCells << std::endl;
    std::cout << "Size y len: " << yLenghtCells << std::endl; 

    int sizeCells = xLenghtCells * yLenghtCells;
    std::cout << "sizeCells draw: " << sizeCells << std::endl;
    Enviroment world(win, ren, sizeCells);
    agentAI player(0,0);
    agentAI goalEnd(xLenghtCells, yLenghtCells);
    world.SetCellSize(sizeCell);

	SDL_Surface* cellopen = SDL_LoadBMP("resource/images/cellopen.bmp");
	if (cellopen == NULL) {
		fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_Texture* texcellopen = SDL_CreateTextureFromSurface(ren, cellopen);
	if (texcellopen == NULL) {
		fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		SDL_FreeSurface(cellopen);
		SDL_DestroyRenderer(ren);
		SDL_DestroyWindow(win);
		SDL_Quit();
		return EXIT_FAILURE;
	}
	SDL_FreeSurface(cellopen);
    
    Uint32 startTime = 0;
    //Main loop flag
    bool quit = false;
    bool isStartGame = false;
    bool isGame = false;
    bool isStartQlearning = false;
    //bool isLoad = false;
    //Event handler
    SDL_Event e;
    world.GenerateCells(xLenghtCells, yLenghtCells);
    world.GenerateGraph(xLenghtCells, yLenghtCells);
    world.GenerateGraphAstar(xLenghtCells, yLenghtCells);
    world.setPlayer(player.getPosition()); 
    world.setGoal(goalEnd.getPosition()); 
    
    //DFS path(world.getAdjCells(), 0);
    std::vector<Node> cellAdj;
    std::vector<NodeAstar> nodesAstar;

    nodesAstar = world.GenerateGraphAdjCellsAstar(xLenghtCells, yLenghtCells);
    NodeAstar startNode(0 * sizeCell, 0 * sizeCell);
    startNode.id = 0;
	NodeAstar endNode(7 * sizeCell, 5 * sizeCell);
    endNode.id = 47;

    Astar aStar(nodesAstar, world.getAdjCellsAstar());
    std::vector<int> pathData;
   
    player.setPosition(0 * sizeCell, 0 * sizeCell);
    goalEnd.setPosition(7 * sizeCell, 5 * sizeCell);
    goalEnd.setConstraint(xLenghtCells, yLenghtCells);
    goalEnd.setWindow(win);
    goalEnd.setRender(ren);
    goalEnd.loadTexture("resource/images/celldestination.bmp");
    goalEnd.setSize(sizeCell,sizeCell);

    startTime = SDL_GetTicks();
    int graphNum = 0;
    int playerX = 0;
    int playerY = 0;
    bool IsGoal = false;
    bool IsInit = false;

    IsGoal = aStar.search(nodesAstar, startNode, endNode);
 
    while( !quit ){
        pathData = aStar.getPath(); 
        std::vector<ImageCell> CellsAll = world.getCells();
        SDL_RenderClear(ren);

        if (!isStartGame){
            player.setPosition(0, 0);
        }
        player.setConstraint(xLenghtCells, yLenghtCells);
        player.setWindow(win);
        player.setRender(ren);
        player.loadTexture("resource/images/cellhero.bmp");
        player.setSize(sizeCell,sizeCell);

        if ((((SDL_GetTicks() - startTime) * 0.001) > 1.0)){
            graphNum++;
            if (graphNum < pathData.size()){
                playerX = CellsAll[pathData[graphNum]].GetPositionGridX() * sizeCell;
                playerY = CellsAll[pathData[graphNum]].GetPositionGridY() * sizeCell;
            }
            startTime = SDL_GetTicks();
        }
        player.setPosition(playerX, playerY);

        ImageCell cellInsidePlayer;
        ImageCell cellNearbyPlayer;
        world.Render();
        
        goalEnd.Render();
        player.Render();

		SDL_RenderPresent(ren);
        
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 ){
            //User requests quit
            if( e.type == SDL_QUIT ){
                quit = true;
            }
            //If mouse event happened
            if(e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP ){
                int x, y;
                SDL_GetMouseState( &x, &y );
                std::cout << " x: " << x << " y: " << y << std::endl;
            }
        //Get mouse position
        int x, y;
        SDL_GetMouseState( &x, &y );
            //If a key was pressed
              if( e.type == SDL_KEYDOWN ){
                    isStartGame = true;
                    switch( e.key.keysym.sym ){
                        case SDLK_UP:
                            if ((player.getYposition() - 1) >= 0){
                                cellNearbyPlayer = world.getCellPosition(player.getXposition(), player.getYposition() - 1);
                            }
                            if (!cellNearbyPlayer.getCollide()){ 
                                cellInsidePlayer = world.getCellPosition(player.getXposition(), player.getYposition());
                                //std::cout << "x: " << cellInsidePlayer.GetPositionGridX() << " y: " << cellInsidePlayer.GetPositionGridY() << std::endl;                            
                                if (isGame) player.MoveUp();
                            }
                            break;
                        case SDLK_DOWN:
                            if ((player.getYposition() + 1) >= yLenghtCells){
                                break;
                            }
                            cellNearbyPlayer = world.getCellPosition(player.getXposition(), player.getYposition() + 1);
                            if (!cellNearbyPlayer.getCollide()){                                
                                cellInsidePlayer = world.getCellPosition(player.getXposition(), player.getYposition());
                                //std::cout << "x: " << cellInsidePlayer.GetPositionGridX() << " y: " << cellInsidePlayer.GetPositionGridY() << std::endl;
                                if (isGame) player.MoveDown();
                            }
                            break;
                        case SDLK_LEFT:
                            //left cell
                            /*
                            std::cout << "LEFT" << std::endl;                            
                            std::cout << "x: " << player.getXposition() << std::endl;
                            std::cout << "New x: " << player.getXposition() - 1 << std::endl;
                            std::cout << "xLenghtCells: " << xLenghtCells << std::endl;
                            */
                            if ((player.getXposition() - 1) == -1){
                                break;
                            } 
                            cellNearbyPlayer = world.getCellPosition(player.getXposition() - 1, player.getYposition());
                            if (!cellNearbyPlayer.getCollide()){
                                cellInsidePlayer = world.getCellPosition(player.getXposition(), player.getYposition());
                                //std::cout << "x: " << cellInsidePlayer.GetPositionGridX() << " y: " << cellInsidePlayer.GetPositionGridY() << std::endl; 
                                if (isGame) player.MoveLeft();
                            }
                            break;
                        case SDLK_RIGHT:
                            //right cell
                            /*
                            std::cout << "RIGHT" << std::endl;                            
                            std::cout << "X: " << player.getXposition() << std::endl;
                            std::cout << "New X: " << player.getXposition() + 1 << std::endl;
                            std::cout << "XLenghtCells: " << xLenghtCells << std::endl;
                            */
                            if ((player.getXposition() + 1) >= xLenghtCells){
                                break;
                            } 
                            cellNearbyPlayer = world.getCellPosition(player.getXposition() + 1, player.getYposition());
                            if (!cellNearbyPlayer.getCollide()){
                                cellInsidePlayer = world.getCellPosition(player.getXposition(), player.getYposition());
                                //std::cout << "x: " << cellInsidePlayer.GetPositionGridX() << " y: " << cellInsidePlayer.GetPositionGridY() << std::endl;
                                if (isGame) player.MoveRight();
                            }
                            break;
                        case SDLK_r:
                            world.GenerateCells(xLenghtCells, yLenghtCells);
                            break;
                        case SDLK_SPACE:
                            isStartQlearning = true; 
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                    }
                    
                }


            }

        }


	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();

	return EXIT_SUCCESS;
}
