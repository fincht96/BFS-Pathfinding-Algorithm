#include <iostream>
#include <array>
#include <vector>
#include <queue>

const int grid_width = 5;
const int grid_height = 5;
const uint8_t start_pos = 1;
const uint8_t goal_pos = 15;



// args: grid, grid width, grid height
template <typename G>
void print(G grid, unsigned width, unsigned height)
{
	std::cout << std::endl << std::endl;
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
void searchNeighbours(G& grid, T& trail, S& search_queue, const int current_node)
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

	if ((node < grid_width*grid_height) && (trail[node] == -1) && (grid[node] != '@'))
	{
		search_queue.push(node);		// add to search_queue
		trail[node] = current_node;		// sets searched from to current node
	}


	// search 'left' (node to left of current)
	node = current_node - 1;

	if ((((node+1) % grid_width) != 0) && (trail[node] == -1) && (grid[node] != '@'))
	{
		search_queue.push(node);		// add to search_queue
		trail[node] = current_node;	// sets searched from to current node
	}
}


// args: grid, start position, goal position
template <typename G>
auto findShortestPath(G& grid, unsigned start, unsigned goal)
{
	// used to indicate which nodes have already been searched, and where they have been searched from
	// a node with a 'trail' value of -1 has not been searched
	// a node with 'trail' value of 8 has been searched by node 8
	std::vector<int> trail(grid.size(), -1);		 // (one element for each node in grid)

													 
	std::queue<int> search_queue;					// used to hold a queue of nodes to be searched next

	search_queue.push(start);		// pushes the start node into queue
	trail[start] = start;			// records starting point in trail

							// if queue is empty then a path was not found
	while (!search_queue.empty())
	{
		int current_node = search_queue.front();		// fetch first element from queue

		if (current_node == goal)
		{
			std::vector<int> path;

			int node = goal;
			path.insert(path.begin(), node);


			while (node != start)
			{
				// read data at pointed node
				node = trail[path[0]];

				// push data to front of path
				path.insert(path.begin(), node);


			}

			return path;
		}


		// search each of it's neighbours, adding their id if their 'trail' value is -1 and not restricted (i.e. on grid && !'@')
		searchNeighbours(grid, trail, search_queue, current_node);

		search_queue.pop();										// remove first element from queue
	}

	std::cout << "No suitable path found.\n";
	std::cin.get();
}

// args: grid, start position, goal position
template <typename G>
bool plotShortestPath(G& grid, unsigned start, unsigned goal)
{
	// used to indicate which nodes have already been searched, and where they have been searched from
	// a node with a 'trail' value of -1 has not been searched
	// a node with 'trail' value of 8 has been searched by node 8
	std::vector<int> trail(grid.size(), -1);		 // (one element for each node in grid)


	std::queue<int> search_queue;					// used to hold a queue of nodes to be searched next

	search_queue.push(start);		// pushes the start node into queue
	trail[start] = start;			// records starting point in trail

									// if queue is empty then a path was not found
	while (!search_queue.empty())
	{
		int current_node = search_queue.front();		// fetch first element from queue

		if (current_node == goal)
		{
			std::vector<int> path;

			int node = goal;
			path.insert(path.begin(), node);


			while (node != start)
			{
				// read data at pointed node
				node = trail[path[0]];

				// push data to front of path
				path.insert(path.begin(), node);


			}


			// draws the shortest path on the maze
			for (unsigned i = 0; i < path.size(); i++)
			{


				if ((grid[path[i]] != 'A') && (grid[path[i]] != 'B'))
					grid[path[i]] = '-';
			}


			return true;
		}


		// search each of it's neighbours, adding their id if their 'trail' value is -1 and not restricted (i.e. on grid && !'@')
		searchNeighbours(grid, trail, search_queue, current_node);

		search_queue.pop();										// remove first element from queue
	}

	std::cout << "No suitable path found.\n";
	return false;
}

int main()
{
	/*
	*	5*5 grid, where each element is labelled as follows:
	*
	*		0,  1,  2,  3,  4
	*		5,  6,  7,  8,  9
	*		10, 11, 12, 13, 14 
	*		15, 16, 17, 18, 19
	*		20, 21, 22, 23, 24
	*
	*/

	std::array<char, grid_width*grid_height> grid;


	grid.fill('.');

	grid[start_pos] = 'A';
	grid[goal_pos] = 'B';
	grid[5] = '@';
	grid[7] = '@';
	grid[11] = '@';
	grid[17] = '@';



	std::cout << "\nThe maze is as follows, where A and B are the start and goal position respectfully:";

	// prints the starting grid
	print(grid, grid_width, grid_height);

	// returns the shortest path, if a valid path can be found
	auto path = findShortestPath(grid, start_pos, goal_pos);


	std::cout << "\nThe shortest path from A to B (including start and goal) is as follows:\n";

	for (const auto element : path)
		std::cout << element << std::endl;


	plotShortestPath(grid, start_pos, goal_pos);


	std::cout << "\nThe maze with the shortest path between A and B is shown below, where '-' represents the path taken:";

	// prints the grid with path drawn
	print(grid, grid_width, grid_height);

	std::cin.get();

	return 0;
}
