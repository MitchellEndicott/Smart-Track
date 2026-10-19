/////////////////////////////////////////////////////////
//
// CS1: Final Project: Smart Track
// Author: Mitchell Endicott
// Date: 11/24/25
//
/////////////////////////////////////////////////////////

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

    // Constants for number of days, events, and goals
    const int numberOfDays = 7;
    const int numberOfEvents = 17;
    const int numberOfGoals = 7;
    
    // Function declaration to get event index
    int getEventIndex(const string &event);

    // Names of the days of the week
    string days[numberOfDays] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
    };
    // List of track and field events
    string events[numberOfEvents] = {
        "60m", "100m", "200m", "400m", "800m", "1500m", "3000m", "60mh", "100/110mh", "400mh", "Long Jump", 
        "High Jump", "Triple Jump", "Pole Vault", "Shot Put", "Discus", "Javelin"
    };
    // List of training goals
    string goals[numberOfGoals] = {
        "Acceleration/Start", "Speed", "Speed Endurance", "Endurance", "Power", "Technique", "Strength"
    };
    // Boolean array indicating which goals apply to which events
    bool eventGoals[numberOfEvents][numberOfGoals] = {
        /*                     Acc  Spd  SpdEnd  Endu  Pow  Tech  Str   */
        /* 0: 60m          */ { 1 ,  1 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 1: 100m         */ { 1 ,  1 ,   1 ,    0 ,   1 ,  1 ,   1 },
        /* 2: 200m         */ { 1 ,  1 ,   1 ,    0 ,   1 ,  1 ,   1 },
        /* 3: 400m         */ { 1 ,  1 ,   1 ,    0 ,   1 ,  1 ,   1 },
        /* 4: 800m         */ { 0 ,  0 ,   1 ,    1 ,   0 ,  0 ,   1 },
        /* 5: 1500m        */ { 0 ,  0 ,   0 ,    1 ,   0 ,  0 ,   0 },
        /* 6: 3000m        */ { 0 ,  0 ,   0 ,    1 ,   0 ,  0 ,   0 },
        /* 7: 60mh         */ { 1 ,  1 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 8: 100/110mh    */ { 1 ,  1 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 9: 400mh        */ { 1 ,  0 ,   1 ,    0 ,   1 ,  1 ,   1 },
        /* 10: Long Jump   */ { 1 ,  1 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 11: High Jump   */ { 1 ,  1 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 12: Triple Jump */ { 1 ,  1 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 13: Pole Vault  */ { 1 ,  1 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 14: Shot Put    */ { 0 ,  0 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 15: Discus      */ { 0 ,  0 ,   0 ,    0 ,   1 ,  1 ,   1 },
        /* 16: Javelin     */ { 0 ,  0 ,   0 ,    0 ,   1 ,  1 ,   1 },
    };
    // Gym lifts
    string gym[4] {
        "Back Squat", "Bench Press", "Deadlift", "Clean"
    };    
    
    //Checks to see if the track pr's are in a valid format for both track and field events
    bool validPr(string s, string eventName) {
        int colonCount = 0;
        int dotCount = 0;
        bool isFieldEvent = (eventName == "Long Jump" || eventName == "High Jump" || eventName == "Triple Jump" || eventName == "Pole Vault" || eventName == "Shot Put" || 
                             eventName == "Discus" || eventName == "Javelin");
        if(s.length() == 0) {
            return false;
        }
        for(int i = 0; i < s.length(); i++) {
            char c = s[i];
            if(isdigit(c)) {
                continue;
            }
            else if(c == ':') {
                if(isFieldEvent) {
                    return false;
                }
                colonCount++;
                if (colonCount > 1) {
                    return false;
                }
            }
            else if(c == '.') {
                dotCount++;
                if(dotCount > 1) {
                    return false;
                }
            }
            else {
                return false;
            }
        }
    return true;
    }

    //Checks to see if the availability is formatted properly
    bool validTimeFormat(string time) {
        int colonPos = -1;
        for(int i = 0; i < time.length(); i++) {
            if(time[i] == ':') {
                colonPos = i;
                break;
            }
        }
        if(colonPos == -1) {
            return false;
        }
        string hhStr = "";
        string mmStr = "";

        for(int i = 0; i < colonPos; i++) {
            hhStr += time[i];
        }
        for(int i = colonPos + 1; i < time.length(); i++) {
            mmStr += time[i];
        }
        if(hhStr.length() < 1 || hhStr.length() > 2 || mmStr.length() != 2) {
            return false;
        }
        for(int i = 0; i < hhStr.length(); i++) {
            if(!isdigit(hhStr[i])) {
                return false;
            }
        }
        for(int i = 0; i < mmStr.length(); i++) {
            if(!isdigit(mmStr[i])) {
                return false;
            }
        }
        int hh = 0;
        
        for(int i = 0; i < hhStr.length(); i++) { //Converts the ASCII value of the input into an int
            hh = hh * 10 + (hhStr[i] - '0');
        }
        int mm = (mmStr[0] - '0') * 10 + (mmStr[1] - '0'); //Converts the ASCII value of the input into an int
        return hh >= 0 && hh <= 23 && mm >= 0 && mm <= 59;
    }

    // Checks if a new availability time window overlaps with existing windows
    bool overlaps(string startTimes[], string endTimes[], int count, string newStart, string newEnd) {
    for(int i = 0; i < count; i++) {
        if(!(newEnd <= startTimes[i] || newStart >= endTimes[i])) { //If the new window does not start before the existing window ends, 
            return true;                                            //or if the new window does not end before the existing window starts, this will be true
        }
    }
    return false;
    }
    
    //Formats the inputted time for easier comparison
    string formattedTime(string t) {
        int colonPos = -1;
        // Formats time string to ensure leading 0 for single-digit hours
        for(int i = 0; i < t.length(); i++) {
            if (t[i] == ':') {
                colonPos = i;
                break;
            }
        }
        if(colonPos == 1) {
            t = "0" + t; // turns a time like "8:30" into "08:30"
        }

        return t;
    }

    // Main lifts by goal type
    string mainLiftsStrength[] = {"Back Squat", "Bench Press", "Deadlift"};
    string mainLiftsPower[] = {"Power Clean","Back Squat", "Deadlift"};
    string mainLiftsSpeed[] = {"Power Clean", "Back Squat", "Deadlift"};
    // Accessory lifts for each main lift
    string accessoryBackSquat[] = {"Dumbbell Lunges", "RDL", "Hip Thrust", "Step-ups"};
    string accessoryBenchPress[] = {"Push Press", "Dips", "Pull-ups", "Tricep Extensions"};
    string accessoryDeadlift[] = {"RDL", "Pull-ups", "Glute Ham Raise", "Good Mornings"};
    string accessoryPowerClean[] = {"Med Ball Throws", "Box Jumps", "Plyometric Jumps", "Step-ups"};

    // Counters for main lifts selection
    int mainLiftCounterStrength = 0;
    int mainLiftCounterPower = 0;
    int mainLiftCounterSpeed = 0;
        
    // Selects a main lift based on goal and returns sets, reps, and load percentage
    string selectMainLift(const string &goal, int &outSets, int &outReps, float &outLoadPercent) {
        string chosenLift;
        if(goal == "Strength") {
            chosenLift = mainLiftsStrength[mainLiftCounterStrength % 3];
            mainLiftCounterStrength++;
            outSets = 4;
            outReps = 4;
            outLoadPercent = 0.80; // 80%
        }
        else if(goal == "Power") {
            chosenLift = mainLiftsPower[mainLiftCounterPower % 3];
            mainLiftCounterPower++;
            outSets = 5;
            outReps = 3;
            outLoadPercent = 0.60; // 60%
        }
        else if(goal == "Speed") {
            chosenLift = mainLiftsSpeed[mainLiftCounterSpeed % 2];
            mainLiftCounterSpeed++;
            outSets = 6;
            outReps = 2;
            outLoadPercent = 0.40; // 40%
        }
        else {  
            chosenLift = "Back Squat";
            outSets = 3;
            outReps = 5;
            outLoadPercent = 0.50; // 50%
        }
        return chosenLift;
    }

    // Select two accessory lifts avoiding repetition
    void selectAccessoryLifts(const string &mainLift, string &acc1, string &acc2) {
        string* pool;
        int count = 4; // All accessory arrays have 4 options

        if(mainLift == "Back Squat") {
            pool = accessoryBackSquat;
        }
        else if(mainLift == "Bench Press") {
            pool = accessoryBenchPress;
        }
        else if(mainLift == "Deadlift") {
            pool = accessoryDeadlift;
        }
        else {
            pool = accessoryPowerClean;
        }
        // Keep track of last selected accessories to avoid repeats
        static string lastAcc1 = "", lastAcc2 = "";
        int idx1, idx2;
        // Pick first accessory
        do {
            idx1 = rand() % count;
        } 
        while(pool[idx1] == lastAcc1 || pool[idx1] == lastAcc2);
        // Pick second accessory
        do {
            idx2 = rand() % count;
        } 
        while(idx2 == idx1 || pool[idx2] == lastAcc1 || pool[idx2] == lastAcc2);
        acc1 = pool[idx1];
        acc2 = pool[idx2];
        // Update last selections
        lastAcc1 = acc1;
        lastAcc2 = acc2;
    }

    // Generate track workout drills for a given event and goals
    string generateTrackWorkout(string event, string ChosenGoals[], int numberGoalsChosen, int counter) {
        string goal;
        if(numberGoalsChosen == 1) {
            goal = ChosenGoals[0];
        } 
        else if(numberGoalsChosen == 2) {
            bool bothGym = ((ChosenGoals[0] == "Power" || ChosenGoals[0] == "Strength") && (ChosenGoals[1] == "Power" || ChosenGoals[1] == "Strength"));
            if(bothGym) {
                if(event == "60m" || event == "100m" || event == "200m" || event == "400m") {
                    goal = "Speed";
                } 
                else {
                    goal = "Technique";
                }
            }
            else {
                if(ChosenGoals[0] == "Speed" || ChosenGoals[0] == "Acceleration/Start" || ChosenGoals[0] == "Speed Endurance" || ChosenGoals[0] == "Endurance" || ChosenGoals[0] == "Technique") {
                    goal = ChosenGoals[0];
                } 
                else {
                    goal = ChosenGoals[1];
                }
            }
        }
        if(goal == "Power" || goal == "Strength") {
            if(event == "60m" || event == "100m" || event == "200m" || event == "400m") {
                goal = "Speed";
            } 
            else {
                goal = "Technique";
            }
        }
        // Track last workout per event to avoid repeats
        static string lastWorkout[numberOfEvents];
        int idx = getEventIndex(event);  // same index used for counter arrays
        string options[5];
        // ---------- Sprints ----------
        if(event == "60m" || event == "100m" || event == "200m" || event == "400m") {
            if(goal == "Technique") {
                if(event == "60m" || event == "100m") {
                    options[0] = "A-skips 2x20m, B-skips 2x20m, Wall Drive 2x10m,";
                    options[1] = "Form strides 4x40m, focus on arm-leg coordination";
                    options[2] = "High knees 3x20m, Butt kicks 3x20m";
                    options[3] = "Stride drills 4x30m, posture focus";
                    options[4] = "Arm swing mechanics 3x20m";
                } else if(event == "200m") {
                    options[0] = "Form strides 3x50m, arm-leg coordination";
                    options[1] = "High knee runs 3x30m, focus on sprint posture";
                    options[2] = "Stride mechanics 4x20m";
                    options[3] = "Posture and drive drills 3x30m";
                    options[4] = "Arm-leg coordination 4x25m";
                } else { // 400m
                    options[0] = "Curve running drills 3x50m";
                    options[1] = "Form strides 3x60m, focus on posture";
                    options[2] = "Posture drills 4x40m";
                    options[3] = "Arm-leg coordination 3x50m";
                    options[4] = "Stride mechanics 3x60m";
                }
            }
            if(goal == "Speed") {
                if(event == "60m" || event == "100m") {
                    options[0] = "6x80m walk in sprints @ 85%";
                    options[1] = "80m, 4x60m, 80m, x4, all out";
                    options[2] = "4x80 sprints, build up the first 25m @ 90%";
                    options[3] = "6x60m sprints @ 85%";
                    options[4] = "5x70m sprints @ 90% effort";
                } else if(event == "200m") {
                    options[0] = "5x150m @ 90%";
                    options[1] = "6x120m walk in sprints, focus on rhythm @ 80% ";
                    options[2] = "5x80m all out";
                    options[3] = "3x150m sprints @ 85%";
                    options[4] = "4x120m progressive sprints";
                } else { // 400m
                    options[0] = "4x200m @ 85%";
                    options[1] = "3x300m @ 80%";
                    options[2] = "5x150m @ 90%";
                    options[3] = "4x250m @ 80%";
                    options[4] = "3x200m walk-in sprints @85%";
                }
            }
            if(goal == "Acceleration/Start") {
                options[0] = "6x20m walk in accels";
                options[1] = "4x15m kneeling starts";
                options[2] = "5x10m sled starts, acceleration emphasis";
                options[3] = "5x20m push sled starts";
                options[4] = "4x20m from blocks, focus on drive";
            }
            if(goal == "Speed Endurance") {
                options[0] = "4x120m @ 90% ";
                options[1] = "3x150m walk in sprints @90%";
                options[2] = "5x120m, start on the curve @ 90%";
                options[3] = "4x120m @90%";
                options[4] = "5x250m @ 80%";
            }
            if(goal == "Endurance") {
                options[0] = "Tempo runs 4x150m @ moderate pace";
                options[1] = "3x200m";
                options[2] = "3x250m @ easy pace";
                options[3] = "5x120m @ aerobic pace";
                options[4] = "4x200m @ moderate pace";
            }
        }
        // ---------- Jumps ----------
        if(event == "Long Jump" || event == "Triple Jump" || event == "High Jump" || event == "Pole Vault") {
            if(goal == "Speed" || goal == "Acceleration/Start" || goal == "Speed Endurance" || goal == "Endurance") {
                string sprintOptions[5] = {
                    "6x80m walk in sprints @ 85%",
                    "80m, 4x60m, 80m, x4, all out",
                    "4x80 sprints, build up the first 25m @ 90%",
                    "6x60m sprints @ 85%",
                    "5x70m sprints @ 90% effort",
                };
                for(int k = 0; k < 5; k++) {
                    options[k] = sprintOptions[k];
                }
            } 
            else {
                if(event == "Long Jump") {
                    options[0] = "Alternating bounds 3x20m, Penultimate step 3x10, Landing drills 3x10";
                    options[1] = "Approaches x5-8, Takeoff drills 3x10, Short approach jumps";
                    options[2] = "Single leg bounds 3x20m, Approaches x 5-8, Chair landing drills x15";
                    options[3] = "Penultimate step 3x10, Full jumps";
                    options[4] = "Skips for height 3x20m, Approach rhythm drills 3x5, Landing drills x15";
                } else if(event == "Triple Jump") {
                    options[0] = "First phase x5, Penultimate step x10, Landing drills x10, all x3";
                    options[1] = "Single leg bounds 3x20m each leg, Approaches x6,";
                    options[2] = "Alternating bounds 3x20m, First two phases x4-6, Landing drills x15";
                    options[3] = "Full approach 4x, Penultimate drills 3x10, Landing drills 3x5";
                    options[4] = "Single Leg bounds 3x20m, Full jumps x6-8";
                } else if(event == "High Jump") {
                    options[0] = "Approach x5, Penultimate step 3x10";
                    options[1] = "Full approach x4, Takeoff drills 3x5";
                    options[2] = "Three step approach jumps x5, Penultimate step 3x5, Full approach over a bar";
                    options[3] = "Plyometric jumps 3x5, Approach rhythm 3x5, Technique focus 3x5";
                    options[4] = "Bar work 3x5, Takeoff drills 3x5, Landing drills 3x5";
                } else { // Pole Vault
                    options[0] = "Pole Roll Overs x5, Swings x5, Short approach vaults";
                    options[1] = "Pole Sprints x5, Sliding box Plants x15, Full vaults over a bar";
                    options[2] = "Swing drills 3x10, Short approach vaults";
                    options[3] = "Swing-ups 3x10, Short approach vaults";
                    options[4] = "Alternating bounds, Pole carries x5, Full vaults";
                }
            }
        }
        //Throws
        if(event == "Shot Put") {
            options[0] = "Standing throws x3-6, Glide/Rotational drills 3x5, emphasis on footwork";
            options[1] = "Kneeling throws x10, Standing Throws x3-6, Full throws";
            options[2] = "Standing throws x3-6, Glide/Rotational drills 3x5, emphasis on footwork";
            options[3] = "Kneeling throws x10, Standing Throws x3-6, Full throws";
            options[4] = "Full throws, get after it";
        }
        if(event == "Discus") {
            options[0] = "Standing throws x3-6, Rotational drills 3x5, emphasis on footwork";
            options[1] = "Release drills 3x5, Rotational drills x7";
            options[2] = "Easy throws 5x5, Balance and posture drills 3x5";
            options[3] = "Power throws 4x5, Turns 3x5";
            options[4] = "Full throw sequence 4x5";
        }
        if(event == "Javelin") {
            options[0] = "Run-up throws 5x5, Release drills 3x5";
            options[1] = "Easy throws 5x5, Arm mechanics focus 3x5";
            options[2] = "Power throws 4x5, Technical drills 3x5";
            options[3] = "Short approach throws 4x5, Footwork drills 3x5";
            options[4] = "Full approach throws 5x5, Release and follow-through drills";
        }
        //Random pick to avoid repeating workouts
        int pick;
        do {
            pick = rand() % 5;
        } while(options[pick] == lastWorkout[idx]);
        lastWorkout[idx] = options[pick];
        return options[pick];
    }

    string eventsList[numberOfEvents];
    int eventCounters[numberOfEvents];
    int numEvents = 0;

    int getEventIndex(const string &event) {
        for(int i = 0; i < numberOfEvents; i++) {
            if(events[i] == event) {
                return i;
            }
        }
        return -1;
    }

    //if the user missed a workout
    void handleMissedWorkout(string scheduledTrack[][3], string scheduledTrackFocus[][3], string scheduledGym[][3], 
                             string scheduledGymAcc1[][3],  string scheduledGymAcc2[][3], float scheduledGymLoad[][3], int scheduledGymSets[][3], 
                             string scheduledGymReps[][3], int windowsPerDay[], bool available[], string days[], int numberOfDays) {

        cout << "=== Weekly Workout Check-In ===" << endl;
        cout << "Did you complete all your workouts this week? (Y/N): ";
        char completed;
        cin >> completed;

        if(completed == 'N' || completed == 'n') {
            int dayMissed = -1, windowMissed = -1;

            // Ask which workout was missed
            cout << "Enter the day number of the missed workout:" << endl;
            for(int i = 0; i < numberOfDays; i++) {
                if(available[i])
                    cout << "  " << (i+1) << ". " << days[i] << endl;
            }
            cin >> dayMissed;
            dayMissed--; // convert to 0-indexed

            cout << "Enter the window number of the missed workout on " << days[dayMissed] << ": ";
            cin >> windowMissed;
            windowMissed--;

            // Store the missed workout
            string missedTrack = scheduledTrack[dayMissed][windowMissed];
            string missedTrackFocus = scheduledTrackFocus[dayMissed][windowMissed];
            string missedGym = scheduledGym[dayMissed][windowMissed];
            string missedAcc1 = scheduledGymAcc1[dayMissed][windowMissed];
            string missedAcc2 = scheduledGymAcc2[dayMissed][windowMissed];
            float missedLoad = scheduledGymLoad[dayMissed][windowMissed];
            int missedSets = scheduledGymSets[dayMissed][windowMissed];
            string missedReps = scheduledGymReps[dayMissed][windowMissed];

            // Find the last available window in the week
            bool placed = false;
            for(int i = numberOfDays - 1; i >= 0 && !placed; i--) {
                if(!available[i]) continue;
                for(int j = windowsPerDay[i] - 1; j >= 0; j--) {
                    if(scheduledTrack[i][j] == "Rest" && scheduledGym[i][j] == "Rest") {
                        // Place the missed workout here
                        scheduledTrack[i][j] = missedTrack;
                        scheduledTrackFocus[i][j] = missedTrackFocus;
                        scheduledGym[i][j] = missedGym;
                        scheduledGymAcc1[i][j] = missedAcc1;
                        scheduledGymAcc2[i][j] = missedAcc2;
                        scheduledGymLoad[i][j] = missedLoad;
                        scheduledGymSets[i][j] = missedSets;
                        scheduledGymReps[i][j] = missedReps;
                        placed = true;
                        cout << "Missed workout moved to " << days[i] << ", window " << (j+1) << "." << endl;
                        break;
                    }
                }
            }

            if(!placed) {
                cout << "No available slots to reschedule missed workout this week." << endl;
            }
        }
    }


int main() {
    srand(time(0));

    //User inputs the events they would like to work on
    cout << "What events would you like to work on? (Select up to 4)" << endl;
    cout << "Enter the number of an event to select it." << endl;
    cout << "Enter 0 when done." << endl;
    string chosenEvents[4];
    int numberEventsChosen = 0;

    //Output the list of events the user can choose from
    for(int i = 0; i < numberOfEvents; i++) {
        cout << "  " << (i+1) << ". " << events[i] << endl;
    }
    int eventChoice;
    
    while(numberEventsChosen < 4) {
        cout << "Choose event #" << (numberEventsChosen + 1) << " (0 to finish): ";
        cin >> eventChoice;
        
        //If the user inputs something other than an integer, it will prompt them to try again
        if(cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Try again" << endl;
                continue;
        }
        if(eventChoice == 0) {
            break;
        }
        if(eventChoice < 1 || eventChoice > 17) {
            cout << "Invalid input. Try again." << endl;
            continue;
        }
        //If the user inputs an event they have already chosen, it will prompt them to try again
        bool alreadyChosenEvent = false;
        for(int i = 0; i < numberEventsChosen; i++) {
            if(chosenEvents[i] == events[eventChoice - 1]) {
                alreadyChosenEvent = true;
                break;
            }
        } 
        if(alreadyChosenEvent) {
            cout << "You already selected " << events[eventChoice - 1] << ". Choose a different event." << endl;
            continue;
        }
        chosenEvents[numberEventsChosen] = events[eventChoice - 1];
        numberEventsChosen++;
        cout << "  Added: " << events[eventChoice - 1] << endl;
    }
    //User inputs their training goals
    cout << "What are your training goals? (Select up to 2)" << endl;
    cout << "Enter the number of a goal to select it." << endl;
    cout << "Enter 0 when done." << endl;
    string ChosenGoals[2];
    int numberGoalsChosen = 0;
    //Output the list of goals the user can choose from
    bool goalShown[numberOfGoals] = {false};
    
    for(int i = 0; i < numberEventsChosen; i++) {
        int eventIndex = -1;
        for(int j = 0; j < numberOfEvents; j++) {
            if(chosenEvents[i] == events[j]) {
                eventIndex = j;
                break;
            }
        }
        if(eventIndex == -1) {
            continue;
        }
        for(int g = 0; g < numberOfGoals; g++) {
            if(eventGoals[eventIndex][g]) {
                goalShown[g] = true;
            }
        }
    }
    //The list will not skip a number, even if a goal is skipped
    int displayNumber = 1;
    int goalMapping[numberOfGoals]; 
    
    for(int i = 0; i < numberOfGoals; i++) {
        if(goalShown[i]) {
            cout << "  " << displayNumber << ". " << goals[i] << endl;
            goalMapping[displayNumber-1] = i; 
            displayNumber++;
        }
    }
    int goalChoice;

    while(numberGoalsChosen < 2) {
        cout << "Choose goal #" << (numberGoalsChosen + 1) << " (0 to finish): ";
        cin >> goalChoice;
        //If the user inputs something other than an integer, it will prompt them to try again
        if(cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Try again" << endl;
                continue;
        }
        if(goalChoice == 0) {
            break;
        }
        if(goalChoice < 1 || goalChoice >= displayNumber) {
            cout << "Invalid choice. Try again." << endl;
            continue;
        }
        int originalIndex = goalMapping[goalChoice-1];
        //If the user inputs an event they have already chosen, it will prompt them to try again
        bool alreadyChosenGoal = false;
        for(int i = 0; i < numberGoalsChosen; i++) {
            if(ChosenGoals[i] == goals[originalIndex]) {
                alreadyChosenGoal = true;
                break;
            }
        }  
        if(alreadyChosenGoal) {
            cout << "You already selected " << goals[originalIndex] << ". Choose a different goal." << endl;
            continue;
        }
        ChosenGoals[numberGoalsChosen] = goals[originalIndex];
        numberGoalsChosen++;
        cout << "  Added: " << goals[originalIndex] << endl;
    }
    //User inputs their pr's in their track events
    string trackPrs[4];
    cout << "What are your pr's in your events? (In MM:SS.SS or meters)" << endl;
    
    for(int i = 0; i < numberEventsChosen; i++) {
        string temp = "";
        cout << "  " << (i+1) << ". " << chosenEvents[i] << ": "; //Displays only the events they chose
        cin >> temp;
        
        //If the user inputs something in the wrong format, it will prompt them to try again
        while(!validPr(temp, chosenEvents[i])) {
            cout << "Invalid format." << endl;
            cout << "  " << (i+1) << ". " << chosenEvents[i] << ": ";
            cin >> temp;
        }
        trackPrs[i] = temp;
    }
    //User inputs their pr's in the gym
    float gymPrs[4];
    cout << "What are your pr's in the gym? (In pounds)" << endl;
    
    //Displays the different lifts
    for(int i = 0; i < 4; i++) {
        while(true) {
            cout << "  " << gym[i] << ": ";
            cin >> gymPrs[i];
            //If the user inputs something other than a float, it will prompt them to try again
            if(cin.fail()) {
                cin.clear();
                cin.ignore(1000, '\n');
                cout << "Invalid input. Try again." << endl;
                continue;
            }
            else {
                break;
            }
        }
    }
   
    // Maximum number of availability windows per day
    const int maxWindows = 3;
    // Arrays storing number of windows per day and whether user is available that day
    int windowsPerDay[numberOfDays];
    bool available[numberOfDays];
    // Arrays for storing start and end times for each availability window
    string startTime[numberOfDays][maxWindows];
    string endTime[numberOfDays][maxWindows];
    
    //Availability section
    cout << "Enter your availability for each day." << endl;
    for(int i = 0; i < numberOfDays; i++) {
        // Reset window count for the current day
        windowsPerDay[i] = 0;
        char ans;
        cout << "  " << days[i] << " available (Y/N)? ";
        cin >> ans;
        
        if(ans == 'Y' || ans == 'y') {
            available[i] = true;
            //Allow user to enter up to maxWindows availability windows
            while(windowsPerDay[i] < maxWindows) {
                string start, end;
                bool validWindow = false;
                //Loop until user enters a valid non-overlapping time window
                while(!validWindow) {
                    cout << "Start time (e.g. 14:00): ";
                    cin >> start;
                    start = formattedTime(start);
                    cout << "End time (e.g. 15:30): ";
                    cin >> end;
                    end = formattedTime(end);
                    
                    if(!validTimeFormat(start) || !validTimeFormat(end)) {
                        cout << "Invalid Format. Try Again" << endl;
                        continue;
                    }
                    //Ensure end time is after start time
                    if(end <= start) {
                        cout << "End time must be after start time. Try again." << endl;
                        continue;
                    }
                    //Prevent overlapping windows for the same day
                    if(overlaps(startTime[i], endTime[i], windowsPerDay[i], start, end)) {
                        cout << "This time window overlaps with an existing one. Try again." << endl;
                        continue;
                    }
                    validWindow = true;
                }         
                //Store the valid window times
                startTime[i][windowsPerDay[i]] = start;
                endTime[i][windowsPerDay[i]] = end;
                windowsPerDay[i]++;
                //Stop if the max number of windows for this day is reached
                if(windowsPerDay[i] == maxWindows) {
                    cout << "Max windows reached for " << days[i] << endl;
                    break;
                }
                //Ask if the user wants to add another window
                char again;
                cout << "  Add another availability window for " << days[i] << "? (Y/N): ";
                cin >> again;
                
                if(!(again == 'Y' || again == 'y')) {
                    break;
                }
            }
        }
        else {
            available[i] = false;
            windowsPerDay[i] = 0;
        }
    }
    // Scheduling arrays initialized after availability collection
    string scheduledTrack[numberOfDays][3], scheduledTrackFocus[numberOfDays][3];
    string scheduledGym[numberOfDays][3];
    string scheduledGymAcc1[numberOfDays][3], scheduledGymAcc2[numberOfDays][3];
    float scheduledGymLoad[numberOfDays][3];
    int scheduledGymSets[numberOfDays][3];
    string scheduledGymReps[numberOfDays][3];
    //Counters and constants for scheduling
    int trackIndex = 0;
    int windowCounter = 0;
    int  setsAccessory = 3;
    string repsAccessory = "10-15";
    const int maxWorkouts = 10;
    bool sprintStartScheduledToday[numberOfDays] = {false};
    int globalWindowCounter = 0;

    //Makes the workouts be distributed somewhat evewnly
    int totalWindows = 0;
    for(int i = 0; i < numberOfDays; i++)
        totalWindows += windowsPerDay[i];

    // Reserve 1 slot for overflow
    int availableWindowsForWorkouts = totalWindows - 1;
    float interval = (float)availableWindowsForWorkouts / maxWorkouts;
    float nextWorkoutWindow = 0.0;

    globalWindowCounter = 0;
    trackIndex = 0;

    for(int i = 0; i < numberOfDays; i++) {
        if(!available[i]) continue;

        for(int j = 0; j < windowsPerDay[i]; j++) {
            //Overflow window
            bool isOverflowWindow = (globalWindowCounter == totalWindows - 1);

            if(isOverflowWindow) {
                scheduledTrack[i][j] = "Rest";
                scheduledTrackFocus[i][j] = "";
                scheduledGym[i][j] = "Rest";
                scheduledGymAcc1[i][j] = "";
                scheduledGymAcc2[i][j] = "";
                scheduledGymLoad[i][j] = 0;
                scheduledGymSets[i][j] = 0;
                scheduledGymReps[i][j] = "";
            } 
            else if(globalWindowCounter < maxWorkouts && globalWindowCounter >= nextWorkoutWindow) {
                bool isTrack = (windowCounter % 3 != 2); 
                int dayIntensity = j % 3;
                string currentGoal = ChosenGoals[windowCounter % numberGoalsChosen];

                if(isTrack) {
                    string currentEvent = chosenEvents[trackIndex % numberEventsChosen];
                    if(currentGoal == "Acceleration/Start" && (currentEvent == "60m" || currentEvent == "100m" || currentEvent == "200m" || currentEvent == "400m")) {
                        if(sprintStartScheduledToday[i]) {
                            currentGoal = "Speed";
                        }
                        else {
                            sprintStartScheduledToday[i] = true;
                        }
                    }
                    scheduledTrack[i][j] = currentEvent;
                    int idx = getEventIndex(currentEvent);
                    scheduledTrackFocus[i][j] = generateTrackWorkout(currentEvent, ChosenGoals, numberGoalsChosen, eventCounters[idx]);
                    eventCounters[idx]++;
                    
                    //Gym rest
                    scheduledGym[i][j] = "Rest";
                    scheduledGymAcc1[i][j] = "";
                    scheduledGymAcc2[i][j] = "";
                    scheduledGymLoad[i][j] = 0;

                    trackIndex++;
                } else {
                    //Gym day
                    int sets, reps;
                    float loadPercent;
                    string mainLift = selectMainLift(currentGoal, sets, reps, loadPercent);

                    int prIndex = (mainLift == "Back Squat") ? 0 :
                                (mainLift == "Bench Press") ? 1 :
                                (mainLift == "Deadlift") ? 2 : 3;

                    float loadFactor = loadPercent * (dayIntensity == 0 ? 0.6 : dayIntensity == 1 ? 0.85 : 1.0);
                    float load = gymPrs[prIndex] * loadFactor;

                    string acc1, acc2;
                    selectAccessoryLifts(mainLift, acc1, acc2);

                    scheduledGym[i][j] = mainLift;
                    scheduledGymAcc1[i][j] = acc1;
                    scheduledGymAcc2[i][j] = acc2;
                    scheduledGymLoad[i][j] = load;
                    scheduledGymSets[i][j] = sets;
                    scheduledGymReps[i][j] = to_string(reps);

                    scheduledTrack[i][j] = "Rest";
                    scheduledTrackFocus[i][j] = "";
                }
                nextWorkoutWindow += interval; // move to next evenly spaced window
            } 
            else {
                scheduledTrack[i][j] = "Rest";
                scheduledTrackFocus[i][j] = "";
                scheduledGym[i][j] = "Rest";
                scheduledGymAcc1[i][j] = "";
                scheduledGymAcc2[i][j] = "";
                scheduledGymLoad[i][j] = 0;
                scheduledGymSets[i][j] = 0;
                scheduledGymReps[i][j] = "";
            }

            globalWindowCounter++;
            windowCounter++;
        }

    }

    // Workout plan
    cout << endl;
    cout << "=== Weekly Workout Plan ===" << endl;
    for(int i = 0; i < numberOfDays; i++) {
        if(!available[i]) {
            continue;
        }
        cout << "Day: " << days[i] << endl;

        for(int j = 0; j < windowsPerDay[i]; j++) {
            cout << "  Window " << (j+1) << " (" << startTime[i][j] << " - " << endTime[i][j] << "):" << endl;
            if(scheduledTrack[i][j] != "Rest") {
                cout << "    Track: " << scheduledTrack[i][j] << " (" << scheduledTrackFocus[i][j] << ")" << endl;
            } 
            else if(scheduledGym[i][j] != "Rest") {
                cout << "    Gym: " << scheduledGym[i][j] << " @ " << scheduledGymLoad[i][j] << " lbs, " << scheduledGymSets[i][j] << " sets x " << scheduledGymReps[i][j] << " reps" << endl;
                cout << "      Accessory 1: " << scheduledGymAcc1[i][j] << " - " << setsAccessory << " sets x " << repsAccessory << " reps" << endl;
                cout << "      Accessory 2: " << scheduledGymAcc2[i][j] << " - " << setsAccessory << " sets x " << repsAccessory << " reps" << endl;
            } 
            else {
                cout << "    Rest day" << endl;
            }
        }
        cout << endl;
    }

    // After the schedule is filled with workouts, sets the last available window as rest
    for (int i = numberOfDays - 1; i >= 0; i--) {
        if(!available[i]) {
            continue;
        }
        int lastWindow = windowsPerDay[i] - 1;
        
        // Set it as rest if it currently has a workout
        if (scheduledTrack[i][lastWindow] != "Rest" || scheduledGym[i][lastWindow] != "Rest") {
            scheduledTrack[i][lastWindow] = "Rest";
            scheduledTrackFocus[i][lastWindow] = "";
            scheduledGym[i][lastWindow] = "Rest";
            scheduledGymAcc1[i][lastWindow] = "";
            scheduledGymAcc2[i][lastWindow] = "";
            scheduledGymLoad[i][lastWindow] = 0;
            scheduledGymSets[i][lastWindow] = 0;
            scheduledGymReps[i][lastWindow] = "";
        }
        break;
    }

    handleMissedWorkout(scheduledTrack, scheduledTrackFocus, scheduledGym, scheduledGymAcc1, scheduledGymAcc2, scheduledGymLoad, 
                        scheduledGymSets, scheduledGymReps, windowsPerDay, available, days, numberOfDays);

    // New workout plan
    cout << endl;
    cout << "=== Weekly Workout Plan ===" << endl;
    for(int i = 0; i < numberOfDays; i++) {
        if(!available[i]) {
            continue;
        }
        cout << "Day: " << days[i] << endl;

        for(int j = 0; j < windowsPerDay[i]; j++) {
            cout << "  Window " << (j+1) << " (" << startTime[i][j] << " - " << endTime[i][j] << "):" << endl;
            if(scheduledTrack[i][j] != "Rest") {
                cout << "    Track: " << scheduledTrack[i][j] << " (" << scheduledTrackFocus[i][j] << ")" << endl;
            } 
            else if(scheduledGym[i][j] != "Rest") {
                cout << "    Gym: " << scheduledGym[i][j] << " @ " << scheduledGymLoad[i][j] << " lbs, " << scheduledGymSets[i][j] << " sets x " << scheduledGymReps[i][j] << " reps" << endl;
                cout << "      Accessory 1: " << scheduledGymAcc1[i][j] << " - " << setsAccessory << " sets x " << repsAccessory << " reps" << endl;
                cout << "      Accessory 2: " << scheduledGymAcc2[i][j] << " - " << setsAccessory << " sets x " << repsAccessory << " reps" << endl;
            } 
            else {
                cout << "    Rest day" << endl;
            }
        }
        cout << endl;
    }

    return 0;
}