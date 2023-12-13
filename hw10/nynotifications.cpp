#include "user.h"
#include "notification.h"

int main(int argc, char* argv[]) {
    try {
        // Check if the correct number of command-line arguments is provided
        if (argc != 6) {
            throw std::invalid_argument("Incorrect number of arguments provided. Needed 6.");
        }

        // Extract command-line arguments
        std::string posts_file = std::string(argv[1]);
        std::string users_file = std::string(argv[2]);
        std::string events_file = std::string(argv[3]);
        std::string profile = std::string(argv[5]);

        // Open the output file for writing
        std::ofstream outFile(argv[4]);
        if (!outFile.good()) {
            throw std::runtime_error("Unable to open the output file to write.");
        }

        // Create a user object
        User user = create_user(profile, users_file, posts_file);

        // Create queues and stack for notifications
        std::queue<Notification*> aggregates;
        std::queue<std::string> outputs;
        std::stack<std::string> ordered_outputs;

        // Create notifications and add them to the queue
        create_notifications(events_file, user, aggregates, outputs);

        // Transfer notifications from the queue to the stack
        while (!outputs.empty()) {
            ordered_outputs.push(outputs.front());
            outputs.pop();
        }

        // Write notifications from the stack to the output file
        while (!ordered_outputs.empty()) {
            outFile << ordered_outputs.top();
            ordered_outputs.pop();
        }

        // Close the output file
        outFile.close();

        // Cleanup: Delete dynamically allocated memory in the aggregates queue
        while (!aggregates.empty()) {
            delete aggregates.front();
            aggregates.pop();
        }

        return 0; // Successful execution

    } catch (const std::exception& e) {
        // Handle exceptions and print error messages
        std::cerr << "Error: " << e.what() << std::endl;
        return 1; // Return an error code
    }
}
