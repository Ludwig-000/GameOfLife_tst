#include <SFML/Graphics.hpp>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>
std::string model = "3";
sf::VideoMode desktop = sf::VideoMode::getDesktopMode();

const int MATRIX_WIDTH = 3000;
const int MATRIX_HEIGHT = 2000;
const int PIXEL_SIZE = 1; // Each pixel will be 10x10
const int WIDTH = MATRIX_WIDTH * PIXEL_SIZE;
const int HEIGHT = MATRIX_HEIGHT * PIXEL_SIZE;
int timer = 0;
bool matrix[MATRIX_HEIGHT][MATRIX_WIDTH];
bool tempmatrix[MATRIX_HEIGHT][MATRIX_WIDTH];

void addGosperGliderGun(int startX, int startY) {
    // Clear the matrix
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int o = 0; o < MATRIX_WIDTH; o++) {
            matrix[i][o] = false;
        }
    }

    // Coordinates for the Gosper Glider Gun
    int gun[36][2] = {
        {0, 24}, {1, 22}, {1, 24}, {2, 12}, {2, 13}, {2, 20}, {2, 21}, {2, 34}, {2, 35},
        {3, 11}, {3, 15}, {3, 20}, {3, 21}, {3, 34}, {3, 35},
        {4, 0}, {4, 1}, {4, 10}, {4, 16}, {4, 20}, {4, 21},
        {5, 0}, {5, 1}, {5, 10}, {5, 14}, {5, 16}, {5, 17}, {5, 22}, {5, 24},
        {6, 10}, {6, 16}, {6, 24},
        {7, 11}, {7, 15},
        {8, 12}, {8, 13}
    };

    // Place the Gosper Glider Gun in the matrix
    for (int i = 0; i < 36; i++) {
        int row = startY + gun[i][0];
        int col = startX + gun[i][1];
        if (row >= 0 && row < MATRIX_HEIGHT && col >= 0 && col < MATRIX_WIDTH) {
            matrix[row][col] = true;
        }
    }

    // Copy the matrix to tempmatrix
    for (int i = 0; i < MATRIX_HEIGHT; i++) {
        for (int o = 0; o < MATRIX_WIDTH; o++) {
            tempmatrix[i][o] = matrix[i][o];
        }
    }
}

    void addGlider( int startX, int startY) {
        for (int i = 0; i < MATRIX_HEIGHT; i++) {
            for (int o = 0; o < MATRIX_WIDTH; o++)
            {
                matrix[i][o] = false;
            }
        }
        if (startX + 2 < MATRIX_WIDTH && startY + 2 < MATRIX_HEIGHT) {
            matrix[startY][startX + 1] = true;
            matrix[startY + 1][startX + 2] = true;
            matrix[startY + 2][startX] = true;
            matrix[startY + 2][startX + 1] = true;
            matrix[startY + 2][startX + 2] = true;
        }
        else { std::cout << "error loading GLIDER"; }


        for (int i = 0; i < MATRIX_HEIGHT; i++) {
            for (int o = 0; o < MATRIX_WIDTH; o++)
            {
                tempmatrix[i][o] = matrix[i][o];
            }
        }
      
    }
  


void initializeMatrix() {
    //std::cout << "1,2 or 3"<<"\n"<< " :";
    std::string s;
    //std::cin >> s;
    s = model;
    if (s=="3"){
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 1);
        for (int y = 0; y < MATRIX_HEIGHT; ++y) {
            for (int x = 0; x < MATRIX_WIDTH; ++x) {
                bool v = dis(gen);
                matrix[y][x] = v;
                tempmatrix[y][x] = v;
            }
        }
   /* std::srand(static_cast<unsigned int>(std::time(nullptr)));
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            bool v = std::rand() % 2;
            matrix[y][x] = v;
            tempmatrix[y][x] = v;
        }
    }*/
    }
    if (s == "2") {
        addGosperGliderGun(MATRIX_WIDTH/2, MATRIX_HEIGHT/2);
      
    }
    if (s == "1") {
        addGlider(MATRIX_WIDTH / 2, MATRIX_HEIGHT / 2);

    }
    
}
void updateMatrix() {
    // Reset the tempmatrix
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            tempmatrix[y][x] = matrix[y][x];
        }
    }

    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            // Define the eight possible directions
            int directions[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1} };
            int count = 0;

            for (int i = 0; i < 8; ++i) {
                int newRow = y + directions[i][0];
                int newCol = x + directions[i][1];

                // Check if the new position is within bounds
                if (newRow >= 0 && newRow < MATRIX_HEIGHT && newCol >= 0 && newCol < MATRIX_WIDTH) {
                    if (matrix[newRow][newCol]) {
                        ++count;
                    }
                }
            }

            // Apply the rules of Conway's Game of Life
            if (matrix[y][x]) {
                if (count < 2 || count > 3) {
                    tempmatrix[y][x] = 0; // Cell dies
                }
            }
            else {
                if (count == 3 ) {
                    tempmatrix[y][x] = 1; // Cell becomes alive
                }
            }
        }
    }

    // Update "matrix" to the updated tempmatrix
    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
        for (int x = 0; x < MATRIX_WIDTH; ++x) {
            matrix[y][x] = tempmatrix[y][x];
        }
    }

    timer++; // Increment timer once per update cycle
    //std::cout << timer << "\n";
}
//void updateMatrix() {
//    for (int y = 0; y < MATRIX_HEIGHT; ++y) {
//        for (int x = 0; x < MATRIX_WIDTH; ++x) {
//          
//            matrix[y][x] = std::rand() % 2;
//        }
//    }
//}

int main() {
    // Create the window
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "G.O.L.");
    sf::Image icon;
    if (!icon.loadFromFile("icon.png")) {
        std::cerr << "Failed to load icon!" << std::endl;
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    // Initialize the matrix
    initializeMatrix();

    // Set the frame rate
    window.setFramerateLimit(60);
    
    // Main loop
    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update the matrix
        updateMatrix();

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the matrix
        for (int y = 0; y < MATRIX_HEIGHT; ++y) {
            for (int x = 0; x < MATRIX_WIDTH; ++x) {
                
                if (matrix[y][x]) {
                    sf::RectangleShape pixel(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
                    pixel.setPosition(x * PIXEL_SIZE, y * PIXEL_SIZE);
                    pixel.setFillColor(sf::Color::White);
                    window.draw(pixel);

                }
               
              
            }
        }
 

        // Display the content
        window.display();
    }

    return 0;
}
