# Smart Track

A C++ command-line program that builds a weekly track and gym training plan for an athlete. It was my individual final project for CS1.

## What it does

The program asks for:

- Up to 4 events from a list of 17 track and field events (sprints, distance, hurdles, jumps, throws)
- Up to 2 training goals, limited to the goals that make sense for the chosen events (for example Speed, Power, Endurance)
- Personal records for each event, and gym PRs for the back squat, bench press, deadlift and clean
- Availability for each day of the week, with up to 3 time windows per day

It then prints a weekly plan that spreads the workouts across the available windows and keeps the last window as a rest slot.

## Features

- Track workouts matched to the event and goal, with a random pick from several options that avoids repeating the same workout back to back
- Gym sessions with a main lift, two accessory lifts, sets, reps, and a load calculated as a percentage of the athlete's PR
- Validation of event choices, PR formats and availability times, including overlap checks between windows
- A weekly check-in that moves a missed workout to a free window

## Build and run

```
g++ -std=c++17 main.cpp -o smarttrack
./smarttrack
```

## Sample output

The following is an actual run of the program, using four selected events, two training goals, example PRs, and a weekly availability schedule. The transcript shows both the command-line prompts and the generated plan.

```text
What events would you like to work on? (Select up to 4)
Enter the number of an event to select it.
Enter 0 when done.
  1. 60m
  2. 100m
  3. 200m
  4. 400m
  5. 800m
  6. 1500m
  7. 3000m
  8. 60mh
  9. 100/110mh
 10. 400mh
 11. Long Jump
 12. High Jump
 13. Triple Jump
 14. Pole Vault
 15. Shot Put
 16. Discus
 17. Javelin
Choose event #1 (0 to finish): 2
Added: 100m
Choose event #2 (0 to finish): 15
Added: Shot Put
Choose event #3 (0 to finish): 16
Added: Discus
Choose event #4 (0 to finish): 14
Added: Pole Vault
What are your training goals? (Select up to 2)
Enter the number of a goal to select it.
Enter 0 when done.
  1. Acceleration/Start
  2. Speed
  3. Speed Endurance
  4. Power
  5. Technique
  6. Strength
Choose goal #1 (0 to finish): 1
Added: Acceleration/Start
Choose goal #2 (0 to finish): 2
Added: Speed
What are your PR's in your events? (In MM:SS.SS or meters)
  1. 100m: 11.51
  2. Shot Put: 15.80
  3. Discus: 48.00
  4. Pole Vault: 4.10
What are your PR's in the gym? (In pounds)
  Back Squat: 405
  Bench Press: 275
  Deadlift: 435
  Clean: 295
Enter your availability for each day.
Monday available (Y/N)? y
Start time (e.g. 14:00): 10:10
End time (e.g. 15:30): 12:00
Add another availability window for Monday? (Y/N): y
Start time (e.g. 14:00): 15:00
End time (e.g. 15:30): 17:00
Add another availability window for Monday? (Y/N): n
Tuesday available (Y/N)? y
Start time (e.g. 14:00): 9:30
End time (e.g. 15:30): 12:00
Add another availability window for Tuesday? (Y/N): n
Wednesday available (Y/N)? y
Start time (e.g. 14:00): 10:10
End time (e.g. 15:30): 12:00
Add another availability window for Wednesday? (Y/N): y
Start time (e.g. 14:00): 15:00
End time (e.g. 15:30): 17:00
Add another availability window for Wednesday? (Y/N): n
Thursday available (Y/N)? y
Start time (e.g. 14:00): 9:30
End time (e.g. 15:30): 12:00
Add another availability window for Thursday? (Y/N): n
Friday available (Y/N)? n
Saturday available (Y/N)? n
Sunday available (Y/N)? n

=== Weekly Workout Plan ===
Day: Monday
  Window 1 (10:10 - 12:00):
    Track: 100m (4x15m kneeling starts)
  Window 2 (15:00 - 17:00):
    Track: Shot Put (Standing throws x3-6, Glide/Rotational drills 3x5, emphasis on footwork)

Day: Tuesday
  Window 1 (09:30 - 12:00):
    Gym: Back Squat @ 121.5 lbs, 3 sets x 5 reps
      Accessory 1: Hip Thrust - 3 sets x 10-15 reps
      Accessory 2: Step-ups - 3 sets x 10-15 reps

Day: Wednesday
  Window 1 (10:10 - 12:00):
    Track: Discus (Standing throws x3-6, Rotational drills 3x5, emphasis on footwork)
  Window 2 (15:00 - 17:00):
    Track: Pole Vault (4x80 sprints, build up the first 25m @ 90%)

Day: Thursday
  Window 1 (09:30 - 12:00):
    Rest day

=== Weekly Workout Check-In ===
Did you complete all your workouts this week? (Y/N): y
```

## Author

Mitchell Endicott
