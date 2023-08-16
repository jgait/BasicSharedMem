#pragma once // Ensure inclusion only once

/*  This is the struct which defines the size and layout for our memory mapped file (shared memory)
*   Think of it a bit as being a bit like a template for our shared memory. It defines what our database looks like
*   and how it is layed out. Every process accessing the memory must include this file in order to use it 
*   when connecting to the shared memory. We can add onto this shared data as needed, creating variables that
*   all our processes can access.
*   
*   NOTE: This SharedData struct lives in shared_data.h so that it can be included in other files. This means we only
*   have one version of the shared data struct to maintain, making things smoother.
*/

struct SharedData {
    int value1;
    int value2;
    // Other variables (can be different types!) added here as needed
};