class ImageCell{
    private:
        int id;
        // coordinate grid
        int xPos;
        int yPos;

        SDL_Window* win;
        SDL_Renderer* ren;

        SDL_Surface* cell;
        SDL_Texture* texcell;
        //coordinate image
        SDL_Rect cellrect;

        std::string pathTexture;
        std::string type;
        
        bool IsWall;

        void loadSurface(std::string pathSurf){
            //pathSurface = pathSurf;
            cell = SDL_LoadBMP(pathSurf.c_str());

	        if (cell == NULL) {
		        fprintf(stderr, "SDL_LoadBMP Error: %s\n", SDL_GetError());
		        SDL_DestroyRenderer(ren);
		        SDL_DestroyWindow(win);
		        SDL_Quit();
		        //return EXIT_FAILURE;
	        }
        }

    public:
        ImageCell(){
            cellrect.x = 0;
            cellrect.y = 0;
            cellrect.w = 0;
            cellrect.h = 0;

            IsWall = false;
        }
        ImageCell(SDL_Window* window, SDL_Renderer* render){
            win = window;
            ren = render;
            cellrect.x = 0;
            cellrect.y = 0;
            cellrect.w = 0;
            cellrect.h = 0;

            IsWall = false;
        }
        void setId(int num){
            id = num;
        }
        int getId(){
            return id;
        }
        void setType(std::string typeObj){
            type = typeObj; 
        }
        void setWindow(SDL_Window* window){
            win = window;
        }
        void setRender(SDL_Renderer* render){
            ren = render;
        }
        void setCollide(bool isSet){
            IsWall = isSet;  
        }
        bool getCollide(){
            return IsWall;
        }
        void loadTexture(std::string pathTex){
            loadSurface(pathTex); 
            texcell = SDL_CreateTextureFromSurface(ren, cell);
	        
            if (texcell == NULL) {
		        fprintf(stderr, "SDL_CreateTextureFromSurface Error: %s\n", SDL_GetError());
		        SDL_FreeSurface(cell);
		        SDL_DestroyRenderer(ren);
		        SDL_DestroyWindow(win);
		        SDL_Quit();
		        //return EXIT_FAILURE;
	        }
        }

        void setPositionGrid(int x, int y){
            xPos = x;
            yPos = y;
        }
        int GetPositionGridX(){
            return xPos;
        }
        int GetPositionGridY(){
            return yPos;
        }
        void setPosition(int x, int y){
            cellrect.x = x;
            cellrect.y = y;
        }
        SDL_Rect getRect(){
            return cellrect; 
        }
        void setSize(int width, int height){
            cellrect.w = width;
            cellrect.h = height;
        }
        void render(){
            if (ren == NULL) std::cout << "ren null" << std::endl;
            if (texcell == NULL) std::cout << "tex null" << std::endl;
            SDL_RenderCopy(ren, texcell, NULL, &cellrect);
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
            leftB = cellrect.x;
            rightB = cellrect.x + cellrect.w;
            topB = cellrect.y;
            bottomB = cellrect.y + cellrect.h;
            
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
