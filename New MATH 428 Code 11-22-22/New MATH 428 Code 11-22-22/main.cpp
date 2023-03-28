//
//  main.cpp
//  New MATH 428 Code 11-22-22
//
//  Created by Amanda Lauen on 11/22/22.
//

#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

//For Testing Purposes
//Example 1: State 1 = 7,2,3,5 (no commas when entering)
//           State 2 = 1,6,4,8 (no commas when entering)
//           Gamma: 0.5
//           Rounds: 10

//Example 2: State 1 = 7,2,3,5 (no commas when entering)
//           State 2 = 1, -10, 1, 2 (no commas when entering)
//           Gamma: 1
//           Rounds: 2

//Example 3: State 1: 5 8 6 9
//           State 2: 4 2 6 4
//           Gamma = 0.6
//           Rounds = 3

int main(int argc, const char * argv[])
{
    //User Initialize
    float A11 = 0;
    float A12 = 0;
    float A21 = 0;
    float A22 = 0;

    float B11 = 0;
    float B12 = 0;
    float B21 = 0;
    float B22 = 0;


    //float A [4] = {A11,A12,A21,A22};
    //float B [4] = {B11,B12,B21,B22};

    float gamma;
    int N;

    //Ask user for information
    std::cout << "Welcome to the Game!" << "\n";

    std::cout << "Enter State 1: ";
    std::cin >> A11 >> A12 >> A21 >> A22;
    std:: cout << "\n";

    std::cout << "Enter State 2: ";
    std::cin >> B11 >> B12 >> B21 >> B22;
    std::cout << "\n";

    std::cout << "Enter Probability of State 1 (Gamma): ";
    std::cin >> gamma;
    std::cout << "\n";

    std::cout << "Enter the Number of Games to Play: ";
    std::cin >> N;
    std:: cout << "\n";

    //Initialize everything
    float G11 = 0;
    float G12 = 0;
    float G21 = 0;
    float G22 = 0;

    float g11 = 0;
    float g12 = 0;
    float g21 = 0;
    float g22 = 0;

    //float G [4] = {G11,G12,G21,G22};
    //float g [4] = {g11, g12, g21, g22};


    float p = 0.5;
    float q = 0.5;
    int n = 1;
    float v = 0;
    float w = 0;
    int rose = 1;
    int col = 1;

    srand((unsigned int) time(NULL));

    //Playing the game
    while (n <= N)
    {
        //Chance Board
        float r = (float) rand()/RAND_MAX;
        
        if (r < gamma)
        {
            g11 = A11;
            g12 = A12;
            g21 = A21;
            g22 = A22;
        }
        else
        {
            g11 = B11;
            g12 = B12;
            g21 = B21;
            g22 = B22;
        }

        //Rose's Strategy
        float r_rose = (float) rand()/RAND_MAX;
        
        if (r_rose < p)
        {
            rose = 1;
        }
        else
        {
            rose = 2;
        }

        //Collin's Strategy
        float r_col = (float) rand()/RAND_MAX;
        
        if (r_col < q)
        {
            col = 1;
        }
        else
        {
            col = 2;
        }

        //Payoff
        if (rose == 1 && col == 1)
        {
            w = w + g11;
        }
        if (rose == 1 && col == 2)
        {
            w = w + g12;
        }
        if (rose == 2 && col == 1)
        {
            w = w + g21;
        }
        if (rose == 2 && col == 2)
        {
            w = w + g22;
        }

        //Assign new G (Expected Value Matrix)

        G11 = (((G11*n)-G11+g11)/n);
        G12 = (((G12*n)-G12+g12)/n);
        G21 = (((G21*n)-G21+g21)/n);
        G22 = (((G22*n)-G22+g22)/n);

        //G = (((n-1)/n)*G)+((1/n)*g); //Original formula (did not work becasue of multiplication error)

        //Saddle Check
        if (G11 <= G12 && G11 >= G21)
        {
            v = G11;
            p = 1;
            q = 1;
        }
        else if (G12 <= G11 && G12 >= G22)
        {
            v = G12;
            p = 1;
            q = 0;
        }
        else if (G21 <= G22 && G21 >= G11)
        {
            v = G21;
            p = 0;
            q = 1;
        }
        else if (G22 <= G21 && G22 >= G12)
        {
            v = G22;
            p = 0;
            q = 0;
        }
        else
        {
            //Determine det, trace, ctrace, ddf, and v
            float det = ((G11*G22)-(G12*G21));
            float trace = (G11+G22);
            float ctrace = (G21+G12);
            float ddf = trace - ctrace;
            v = det/ddf;

            //Determine Probabilities
            p = abs((G22-G12)/ddf);
            q = abs((G22-G21)/ddf);
        }

        //Printout (Lots of spaces for printout purposes
        std::cout << "Round: " << n << "\n";
        std::cout << "Expected Game Matrix G: " << G11 << "," << G12 << "\n" << "                        " << G21 << "," << G22 << "\n";
        std::cout << "Value of Game: " << v << "\n";
        std::cout << "Rose's Probability: " << p << "\n";
        std::cout << "Collin's Probability: " << q << "\n";
        std::cout << "Payoff: " << (w/n) << "\n";
        std::cout << "\n";

        n++;
    }

    return 0;
}
