/*-------------------------------------------
Program 1: 1D cellur Automata
Course: CS 211, Fall 2023, UIC
System: Visual Studio Code
Author: Zaheer Safi
------------------------------------------- */

#include <stdio.h>
#include <stdbool.h> 

const int WORLD_SIZE = 65;

typedef struct cell_struct
{
    bool state[3]; // active status for [left, me, right] cells 
    bool active;   // current active status for this cell
} cell;

// Function to convert an 8-bit integer rule (0-255) to an array of bits
bool setBitArray(bool bitArray[8], int rule) 
{
    if (rule >= 0 && rule <= 255)
    {
        // calculate the binary representation and return true
        for (int i = 0; i < 8; i++)
        {
            int remainder = rule % 2;
            bitArray[i] = remainder;
            rule = rule / 2;
        }
        return true;
    }
    return false; // if bigger then 8 bytes or a negative number return false
}

// check the state array and return the index.
int stateToIndex(bool state[3]) 
{
    int index = 0;
    
    for (int i = 0; i < 3; i++) 
    {
        index = index * 2 + state[i];
    }
    return index;
}

// Function to update the state array for each cell in the world array based on the state to index
void setStates(cell world[WORLD_SIZE]) 
{
    for (int i = 0; i < WORLD_SIZE; i++) 
    {
        int left_index, right_index;
        
        // for the first element the left index in the the last element otherwise element minus one
        if (i == 0)
        {
            left_index = WORLD_SIZE - 1;
        }
        
        else
        {
            left_index = i - 1;
        }
        
        // the right index for the last element is the first element otherwise one more then the current element
        if (i == WORLD_SIZE - 1)
        {
            right_index = 0;
        }
        
        else
        {
            right_index = i + 1;
        }
        
        // update the state array according to the current, left and right element
        world[i].state[0] = world[left_index].active;
        world[i].state[1] = world[i].active;
        world[i].state[2] = world[right_index].active;
    }
}

// function to print new generatoins according to rule's bit array
void evolveWorld(cell world[WORLD_SIZE], bool ruleBitArray[8]) 
{
    // temprary array to hold next generation
    cell temprary_array[WORLD_SIZE];
    
    for (int i = 0; i < WORLD_SIZE; i++) 
    {
        int ruleIndex = stateToIndex(world[i].state);
        temprary_array[i].active = ruleBitArray[ruleIndex];
    }
    
    // Copy the temporary world back to the original world
    for (int i = 0; i < WORLD_SIZE; i++) 
    {
        world[i].active = temprary_array[i].active;
    }
}

int main() 
{
    cell world[WORLD_SIZE];
    int rule; // to take user input for the rule
    bool bitArray[8]; // to store the rule a 8 bit array

    printf("Welcome to the Elementary Cellular Automaton!\n");

    // take the user input try until it is correct
    do
    {
        printf("Enter the rule # (0-255): ");
        scanf("%d", &rule);
    
    } while (!setBitArray(bitArray, rule));

    printf("\nThe bit array for rule #%d is ", rule);
    
    // change the rule to binary representation
    for (int i = 0; i < 8; i++)
    {
        printf("%d", bitArray[7 - i]);
    }
    
    printf("\n\n");
    printf("The evolution of all possible states are as follows:\n");
    printf("|***|   |** |   |* *|   |*  |   | **|   | * |   |  *|   |   |\n");
    
    
    // print the pattren '*' for every 1 and space for every 0
    for (int i = 7; i >= 0; i--)
    {
        if (bitArray[i] == true)
        {
            printf(" |*|    ");
        }
        
        else
        {
            // the last elemtnt should have no spaces in the end
            if (i == 0)
            {
                printf(" | |");
            }
            
            else
            {
                printf(" | |    ");
            }
        }
    }

    printf("\n\n");

    // take the user input to print how many generations
    int generations;
    
    printf("Enter the number of generations: ");
    scanf("%d", &generations);
    printf("\n");
    
    // intialize the world array with zeros except 1 in the middle
    for (int i = 0; i < WORLD_SIZE; i++) 
    {
        if (i == WORLD_SIZE / 2) 
        {
            world[i].active = true;
        } 
        else 
        {
            world[i].active = false;
        }
    }
    
    // if the user input for generation is zero just print out the world array with intizlized values
    if (generations == 0)
    {
        printf("Initializing world & evolving...\n");
        for (int i = 0; i < WORLD_SIZE; i++)
        {
            if (world[i].active == true)
            {
                printf("*");
            }
            
            else
            {
                printf(" ");
            }
        }
    }
    
    else
    {
        printf("Initializing world & evolving...\n");
        
        // evolve world for the inputed amount of generations
        for (int g = 0; g < generations; g++) 
        {
            // print the intialized world array
            for (int i = 0; i < WORLD_SIZE; i++) 
            {
                if (world[i].active)
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");

            // calculate the new states
            setStates(world);

            // next generation
            evolveWorld(world, bitArray);
        }
    }
    
    return 0;
}
