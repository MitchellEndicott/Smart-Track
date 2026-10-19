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

```
=== Weekly Workout Plan ===
Day: Monday
  Window 1 (07:00 - 08:00):
    Track: 100m (6x80m walk in sprints @ 85%)
  Window 2 (16:00 - 17:30):
    Track: Long Jump (80m, 4x60m, 80m, x4, all out)

Day: Tuesday
  Window 1 (16:00 - 17:30):
    Gym: Power Clean @ 44.4 lbs, 6 sets x 2 reps
      Accessory 1: Box Jumps - 3 sets x 10-15 reps
      Accessory 2: Plyometric Jumps - 3 sets x 10-15 reps
```

Sample run with 100m and Long Jump, goals Speed and Power, and example PRs and availability.

## Author

Mitchell Endicott
