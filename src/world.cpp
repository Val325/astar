class Enviroment{
    private:
        SDL_Window* win;
        SDL_Renderer* ren;
        SDL_Rect Player;
        SDL_Rect Goal;
        std::vector<ImageCell> Cells;
        int sizeCells;
        int sizeCell;
        std::map<int, std::vector<Node>> adjCells;
        std::map<int, std::vector<NodeAstar>> adjCellsAstar;
    public:
        Enviroment(SDL_Window* window, SDL_Renderer* render, int sizeAllCells){
            win = window;
            ren = render;
            sizeCells = sizeAllCells;
            
            ImageCell cellOpen(win, ren);
            cellOpen.loadTexture("resource/images/cellopen.bmp");
            cellOpen.setSize(sizeCell, sizeCell);
            cellOpen.setWindow(win);
            cellOpen.setRender(ren);
            
            Cells.resize(sizeCells);
            for (int i = 0; i <= sizeCells; i++){
                Cells.push_back(cellOpen);
            }
        }
        void SetCellSize(int size){
            sizeCell = size;
        }
        void GenerateCells(int xsize, int ysize){
            std::random_device dev;
            std::mt19937 rng(dev());
            std::uniform_int_distribution<std::mt19937::result_type> ran(0,3);
            
            int x = 0;
            int y = 0;
            for (int i = 0; i < sizeCells; i++){
                Cells[i].setId(i);
                Cells[i].setPosition(x * sizeCell,y * sizeCell);
                Cells[i].setWindow(win);
                Cells[i].setRender(ren);
                Cells[i].setPositionGrid(x, y);
                Cells[i].setSize(sizeCell, sizeCell);

                (ran(rng) == 0) ? Cells[i].setCollide(true): Cells[i].setCollide(false);
                //Cells[i].setCollide(false);
                (Cells[i].getCollide() == true) ? Cells[i].loadTexture("resource/images/cellobstacle.bmp"): Cells[i].loadTexture("resource/images/cellopen.bmp");
                
                x++;
                // x = 8
                if (x == xsize){
                    x = 0;
                    y++;
                }
                // y == 6
                if (y == ysize){
                    y = 0;
                }
                //std::cout << "random: " << ran(rng) << std::endl;
            }
        }
        void setGoal(SDL_Rect goalData){
            Goal = goalData;
        }
        void setPlayer(SDL_Rect playerData){
            Player = playerData; 
        }
        void GenerateGraph(int xsize, int ysize){            
            int x = 0;
            int y = 0;
            for (int i = 0; i < sizeCells; i++){
                std::vector<Node> sides;
                Node side;
                //std::cout << "Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                //std::cout << "Number : " << i << " Position X : " << Cells[i].GetPositionGridX() << " Position Y : " << Cells[i].GetPositionGridY() << std::endl;  
                for (int j = 0; j < sizeCells; j++){
                //UP
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() - 1){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl;

                        side.value = Cells[j].getId();
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;
                        side.f = 0;
                        if (!Cells[j].getCollide()) sides.push_back(side); 
                    }
                    //DOWN
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() + 1){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                        side.value = Cells[j].getId();
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;
                        side.f = 0;
                        if (!Cells[j].getCollide()) sides.push_back(side);                  
                    }
                    //LEFT
                    if (x == Cells[j].GetPositionGridX() - 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                        side.value = Cells[j].getId();
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;
                        side.f = 0;
                        if (!Cells[j].getCollide()) sides.push_back(side);                   
                    }
                    //RIGHT
                    if (x == Cells[j].GetPositionGridX() + 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl;  
                        side.value = Cells[j].getId();
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;
                        side.f = 0;
                        if (!Cells[j].getCollide()) sides.push_back(side);                 
                    }
                }
                //auto it = std::unique(sides.begin(), sides.end());
                //sides.erase(it, sides.end());
                //std::cout << "Sides: " << i << std::endl;
                //for (auto& side : sides) { 
                    //std::cout << "Num: " << i << " Edges: " << side << std::endl; 
                //}
                /*for (auto& side : adjCells) { 
                    std::cout << "Num: " << i << " Edges: " << sides.size() << std::endl; 
                }*/
                adjCells.insert(make_pair(i, sides)); 
                x++;
                // x = 8
                if (x == xsize){
                    x = 0;
                    y++;
                }
                // y == 6
                if (y == ysize){
                    y = 0;
                }
            }

        }
        void GenerateGraphAstar(int xsize, int ysize){            
            int x = 0;
            int y = 0;
            int numIter = 0;
            
            //std::cout << "sizeCells: " << sizeCells << std::endl;
            //std::cout << "Cells size: " << Cells.size() << std::endl;

            for (int i = 0; i < sizeCells; i++){
                std::vector<NodeAstar> AdjCells; 
                NodeAstar side; 


                //std::cout << "Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                //std::cout << "Number : " << i << " Position X : " << Cells[i].GetPositionGridX() << " Position Y : " << Cells[i].GetPositionGridY() << std::endl;  
                for (int j = 0; j < sizeCells; j++){
                //UP
                        //std::cout << "two" << std::endl; 

                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() - 1){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl;
                        NodeAstar side(Cells[j].getRect().x, Cells[j].getRect().y);
                        side.id = Cells[j].getId(); 
                        //side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        //side->g = 0;
                        side.h = 0;

                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side); 
                    }
                    //DOWN
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() + 1){
                        //NodeAstar side(Cells[j].getRect().x, Cells[j].getRect().y);
                        side.id = Cells[j].getId(); 
                        //std::cout << "inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl; 
                        //side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        //side->g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                  
                    }
                    //LEFT
                    if (x == Cells[j].GetPositionGridX() - 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //NodeAstar side(Cells[j].getRect().x, Cells[j].getRect().y);
                        side.id = Cells[j].getId(); 
                        //std::cout << "inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl; 
                        //side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        //side->g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                   
                    }
                    //RIGHT
                    if (x == Cells[j].GetPositionGridX() + 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //NodeAstar side(Cells[j].getRect().x, Cells[j].getRect().y);
                        side.id = Cells[j].getId(); 
                        //std::cout << "inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl;  
                        //side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        //side->g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                 
                    }
                }
                //auto it = std::unique(sides.begin(), sides.end());
                //sides.erase(it, sides.end());
                //std::cout << "Sides: " << i << std::endl;
                std::cout << "Gen astar: " << std::endl;
                for (auto& side : AdjCells) { 
                    std::cout << "Num: " << i << " Edges: " << side.id << std::endl; 
                }
                adjCellsAstar.insert(make_pair(i, AdjCells)); 
                x++;
                // x = 8
                if (x == xsize){
                    x = 0;
                    y++;
                }
                // y == 6
                if (y == ysize){
                    y = 0;
                }
                /*
                std::cout << "sizeCells: " << sizeCells << std::endl;
                std::cout << "end" << std::endl;

                std::cout << "x: " << x << std::endl;
                std::cout << "y: " << y << std::endl;
                std::cout << "xsize: " << xsize << std::endl;
                std::cout << "ysize: " << ysize << std::endl;
                */
            }


        }
        std::vector<Node> GenerateGraphAdjCells(int xsize, int ysize){            
            int x = 0;
            int y = 0;
            for (int i = 0; i < sizeCells; i++){
                std::vector<Node> AdjCells;
                Node side;
                //std::cout << "Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                //std::cout << "Number : " << i << " Position X : " << Cells[i].GetPositionGridX() << " Position Y : " << Cells[i].GetPositionGridY() << std::endl;  
                for (int j = 0; j < sizeCells; j++){
                //UP
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() - 1){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl;

                        side.value = Cells[j].getId();
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;
                        side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side); 
                    }
                    //DOWN
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() + 1){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                        side.value = Cells[j].getId();
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;
                        side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                  
                    }
                    //LEFT
                    if (x == Cells[j].GetPositionGridX() - 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                        side.value = Cells[j].getId();
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;
                        side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                   
                    }
                    //RIGHT
                    if (x == Cells[j].GetPositionGridX() + 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl;  
                        side.value = Cells[j].getId();
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;
                        side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                 
                    }
                }
                //auto it = std::unique(sides.begin(), sides.end());
                //sides.erase(it, sides.end());
                //std::cout << "Sides: " << i << std::endl;
                //for (auto& side : sides) { 
                    //std::cout << "Num: " << i << " Edges: " << side << std::endl; 
                //}
                //adjCells.insert(make_pair(i, sides)); 
                x++;
                // x = 8
                if (x == xsize){
                    x = 0;
                    y++;
                }
                // y == 6
                if (y == ysize){
                    y = 0;
                }
                if ((x == xsize) && (y == ysize)){
                    return AdjCells;
                }
            }

        }
        std::vector<NodeAstar> GenerateGraphAdjCellsAstar(int xsize, int ysize){            
            int x = 0;
            int y = 0;
            int numIter = 0;
            
            //std::cout << "sizeCells: " << sizeCells << std::endl;
            for (int i = 0; i < sizeCells; i++){
                std::vector<NodeAstar> AdjCells; 
                NodeAstar side;


                //std::cout << "Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                //std::cout << "Number : " << i << " Position X : " << Cells[i].GetPositionGridX() << " Position Y : " << Cells[i].GetPositionGridY() << std::endl;  
                for (int j = 0; j < sizeCells; j++){
                //UP
                        //std::cout << "two" << std::endl; 

                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() - 1){
                        //std::cout << "UP inside Add i: " << i << " x: " << x << " y: " << y << std::endl;
                        side.id = Cells[j].getId(); 
                        //side.cost = 0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;

                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side); 
                    }
                    //DOWN
                    
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() + 1){
                        side.id = Cells[j].getId(); 
                        //std::cout << "DOWN inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl; 
                        //side.cost = 0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                  
                    }
                    //LEFT
                    if (x == Cells[j].GetPositionGridX() - 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        side.id = Cells[j].getId(); 
                        //std::cout << "LEFT inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl; 
                        //side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                   
                    }
                    //RIGHT
                    if (x == Cells[j].GetPositionGridX() + 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        side.id = Cells[j].getId(); 
                        //std::cout << "RIGHT inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl;  
                        //side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        side.g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                 
                    }
                    //std::cout << "Size AdjCells: " << adjCellsAstar.size() << std::endl; 
                }
                //auto it = std::unique(sides.begin(), sides.end());
                //sides.erase(it, sides.end());
                //std::cout << "Sides: " << i << std::endl;
                for (auto& side : adjCellsAstar) { 
                    std::cout << "Num: " << i << "size AdjCells: " << AdjCells.size() << std::endl; 
                }
                adjCellsAstar.insert(make_pair(i, AdjCells)); 
                x++;
                // x = 8
                if (x == xsize){
                    x = 0;
                    y++;
                }
                // y == 6
                if (y == ysize){
                    y = 0;
                }
                /* 
                std::cout << "sizeCells: " << sizeCells << std::endl;
                std::cout << "end" << std::endl;

                std::cout << "x: " << x << std::endl;
                std::cout << "y: " << y << std::endl;
                std::cout << "xsize: " << xsize << std::endl;
                std::cout << "ysize: " << ysize << std::endl;
                */
                if ((x == 0) && (y == 0)){    
                    return AdjCells;
                }
            }
            /*
*/

        }

        std::vector<NodeAstar> GenerateGraphAdjCellsAstar(int nodeId,int xsize, int ysize){            
            int x = 0;
            int y = 0;
            int numIter = 0;
            std::vector<NodeAstar> AdjCells;
            //std::cout << "sizeCells: " << sizeCells << std::endl;
            for (int i = 0; i < sizeCells; i++){
                
                NodeAstar side;


                //std::cout << "Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                //std::cout << "Number : " << i << " Position X : " << Cells[i].GetPositionGridX() << " Position Y : " << Cells[i].GetPositionGridY() << std::endl;  
                for (int j = 0; j < sizeCells; j++){
                //UP
                        //std::cout << "two" << std::endl; 

                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() - 1){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl;

                        side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        //side->g = 0;
                        side.h = 0;

                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side); 
                    }
                    //DOWN
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() + 1){
                        //std::cout << "inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl; 
                        side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        //side->g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                  
                    }
                    //LEFT
                    if (x == Cells[j].GetPositionGridX() - 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //std::cout << "inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl; 
                        side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        //side->g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                   
                    }
                    //RIGHT
                    if (x == Cells[j].GetPositionGridX() + 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //std::cout << "inside Add i: " << i << " j: "  << j  << " x: " << x << " y: " << y << std::endl;  
                        side.cost = 100.0;
                        side.x = Cells[j].getRect().x;
                        side.y = Cells[j].getRect().y;
                        //side->g = 0;
                        side.h = 0;


                        //side.f = 0;
                        if (!Cells[j].getCollide()) AdjCells.push_back(side);                 
                    }
                }
                //auto it = std::unique(sides.begin(), sides.end());
                //sides.erase(it, sides.end());
                //std::cout << "Sides: " << i << std::endl;
                //for (auto& side : sides) { 
                    //std::cout << "Num: " << i << " Edges: " << side << std::endl; 
                //}
                //adjCells.insert(make_pair(i, sides)); 
                x++;
                // x = 8
                if (x == xsize){
                    x = 0;
                    y++;
                }
                // y == 6
                if (y == ysize){
                    y = 0;
                }
                /*
                std::cout << "sizeCells: " << sizeCells << std::endl;
                std::cout << "end" << std::endl;

                std::cout << "x: " << x << std::endl;
                std::cout << "y: " << y << std::endl;
                std::cout << "xsize: " << xsize << std::endl;
                std::cout << "ysize: " << ysize << std::endl;
                */
                /*
                if ((x == xsize - 1) && (y == ysize - 1)){    
                    return AdjCells;
                }*/
                if ((x == xsize) && (y == ysize)){    
                    return AdjCells;
                }
            }
            /*
*/
        }
        void GenerateGraphMinPath(int xsize, int ysize){            
            int x = 0;
            int y = 0;
            for (int i = 0; i < sizeCells; i++){
                std::vector<Node> sides;
                //std::vector<int> heiristicValue;
                Node side;
                //std::cout << "Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                //std::cout << "Number : " << i << " Position X : " << Cells[i].GetPositionGridX() << " Position Y : " << Cells[i].GetPositionGridY() << std::endl;  
                for (int j = 0; j < sizeCells; j++){
                //UP
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() - 1){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl;
                        side.heuristic = heuristic(Player, Goal);  
                        side.value = Cells[j].getId(); 
                        if (!Cells[j].getCollide()) sides.push_back(side); 
                    }
                    //DOWN
                    if (x == Cells[j].GetPositionGridX() && 
                        y == Cells[j].GetPositionGridY() + 1){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                        side.heuristic = heuristic(Player, Goal);  
                        side.value = Cells[j].getId(); 
                        if (!Cells[j].getCollide()) sides.push_back(side);                  
                    }
                    //LEFT
                    if (x == Cells[j].GetPositionGridX() - 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl; 
                        side.heuristic = heuristic(Player, Goal);  
                        side.value = Cells[j].getId(); 
                        if (!Cells[j].getCollide()) sides.push_back(side);                   
                    }
                    //RIGHT
                    if (x == Cells[j].GetPositionGridX() + 1 && 
                        y == Cells[j].GetPositionGridY() ){
                        //std::cout << "inside Add i: " << i << " x: " << x << " y: " << y << std::endl;  
                        side.heuristic = heuristic(Player, Goal);                          
                        side.value = Cells[j].getId();                         
                        if (!Cells[j].getCollide()) sides.push_back(side);                 
                    }
                }
                //auto it = std::unique(sides.begin(), sides.end());
                //sides.erase(it, sides.end());
                //std::cout << "Sides: " << i << std::endl;
                
                Node minimum = sides[0]; 
                for (int j = 0; j < sides.size(); j++){
                    if (sides[j].value < minimum.value){
                        minimum = sides[j]; 
                    }
                } 
                std::vector<Node> sidesMin;
                sidesMin.push_back(minimum);
                adjCells.insert(make_pair(i, sidesMin)); 
                x++;
                // x = 8
                if (x == xsize){
                    x = 0;
                    y++;
                }
                // y == 6
                if (y == ysize){
                    y = 0;
                }
            }

        }
        std::map<int, std::vector<Node>> getAdjCells(){
            return adjCells; 
        }
        std::map<int, std::vector<NodeAstar>> getAdjCellsAstar(){
            return adjCellsAstar; 
        }
        ImageCell getCellNum(int num){
            return Cells[num]; 
        }
        ImageCell getCellPosition(int numGridX, int numGridY){
            for (int i = 0; i < sizeCells; i++){
                if (Cells[i].GetPositionGridX() == numGridX && 
                    Cells[i].GetPositionGridY() == numGridY){
                    return Cells[i]; 
                }
            }
        }
        std::vector<ImageCell> getCells(){
            return Cells; 
        }
        void Render(){
            for (int i = 0; i < sizeCells; i++){
                Cells[i].render();
            }
        }
};
