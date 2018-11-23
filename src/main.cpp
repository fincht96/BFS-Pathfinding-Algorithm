#include <iostream>
#include <array>
#include <vector>
#include <queue>

const int grid_width = 4;
const int grid_height = 4;




// args: grid, grid width, grid height
template <typename G>
void print(G grid, unsigned width, unsigned height)
{
	for (unsigned y = 0; y < height; y++)
	{
		for (unsigned x = 0; x < width; x++)
		{
			std::cout << grid[y*width + x];
		}
		std::cout << std::endl;
	}
}




template <typename G, typename T, typename S>
void searchNeighbours(G& grid, T& trail, S& search_queue, int current_node)
{
	int node;


	// search 'up' (node above current)
	node = current_node - grid_width;

	if ((node >= 0) && (trail[node] == -1) && (grid[node] != '@'))
	{
		search_queue.push(node);		// add to search_queue
		trail[node] = current_node;	// sets searched from to current node
	}


	// search 'right'(node to right of current)
	node = current_node + 1;

	if (((node % grid_width) > 0) && (trail[node] == -1) && (grid[node] != '@'))
	{
		search_queue.push(node);		// add to search_queue
		trail[node] = current_node;	// sets searched from to current node
	}


	// search 'down' (node below current)
	node = current_node + grid_width;

	if ((node < 16) && (trail[node] == -1) && (grid[node] != '@'))
	{
		search_queue.push(node);		// add to search_queue
		trail[node] = current_node;		// sets searched from to current node
	}


	// search 'left' (node to left of current)
	node = current_node - 1;

	if (((current_node % grid_width) > 0) && (trail[node] == -1) && (grid[node] != '@'))
	{
		search_queue.push(node);		// add to search_queue
		trail[node] = current_node;	// sets searched from to current node
	}
}


// args: grid, start position, goal position
template <typename G>
void findShortestPath(G& grid, unsigned start, unsigned goal)	
{
	// used to indicate which nodes have already been searched, and where they have been searched from
	// a node with a 'trail' value of -1 has not been searched
	// a node with 'trail' value of 8 has been searched by node 8
	std::vector<int> trail(grid.size(), -1);		 // (one element for each node in grid)
	
	// used to hold a queue of nodes to be searched next
	std::queue<int> search_queue;

	search_queue.push(0);	// pushes the start node into queue
	trail[0] = 0;			// records starting point in trail

	// if queue is empty then a path was not found
	while (!search_queue.empty())
	{
		int current_node = search_queue.front();		// fetch first element from queue
		
		if (current_node == goal)
		{
			std::vector<int> path;
			
			int node = goal;
			path.insert(path.begin(), node);

			node = trail[goal];
			path.insert(path.begin(), node);
			
			while (node != start)
			{
				// read data at pointed node
				node = trail[path[0]];
			
				// push data to front of path
				path.insert(path.begin(), node);

			}


			std::cout << "\nThe shortest path from A to B (including start and goal) is as follows:\n";

			for (const auto element : path)
				std::cout << element << std::endl;

				
			return;
		}


		// search each of it's neighbours, adding their id if their 'trail' value is -1 and not restricted (i.e. on grid && !'@')
		searchNeighbours(grid, trail, search_queue, current_node);

		search_queue.pop();										// remove first element from queue
	}

	std::cout << "No suitable path found.\n";
	return;
}



int main()
{

	/*
	*	4*4 grid, where each element is labelled as follows:
	*
	*		0,  1,  2,  3
	*		4,  5,  6,  7
	*		8,  9,  10, 11
	*		12, 13, 14, 15
	*	
	*/
	std::array<char, grid_width*grid_height> grid;


	grid.fill('.');

	grid[0] = 'A';
	grid[8] = 'B';

	grid[3] = '@';
	grid[4] = '@';
	grid[5] = '@';
	grid[7] = '@';
	grid[9] = '@';

	print(grid, grid_width, grid_height);

	findShortestPath(grid, 0, 8);

	std::cin.get();

	return 0;
}

