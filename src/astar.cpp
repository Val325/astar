

struct Node {
	int id;
    std::vector<Node> children;

    int value;
    int distance;
    int heuristic;

    int x;
    int y;

    int g;
    int h;
    int f;
};


int heuristic(SDL_Rect node, SDL_Rect goal){
    return std::abs(node.x - goal.x) - std::abs(node.y - goal.y);
}

int heuristic(int nodeX, int nodeY, int goalX, int goalY){
    return std::abs(nodeX - goalX) - std::abs(nodeY - goalY);
}



class DFS{
    private:
        int currentNum;
        std::map<int, std::vector<Node>> graph;
        std::map<int, bool> visited;
        std::vector<int> pathCells;
    public:
        DFS(std::map<int, std::vector<Node>> DataGraph, int numspawn){
            //visited.resize(DataGraph.size());
            graph = DataGraph;
            currentNum = numspawn;
        }
        void search(int num){
            visited[num] = true;
            std::vector<Node> allCellsNear = graph[num];

            std::cout << "DFS number: " << num << std::endl;
            pathCells.push_back(num);

            for(auto nextNode : graph[num]) {
                if (!visited[nextNode.value]) {
                    search(nextNode.value);
                }
            }
        }

        std::vector<int> getPath(){
            return pathCells; 
        }
};

//--------------------------------------------------------------------
// A star pathfinding
//--------------------------------------------------------------------
bool diagolanWalk = false;

class NodeAstar{
public:
    int id;
	int x;
	int y;
	float cost;
	int g = 10; //  std::numeric_limits<int>::infinity(); -> Not working
	int h = 0;
	int f = 0;
    NodeAstar* cameFrom = NULL;
    std::vector<NodeAstar> path;
    
    NodeAstar(){}
    NodeAstar(int xpos, int ypos){
        x = xpos;
        y = ypos;
    }
    
    void addParent(NodeAstar node){
        path.push_back(node);
    }    
    std::vector<NodeAstar> GetParent(){
        return path; 
    } 
//	NodeAstar::NodeAstar(int set_x, int set_y, float set_cost);
};
bool operator==(const NodeAstar &n1, const NodeAstar &n2)
{
	return ((n1.x == n2.x) && (n1.y == n2.y));
}
//NodeAstar::NodeAstar(int set_x, int set_y, float set_cost = 1.0f) : x(set_x), y(set_y), cost(set_cost) {}

int ManhattanDist(NodeAstar &n1, NodeAstar &n2)
{
	return std::abs(n1.x - n2.x) + std::abs(n1.y - n2.y);
}

int DiagDist(NodeAstar &n1, NodeAstar &n2)
{
	return std::max(std::abs(n1.x - n2.x), std::abs(n1.y - n2.y));
}

int DistanceHeuristic(NodeAstar &n1, NodeAstar &n2)
{
	if (diagolanWalk)
		return DiagDist(n1, n2);
	else
		return ManhattanDist(n1, n2);
}


bool NodeIn(NodeAstar &node, std::vector<NodeAstar> &nodes)
{
	bool found = false;
	for (size_t i = 0; i < nodes.size(); i++){
		if (node.id == nodes[i].id){
			found = true;
        }
    }
	return found;
}
/*
void ReconstructPath(NodeAstar* goal)
{
	NodeAstar* curNode = goal;
	int count = 0;

	while (curNode->cameFrom != NULL)
	{
		count++;
		curNode = curNode->cameFrom;
	}
}
*/
/*
bool compareNodes(NodeAstar *n1, NodeAstar *n2)
{
	return (n1->f() > n2->f());
}*/

class Astar{
    private:
        //int currentNum;
        //std::map<int, std::vector<Node>> graph;
        //std::map<int, bool> visited;
        std::vector<int> pathCells;
        std::unordered_set<int> path;
        std::map<int, std::vector<NodeAstar>> graph;

        std::vector<NodeAstar> openList;
        std::vector<NodeAstar> closeList;
        std::vector<NodeAstar> to_visit; 
        std::vector<NodeAstar> visited;  
 
        std::vector<NodeAstar*> childern;
         bool isGetGoal;
        NodeAstar* StartNode;
        NodeAstar* EndNode;
        SDL_Rect startData;
        SDL_Rect endData;
    public:

        Astar(std::vector<NodeAstar> childrenGraph, std::map<int, std::vector<NodeAstar>> DataGraph){
            //std::cout << "one" << std::endl; 
            graph = DataGraph;
            
            //childern = childrenGraph;

        }
        void ReconstructPath(NodeAstar *goal)
        {
	        NodeAstar* curNode = goal;

	        while (curNode->cameFrom != nullptr)
	        {
		        curNode = curNode->cameFrom;
                std::cout << "id: " << curNode->id << std::endl; 
	        }
        }
        std::vector<NodeAstar> GetNeighbours(NodeAstar &node){
            std::vector<NodeAstar> neighbours;
            std::vector<NodeAstar> neibor;
            neibor = graph[node.id];
            for (int i = 0; i < neibor.size();i++){
                neighbours.push_back(neibor[i]);
            }
            return neighbours;
        }

        bool search(std::vector<NodeAstar> &nodes, NodeAstar &start, NodeAstar &endNode){
            start.g = 0;
            start.id = 0;
            start.h = DistanceHeuristic(start, endNode);
            EndNode = &endNode; 
            openList.push_back(start);
            //openList.push_back(endNode);

            bool isEnd = false;
            while (!openList.empty() && !isEnd){
		        NodeAstar visiting = openList.front();
                int index = 0;
                for (size_t j = 0; j < openList.size(); j++){
                    if (openList[j].f < visiting.f){
                        visiting = openList[j];
                        index = j; 
                    }
                }

                if (visiting.id == endNode.id){
                    for (int n : path){
                        std::cout << " id: " << n << "\t";
                        pathCells.push_back(n);
                    }
                    std::cout << std::endl;
                    endNode = visiting; 
                    isEnd = true;
                    break;
                } 

                openList.erase(openList.begin() + index);
                closeList.push_back(visiting);
		        std::vector<NodeAstar> neighbours = GetNeighbours(visiting);

                for (size_t i = 0; i < neighbours.size(); i++){
                    int tentativeG = neighbours[i].g + DiagDist(neighbours[i], visiting); 
                    if (NodeIn(neighbours[i], closeList) && tentativeG >= neighbours[i].g){
                        continue;
                    }

                    if (!NodeIn(neighbours[i], openList) || tentativeG < neighbours[i].g){
                        //std::cout << "visiting.id: " << visiting.id << std::endl;
                        path.insert(visiting.id);
                        neighbours[i].g = visiting.g + 1;
                        neighbours[i].h = DiagDist(neighbours[i], endNode);
                        neighbours[i].f = neighbours[i].g + neighbours[i].h;
                        if (!NodeIn(neighbours[i], openList)){
                            openList.push_back(neighbours[i]);
                        }
                    }
                }
            }

            return isEnd;
        }

        std::vector<int> getPath(){
            //pathCells.push_back(47);
            if(std::find(pathCells.begin(), pathCells.end(), EndNode->id) == pathCells.end()) pathCells.push_back(EndNode->id);
            sort(pathCells.begin(), pathCells.end());  
            return pathCells; 
        }
};
