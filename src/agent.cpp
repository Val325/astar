class agentAI{
    private:
        int moveSizeCell;
        //grid
        int x;
        int y;
        
        //constraint cells
        int xSizeCells;
        int ySizeCells;

        SDL_Window* win;
        SDL_Renderer* ren;

        SDL_Surface* agentSurface;
        SDL_Texture* textureAgent;
        //coordinate image
        SDL_Rect AgentRect;

        std::string pathTexture;
        
        void loadSurface(std::string pathSurf){
            agentSurface = SDL_LoadBMP(pathSurf.c_str());

	        if (agentSurface == NULL) {
		        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
		        SDL_DestroyRenderer(ren);
		        SDL_DestroyWindow(win);
		        SDL_Quit();
	        }
        }
    public:
        agentAI(int xpos, int ypos){
            moveSizeCell = 100;
            x = xpos;
            y = ypos;
        }
        void setWindow(SDL_Window* window){
            win = window;
        }
        void setRender(SDL_Renderer* render){
            ren = render;
        }
        void loadTexture(std::string pathTex){
            loadSurface(pathTex); 
            textureAgent = SDL_CreateTextureFromSurface(ren, agentSurface);
	        
            if (textureAgent == NULL) {
		        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		        SDL_FreeSurface(agentSurface);
		        SDL_DestroyRenderer(ren);
		        SDL_DestroyWindow(win);
		        SDL_Quit();
	        }
        }
        int getXposition(){
            return x;
        }
        int getYposition(){
            return y;
        }
        void setConstraint(int xconstr, int yconstr){
            xSizeCells = xconstr;
            ySizeCells = yconstr;
        }
        void setPosition(int x, int y){
            AgentRect.x = x;
            AgentRect.y = y;
        }
        SDL_Rect getPosition(){
            return AgentRect; 
        }
        void setSize(int width, int height){
            AgentRect.w = width;
            AgentRect.h = height;
        }
        void MoveUp(){
            int yTopPos = 0;
            if (y > yTopPos){
                y--;
                AgentRect.y = y * moveSizeCell;
            }
        }
        void MoveDown(){
            int yTopPos = 0;
            int offsetY = 1;
            if (y < ySizeCells - offsetY){
                y++;
                AgentRect.y = y * moveSizeCell;
            }
        }
        void MoveRight(){
            int xTopPos = 0;
            if (x <= ySizeCells){
                x++;
                AgentRect.x = x * moveSizeCell;
            }
        }
        void MoveLeft(){
            int xTopPos = 0;
            if (x > xTopPos){
                x--;
                AgentRect.x = x * moveSizeCell;
            }
        }
        void RandomDirectionMove(Enviroment universe){
            ImageCell cellNearbyPlayer;
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> ran(0,3);
        
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Up
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getYposition() - 1) >= 0){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition() - 1);
            }
            if (!cellNearbyPlayer.getCollide()){ 
                if (ran(rng) == 0) MoveUp();
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Down
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getYposition() + 1) < ySizeCells){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition() + 1);
            }
            if (!cellNearbyPlayer.getCollide()){                                
                if (ran(rng) == 1) MoveDown();
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Right
            ///////////////////////////////////////////////////////////////////////////////////////////////

            if ((getXposition() + 1) < xSizeCells){ 
                cellNearbyPlayer = universe.getCellPosition(getXposition() + 1, getYposition());
            }
            if (!cellNearbyPlayer.getCollide()){
                if (ran(rng) == 2) MoveRight();
            }
            /////////////////////////////////////////////////////////////////////////////////////////////// 
            // Left
            ///////////////////////////////////////////////////////////////////////////////////////////////
            if ((getXposition() - 1) == -1){
                cellNearbyPlayer = universe.getCellPosition(getXposition(), getYposition());
            }else{
                cellNearbyPlayer = universe.getCellPosition(getXposition() - 1, getYposition());
            }
            if (!cellNearbyPlayer.getCollide()){
                if (ran(rng) == 3) MoveLeft();
            }
        }
        void Render(){
            if (ren == NULL) std::cout << "ren agent null" << std::endl;
            if (textureAgent == NULL) std::cout << "tex agent null" << std::endl;
            //std::cout << "x: " << x << "y: " << y << "w: " << x << "h: " << std::endl;
            SDL_RenderCopy(ren, textureAgent, NULL, &AgentRect);
        }
        bool checkCollision(SDL_Rect player_rect){
            //The sides of the rectangles
            int leftA, leftB;
            int rightA, rightB;
            int topA, topB;
            int bottomA, bottomB;

            //Calculate the sides of rect A
            leftA = player_rect.x;
            rightA = player_rect.x + player_rect.w;
            topA = player_rect.y;
            bottomA = player_rect.y + player_rect.h;

            //Calculate the sides of rect B
            leftB = AgentRect.x;
            rightB = AgentRect.x + AgentRect.w;
            topB = AgentRect.y;
            bottomB = AgentRect.y + AgentRect.h;
            
            //If any of the sides from A are outside of B
            if( bottomA <= topB ){
                return false;
            }

            if( topA >= bottomB ){
                return false;
            }

            if( rightA <= leftB ){
                return false;
            }

            if( leftA >= rightB ){
                return false;
            }

            //If none of the sides from A are outside B
            return true;
        }
};
