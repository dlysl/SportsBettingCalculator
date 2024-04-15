#include <iostream>
#include <cmath>

typedef double odds;
typedef double dollars;

int main()
{

    // Program only limited to 2 odds at the moment
    odds implied_odds[2];

    // Running this block over and over until a arb is found (arb_coefficient < 1)
    double arb_coefficient;
    bool found_arb = false; 
    while(found_arb == false)
    {
        // Getting the implied odds (again, this is limited to 2 odds)
        std::cout << "Enter odd 1: ";
        std::cin >> implied_odds[0];
        std::cout << "Enter odd 2: ";
        std::cin >> implied_odds[1]; 

        // Calculating arb coefficient
        arb_coefficient = 0;
        int number_of_odds = sizeof(implied_odds) / sizeof(implied_odds[0]);
        for(int i = 0; i < number_of_odds; i++)
        {
            arb_coefficient += 1 / implied_odds[i];
        }
        
        // Checking if arb is found (if yes, exit loop)
        if(arb_coefficient < 1)
        {
            found_arb = true;
            std::cout << "Arb has been found..." << '\n';
        }
        else
        {
        // if not found, print "Arb not found..."
        std::cout << "Arb not found..." << '\n';
        }

    }

    // Printing out arb coefficient
    std::cout << "Arb Coefficient: " << arb_coefficient << '\n';

    /*
    For us not to get banned, we need to bet some sensible number (e.g., no $213.58)
    If it is divisible by 5, with 0.25 rounding leeway, we can accept it 
    Only going lower at this time and not upper
    */

    // Getting maximum wager of the user
    dollars max_wager = 0; 
    std::cout << "What is your maximum wager? ";
    std::cin >> max_wager;

    // initialising wager array that stores wager value respective of the odd's order 
    // (limited to 2 at this time)
    dollars individual_wager[2];

    // if all wager is divisible by 5 with 0.2 rounding error, display results 
    // We can use an array of wager booleans, and check if above condition is true
    // If all is true, display the value
    bool individual_wager_divisible[2] = {false, false};
    bool all_wager_divisible = false;
    int number_of_wager = sizeof(individual_wager) / sizeof(individual_wager[0]);

    // to be used as total wager placeholder (keeps going down not up at this time)
    dollars current_wager = max_wager;

    while(all_wager_divisible == false)
    {
        // Input individual wager array using current wager
        for(int i = 0; i < number_of_wager; i++)
        {
            individual_wager[i] = (current_wager * (1 / implied_odds[i])) / arb_coefficient;

            // checking if + - 20 of wager value is divisible by 5
            for(int j = 0; j <= 20; j++)
            {
                // just a placeholder for fmod function
                dollars placeholder = individual_wager[i] + (j / 100);
                if(fmod(placeholder, 5) <= 0.2)
                {
                    individual_wager_divisible[i] = true;
                    break;
                }
            }
        }
        
        // Need to come up with a solution to make this one scalable 
        // But for now, this will do 
        if((individual_wager_divisible[0] == true) && (individual_wager_divisible[1] == true))
        {
            all_wager_divisible = true;
        }
        else
        {
            current_wager -= 5;
        }
    }

    // Printing out all wager (make scalable later!)
    std::cout << "Wager 1: " << individual_wager[0] << '\n';
    std::cout << "Wager 2: " << individual_wager[1] << '\n';

    // To be removed later 
    std::cout << individual_wager[0] * implied_odds[0] << '\n';
    std::cout << individual_wager[1] * implied_odds[1];

    return 0;
}
