#include <stdio.h>
#include <string.h>

#define TOTAL_CANDIDATES 3
#define MAX_VOTERS 100
#define PASSWORD "nikit123"

// Structure for candidates
typedef struct {
    char candidateName[100];
    int totalVotes;
} Candidate;

// Structure for voters
typedef struct {
    char voterID[50]; // VOter ID is unique
} Voter;

// Candidate
Candidate candidateList[TOTAL_CANDIDATES] = {
    {"Nikit", 0},
    {"Bishal", 0},
    {"Malla", 0}
};

// Voter tracking
Voter recordedVoters[MAX_VOTERS];
int voterCount = 0;

// Check if already voted
int hasAlreadyVoted(const char id[]) {
    for (int i = 0; i < voterCount; i++) {
        if (strcmp(recordedVoters[i].voterID, id) == 0) {
            return 1;
        }
    }
    return 0;
}

// Store new voter
void registerVoter(const char id[]) {
    strcpy(recordedVoters[voterCount].voterID, id);
    voterCount++;
}

// Verify admin]
int authenticateAdmin() {
    char enteredPassword[50];
    printf("Enter admin password: ");
    scanf("%s", enteredPassword);
    if (strcmp(enteredPassword, PASSWORD) == 0) {
        return 1;
    } else {
        printf("Incorrect password! Access denied.\n");
        return 0;
    }
}

// Clear the input buffer
void clearInputBuffer() {
    while (getchar() != '\n');  // Clear the newline character from buffer
}

// Allow a user to vote
void voteNow() {
    char id[50];
    int voteOption;

    printf("\nEnter your Voter ID: ");
    scanf("%s", id);

    if (hasAlreadyVoted(id)) {
        printf("This ID has already been used. Voting denied.\n");
        clearInputBuffer();  // Clear buffer after input
        return;
    }

    printf("\n--- Vote for your preferred candidate ---\n");
    for (int i = 0; i < TOTAL_CANDIDATES; i++) {
        printf("%d. %s\n", i + 1, candidateList[i].candidateName);
    }

    printf("Your choice (1-%d): ", TOTAL_CANDIDATES);
    scanf("%d", &voteOption);
    clearInputBuffer(); 

    if (voteOption >= 1 && voteOption <= TOTAL_CANDIDATES) {
        candidateList[voteOption - 1].totalVotes++;
        registerVoter(id);
        printf("Voted successfully. Thank you!\n");
    } else {
        printf("Invalid!. Vote not counted.\n");
    }
    printf("-------------------------------------------------\n");
}

// Display results (Only admin)
void displayVoteCount() {
    if (!authenticateAdmin()) return;

    printf("\n--- Current Vote Count ---\n");
    for (int i = 0; i < TOTAL_CANDIDATES; i++) {
        printf("%s: %d votes\n", candidateList[i].candidateName, candidateList[i].totalVotes);
    }
    printf("-------------------------------------------------\n");
}

// Announce winner (Only admin)
void announceWinner() {
    if (!authenticateAdmin()) return;

    int highest = 0, winner = -1, tie = 0;

    for (int i = 0; i < TOTAL_CANDIDATES; i++) {
        if (candidateList[i].totalVotes > highest) {
            highest = candidateList[i].totalVotes;
            winner = i;
            tie = 0;
        } else if (candidateList[i].totalVotes == highest && highest != 0) {
            tie = 1;
        }
    }

    if (highest == 0) {
        printf("No votes have been cast yet.\n");
    } else if (tie) {
        printf("There is a tie between candidates.\n");
    } else {
        printf("Winner: %s with %d votes!\n", candidateList[winner].candidateName, highest);
    }
    printf("-------------------------------------------------\n");
}

// Main
int main() {
    int userChoice;

    while (1) {
        printf("\n=== Simple Voting Program ===\n");
        printf("1. Vote\n");
        printf("2. View Vote Count (Admin)\n");
        printf("3. View Winner (Admin)\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &userChoice);

        // Clear the input buffer
        clearInputBuffer();

        switch (userChoice) {
            case 1:
                voteNow();
                break;
            case 2:
                displayVoteCount();
                break;
            case 3:
                announceWinner();
                break;
            case 4:
                printf("Exiting the system. Goodbye!\n");
                return 0;  
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}
